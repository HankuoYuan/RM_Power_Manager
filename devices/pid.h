//
// Created by Lao·Zhu on 2021/1/16.
//

#ifndef _DEVICE_PID_H_
#define _DEVICE_PID_H_

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float I_Sum;
    float User;
    float Result;
    float LastError;
    float Maxinum;
    float Minium;
    float I_Sum_Max;
} PID_Structure;

extern PID_Structure PID_Capacitor;
void PID_Get_Result(PID_Structure *PID_Handler, float collect);
void PID_ValueConfig(void);
void PID_CalculateTask(void *pvParameters);

#endif //_DEVICE_PID_H_
