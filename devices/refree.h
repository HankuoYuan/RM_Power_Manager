//
// Created by Lao·Zhu on 2021/3/26.
//

#ifndef PROGRAM_DEVICES_REFREE_H_
#define PROGRAM_DEVICES_REFREE_H_

typedef enum {
    kGameStatusCmdId = 0x0001,
    kGameResultCmdId = 0x0002,
    kGameRobotHpCmdId = 0x0003,
    kDartStatusCmdId = 0x0004,
    kIcraZoneStatusCmdId = 0x0005,
    kFieldEventsCmdId = 0x0101,
    kSupplyProjectileActionCmdId = 0x0102,
    kRefereeWarningCmdId = 0x0104,
    kDartRemainingCmdId = 0x0105,
    kRobotStatusCmdId = 0x0201,
    kPowerHeatDataCmdId = 0x0202,
    kRobotPosCmdId = 0x0203,
    kBuffCmdId = 0x0204,
    kAerialRobotEnergyCmdId = 0x0205,
    kRobotHurtCmdId = 0x0206,
    kShootDataCmdId = 0x0207,
    kBulletRemainingCmdId = 0x0208,
    kRobotRfidStatusCmdId = 0x0209,
    kDartClientCmdId = 0x020A,
    kStudentInteractiveDataCmdId = 0x0301,
    kRobotInteractiveDataCmdId = 0x0302,
    kRobotCommandCmdId = 0x0303,
} RefereeCmdId;

typedef struct {
    unsigned char sof;
    unsigned short data_length;
    unsigned char seq;
    unsigned char crc8;
} FrameHeaderStruct;

// Unpacking order
typedef enum {
    kStepHeaderSof = 0,
    kStepLengthLow = 1,
    kStepLengthHigh = 2,
    kStepFrameSeq = 3,
    kStepHeaderCrc8 = 4,
    kStepDataCrc16 = 5,
} UnpackStep;

// Unpacking data
typedef struct {
    FrameHeaderStruct *p_header;
    unsigned short data_len;
    unsigned char protocol_packet[128];
    UnpackStep unpack_step;
    unsigned short index;
} UnpackData;

/*------------------------REFEREE_GAME_CMD---- 0x40 -------------------*/
typedef struct {
    unsigned char game_type: 4;
    unsigned char game_progress: 4;
    unsigned short stage_remain_time;
} GameStatus;

typedef struct {
    unsigned char winner;
} GameResult;

typedef struct {
    unsigned short red_1_robot_HP;
    unsigned short red_2_robot_HP;
    unsigned short red_3_robot_HP;
    unsigned short red_4_robot_HP;
    unsigned short red_5_robot_HP;
    unsigned short red_7_robot_HP;
    unsigned short red_outpost_HP;
    unsigned short red_base_HP;
    unsigned short blue_1_robot_HP;
    unsigned short blue_2_robot_HP;
    unsigned short blue_3_robot_HP;
    unsigned short blue_4_robot_HP;
    unsigned short blue_5_robot_HP;
    unsigned short blue_7_robot_HP;
    unsigned short blue_outpost_HP;
    unsigned short blue_base_HP;
} GameRobotHp;

typedef struct {
    unsigned char dart_belong;
    unsigned short stage_remaining_time;
} DartStatus;

typedef struct {
    unsigned char F1_zone_status: 1;
    unsigned char F1_zone_buff_debuff_status: 3;
    unsigned char F2_zone_status: 1;
    unsigned char F2_zone_buff_debuff_status: 3;
    unsigned char F3_zone_status: 1;
    unsigned char F3_zone_buff_debuff_status: 3;
    unsigned char F4_zone_status: 1;
    unsigned char F4_zone_buff_debuff_status: 3;
    unsigned char F5_zone_status: 1;
    unsigned char F5_zone_buff_debuff_status: 3;
    unsigned char F6_zone_status: 1;
    unsigned char F6_zone_buff_debuff_status: 3;
} IcraBuffDebuffZoneStatus;

/*-------------------REFEREE_BATTLEFIELD_CMD_SET---- 0x41 -------------*/
typedef struct {
    unsigned int event_type;
} EventData;

typedef struct {
    unsigned char supply_projectile_id;
    unsigned char supply_robot_id;
    unsigned char supply_projectile_step;
    unsigned char supply_projectile_num;
} SupplyProjectileAction;

typedef struct {
    unsigned char level;
    unsigned char foul_robot_id;
} RefereeWarning;

typedef struct {
    unsigned char dart_remaining_time;
} DartRemainingTime;

/*------------------------REFEREE_ROBOT_CMD---- 0x42 -------------------*/
typedef struct {
    unsigned char robot_id;
    unsigned char robot_level;
    unsigned short remain_HP;
    unsigned short max_HP;
    unsigned short shooter_heat0_cooling_rate;
    unsigned short shooter_heat0_cooling_limit;
    unsigned short shooter_heat1_cooling_rate;
    unsigned short shooter_heat1_cooling_limit;
    unsigned char mains_power_gimbal_output: 1;
    unsigned char mains_power_chassis_output: 1;
    unsigned char mains_power_shooter_output: 1;
} GameRobotStatus;

typedef struct {
    unsigned short chassis_volt;
    unsigned short chassis_current;
    float chassis_power;
    unsigned short chassis_power_buffer;
    unsigned short shooter_heat0;
    unsigned short shooter_heat1;
} PowerHeatData;

typedef struct {
    float x;
    float y;
    float z;
    float yaw;
} GameRobotPos;

typedef struct {
    unsigned char power_rune_buff;
} Buff;

typedef struct {
    unsigned char energy_point;
    unsigned char attack_time;
} AerialRobotEnergy;

typedef struct {
    unsigned char armor_id: 4;
    unsigned char hurt_type: 4;
} RobotHurt;

typedef struct {
    unsigned char bullet_type;
    unsigned char bullet_freq;
    float bullet_speed;
} ShootData;

typedef struct {
    unsigned char bullet_remaining_num;
} BulletRemaining;

typedef struct {
    unsigned int rfid_status;
} RfidStatus;

typedef struct {
    unsigned char dart_launch_opening_status;
    unsigned char dart_attack_target;
    unsigned short target_change_time;
    unsigned char first_dart_speed;
    unsigned char second_dart_speed;
    unsigned char third_dart_speed;
    unsigned char fourth_dart_speed;
    unsigned short last_dart_launch_time;
    unsigned short operate_launch_cmd_time;
} DartClientCmd;

/*********************** Interactive data between robots----0x0301 ********************/
typedef enum {
    kRobotInteractiveCmdIdMin = 0x0200,
    kRobotInteractiveCmdIdMax = 0x02FF,
    kClientGraphicDeleteCmdId = 0x0100,
    kClientGraphicSingleCmdId = 0x0101,
    kClientGraphicDoubleCmdId = 0x0102,
    kClientGraphicFiveCmdId = 0x0103,
    kClientGraphicSevenCmdId = 0x0104,
    kClientCharacterCmdId = 0x0110,
} DataCmdId;

typedef enum {
    kRedHero = 1,
    kRedEngineer = 2,
    kRedStandard1 = 3,
    kRedStandard2 = 4,
    kRedStandard3 = 5,
    kRedAerial = 6,
    kRedSentry = 7,
    kRedRadar = 9,
    kBlueHero = 101,
    kBlueEngineer = 102,
    kBlueStandard1 = 103,
    kBlueStandard2 = 104,
    kBlueStandard3 = 105,
    kBlueAerial = 106,
    kBlueSentry = 107,
    kBlueRadar = 109,
} RobotId;

typedef enum {
    kRedHeroClientId = 0x0101,
    kRedEngineerClientId = 0x0102,
    kRedStandard1ClientId = 0x0103,
    kRedStandard2ClientId = 0x0104,
    kRedStandard3ClientId = 0x0105,
    kRedAerialClientId = 0x0106,
    kBlueHeroClientId = 0x0165,
    kBlueEngineerClientId = 0x0166,
    kBlueStandard1ClientId = 0x0167,
    kBlueStandard2ClientId = 0x0168,
    kBlueStandard3ClientId = 0x0169,
    kBlueAerialClientId = 0x016A,
} ClientId;

typedef struct {
    unsigned short data_cmd_id;
    unsigned short send_ID;
    unsigned short receiver_ID;
} StudentInteractiveHeaderData;

typedef enum {
    kAdd = 1,
    kModify = 2,
    kDelete = 3
} GraphicOperateType;

typedef struct {
    unsigned char graphic_name[3];
    unsigned int operate_type: 3;
    unsigned int graphic_type: 3;
    unsigned int layer: 4;
    unsigned int color: 4;
    unsigned int start_angle: 9;
    unsigned int end_angle: 9;
    unsigned int width: 10;
    unsigned int start_x: 11;
    unsigned int start_y: 11;
    unsigned int radius: 10;
    unsigned int end_x: 11;
    unsigned int end_y: 11;
} GraphicDataStruct;

typedef struct {
    FrameHeaderStruct tx_frame_header_;
    unsigned short cmd_id_;
    StudentInteractiveHeaderData graphic_header_data_;
    GraphicDataStruct graphic_data_struct_;
    unsigned short frame_tail_;
} DrawClientGraphicData;

typedef struct {
    FrameHeaderStruct tx_frame_header_;
    unsigned short cmd_id_;
    StudentInteractiveHeaderData graphic_header_data_;
    GraphicDataStruct graphic_data_struct_;
    unsigned char data_[30];
    unsigned short frame_tail_;
} DrawClientCharData;

/********************** Robot Interactive data ----0x0302 *******************************************/
typedef struct {
    unsigned char *data;
} RobotInteractiveData;

/********************** Robot command data ----0x0303 ***********************************************/
typedef struct {
    float target_position_x;
    float target_position_y;
    float target_position_z;
    unsigned char command_keyboard;
    unsigned short target_robot_ID;
} RobotCommand;

/***********************Frame tail(CRC8_CRC16)********************************************/
const unsigned char
    CRC8_INIT = 0xff;
const unsigned char CRC8_table[256] =
    {
        0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
        0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
        0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
        0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
        0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
        0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
        0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
        0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
        0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
        0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
        0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
        0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
        0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
        0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
        0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
        0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
    };
const unsigned short CRC16_INIT = 0xffff;
const unsigned short wCRC_table[256] =
    {
        0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
        0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
        0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
        0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
        0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
        0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
        0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
        0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
        0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
        0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
        0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
        0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
        0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
        0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
        0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
        0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
        0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
        0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
        0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
        0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
        0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
        0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
        0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
        0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
        0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
        0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
        0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
        0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
        0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
        0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
        0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
        0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
    };

struct RefereeData {
    GameStatus game_status_;
    GameResult game_result_;
    GameRobotHp game_robot_hp_;
    DartStatus dart_status_;
    IcraBuffDebuffZoneStatus icra_buff_debuff_zone_status;
    EventData event_data_;
    SupplyProjectileAction supply_projectile_action_;
    RefereeWarning referee_warning_;
    DartRemainingTime dart_remaining_time_;
    GameRobotStatus game_robot_status_;
    PowerHeatData power_heat_data_;
    GameRobotPos game_robot_pos_;
    Buff buff_;
    AerialRobotEnergy aerial_robot_energy_;
    RobotHurt robot_hurt_;
    ShootData shoot_data_;
    BulletRemaining bullet_remaining_;
    RfidStatus rfid_status_;
    DartClientCmd dart_client_cmd_;
    StudentInteractiveHeaderData student_interactive_header_data_;
    GraphicDataStruct graphic_data_struct_;
    RobotInteractiveData robot_interactive_data_;
    RobotCommand robot_command_;
    int performance_system_; // Performance level system
};

#endif //PROGRAM_DEVICES_REFREE_H_
