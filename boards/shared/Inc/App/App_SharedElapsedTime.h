#pragma once

#include <stdint.h>

struct ElapsedTime *
         App_SharedElapsedTime_Create(uint32_t (*get_current_ms)(void));
void     App_SharedElapsedTime_Destroy(struct ElapsedTime *elapsed_time);
void     App_SharedElapsedTime_Reset(struct ElapsedTime *elapsed_time);
uint32_t App_SharedElapsedTime_Get(struct ElapsedTime *elapsed_time);
