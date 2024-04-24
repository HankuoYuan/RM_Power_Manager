//
// Created by LaoZhu on 2023/5/12.
//
#include "fsm.h"
#include "referee.h"

TaskHandle_t fsm_task_handler;
static struct fsm_t {
  mode_target_e mode;
  typology_e typology;
} main_fsm;

void fsm_set_mode(mode_target_e target_mode) {
  if (target_mode == all_off_mode || target_mode == selftest_mode) {
    power_info.expect_chassis_power = 0;
    main_fsm.typology = switches_all_off;
    pid_set_expect(0);
    close_all_switches();
  }
  if (!(power_info.battery_voltage < 18.0f && main_fsm.mode == all_off_mode))
    main_fsm.mode = target_mode;
}

mode_target_e fsm_get_mode(void) { return main_fsm.mode; }

typology_e fsm_get_typology(void) { return main_fsm.typology; }

_Noreturn void fsm_task(void *parameters) {
  (void)parameters;
  static typology_e last_typology = refresh_typology;
  delayms(100);
  main_fsm.mode = all_off_mode;
  main_fsm.typology = switches_all_off;
  calibrate_referee_config();
  pid_config();
  main_fsm.mode = normal_mode;
  while (1) {
    if (referee_available() != 1) {
      referee_info.chassis_power_limit = 50;
    }
    switch (main_fsm.mode) {
    case charge_mode:
      main_fsm.typology = charge_with_boost;
      power_info.expect_chassis_power =
          0.6f * (float)referee_info.chassis_power_limit;
      break;
    case boost_mode:
      if (power_info.capacitor_voltage < 8.0f)
        main_fsm.typology = pass_through;
      else
        main_fsm.typology = charge_with_boost;
      power_info.expect_chassis_power = 220.0f;
      break;
    case all_off_mode:
      main_fsm.typology = switches_all_off;
      power_info.expect_chassis_power = 0;
      break;
    default:
    case normal_mode:
      main_fsm.typology = pass_through;
      power_info.expect_chassis_power = (float)referee_info.chassis_power_limit;
      break;
    }

    if (main_fsm.typology == charge_with_boost) {
      if (power_info.capacitor_voltage >= 15.7f ||
          referee_info.chassis_power_buffer < 2)
        pid_set_expect(0);
      else {
        if (referee_info.chassis_power_buffer < 5)
          pid_set_expect((float)(referee_info.chassis_power_limit) * 0.6f);
        else if (referee_info.chassis_power_buffer < 10)
          pid_set_expect((float)(referee_info.chassis_power_limit - 5));
        else if (referee_info.chassis_power_buffer < 20)
          pid_set_expect((float)(referee_info.chassis_power_limit));
        else
          pid_set_expect((float)(referee_info.chassis_power_limit + 5));
      }
      charge_with_boost_switches(last_typology == pass_through,
                                 power_info.capacitor_voltage >= 15.7f ||
                                     referee_info.chassis_power_buffer < 2);
    } else if (last_typology != main_fsm.typology) {
      switch (main_fsm.typology) {
      case pass_through:
        pid_set_expect(0);
        passthrough_switch_only(last_typology == charge_with_boost);
        break;
      case switches_all_off:
        pid_set_expect(0);
        close_all_switches();
        break;
      default:
        pid_set_expect(0);
        close_all_switches();
        error_handler(__FILE__, __LINE__);
        break;
      }
    }
    pack_powerinfo_buffer();
    last_typology = main_fsm.typology;
    delayms(50);
  }
}
