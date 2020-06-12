#pragma once

#include <stdint.h>
#include <stdbool.h>

struct Efuse *App_Efuse_Create(
    void (*enable_channel1)(void),
    void (*enable_channel2)(void),
    void (*disable_channel1)(void),
    void (*disable_channel2)(void),
    float (*get_current_channel1)(void),
    float (*get_current_channel2)(void),
    bool (*is_in_fail_safe_mode)(void));
void  App_Efuse_Destroy(struct Efuse *efuse);
void  App_Efuse_EnableChannel1(const struct Efuse *efuse);
void  App_Efuse_EnableChannel2(const struct Efuse *efuse);
void  App_Efuse_DisableChannel1(const struct Efuse *efuse);
void  App_Efuse_DisableChannel2(const struct Efuse *efuse);
float App_Efuse_GetCurrentChannel1(const struct Efuse *efuse);
float App_Efuse_GetCurrentChannel2(const struct Efuse *efuse);
bool  App_Efuse_IsInFailSafeMode(const struct Efuse *efuse);
