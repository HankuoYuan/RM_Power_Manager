//
// Created by Lao·Zhu on 2021/4/6.
//

#include "main.h"

unsigned char *Savebuf = (unsigned char *) 0x38800000UL;
unsigned char Reset_Number = 0;

void DataRead_From_Flash(void) {
    unsigned char Buffer[16];
    for (unsigned int counter = 0; counter < sizeof(Buffer); counter++)
        Buffer[counter] = Savebuf[counter];
}

void DataSave_To_Flash(Saving_Reason_e reason) {
    unsigned char Buffer[16];
    Buffer[0] = (reason & 0x07) << 5;
    Buffer[0] |= (FSM_Status.Charge_Mode & 0x07) << 2;
    Buffer[0] |= FSM_Status.Typology_Mode & 0x03;
    Buffer[1] = (FSM_Status.Expect_Mode & 0x07) << 5;
    Buffer[1] |= (FSM_Status.FSM_Mode & 0x07) << 2;
    Buffer[1] |= Reset_Number & 0x03;
    Buffer[2] = FloatToInt16(I_Capacitor) >> 8;
    Buffer[3] = FloatToInt16(I_Capacitor) & 0x00ff;
    Buffer[4] = FloatToInt16(I_Chassis) >> 8;
    Buffer[5] = FloatToInt16(I_Chassis) & 0x00ff;
    Buffer[6] = FloatToInt16(V_Capacitor) >> 8;
    Buffer[7] = FloatToInt16(V_Capacitor) & 0x00ff;
    Buffer[8] = FloatToInt16(V_Chassis) >> 8;
    Buffer[9] = FloatToInt16(V_Chassis) & 0x00ff;
    Buffer[10] = FloatToInt16(V_Baterry) >> 8;
    Buffer[11] = FloatToInt16(V_Baterry) & 0x00ff;
    Buffer[12] = referee_data_.game_robot_status_.chassis_power_limit;
    Buffer[13] = FloatToInt16(referee_data_.power_heat_data_.chassis_power) >> 8;
    Buffer[14] = FloatToInt16(referee_data_.power_heat_data_.chassis_power) & 0x00ff;
    Buffer[15] = ((HAL_GPIO_ReadPin(EN_NMOS_GPIO_Port, EN_NMOS_Pin) & 0x01) << 7)
        | ((HAL_GPIO_ReadPin(CHG_EN_GPIO_Port, CHG_EN_Pin) & 0x01) << 6)
        | ((HAL_GPIO_ReadPin(BOOST_EN_GPIO_Port, BOOST_EN_Pin) & 0x01) << 5)
        | ((HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin) & 0x01) << 4)
        | ((HAL_GPIO_ReadPin(LED2_GPIO_Port, LED2_Pin) & 0x01) << 3);
    for (unsigned int counter = 0; counter < sizeof(Buffer); counter++)
        Savebuf[counter] = Buffer[counter];
}
