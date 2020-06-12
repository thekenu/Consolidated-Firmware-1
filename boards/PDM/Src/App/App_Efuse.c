#include <stdlib.h>
#include <assert.h>
#include "App_Efuse.h"

struct Efuse
{
    void (*enable_channel1)(void);
    void (*enable_channel2)(void);
    void (*disable_channel1)(void);
    void (*disable_channel2)(void);
    float (*get_current_channel1)(void);
    float (*get_current_channel2)(void);
    bool (*is_in_fail_safe_mode)(void);
};

struct Efuse *App_Efuse_Create(
    void (*enable_channel1)(void),
    void (*enable_channel2)(void),
    void (*disable_channel1)(void),
    void (*disable_channel2)(void),
    float (*get_current_channel1)(void),
    float (*get_current_channel2)(void),
    bool (*is_in_fail_safe_mode)(void))
{
    struct Efuse *efuse = malloc(sizeof(struct Efuse));
    assert(efuse != NULL);

    efuse->enable_channel1      = enable_channel1;
    efuse->enable_channel2      = enable_channel2;
    efuse->disable_channel1     = disable_channel1;
    efuse->disable_channel2     = disable_channel2;
    efuse->get_current_channel1 = get_current_channel1;
    efuse->get_current_channel2 = get_current_channel2;
    efuse->is_in_fail_safe_mode = is_in_fail_safe_mode;

    return efuse;
}

void  App_Efuse_Destroy(struct Efuse *efuse)
{
    free(efuse);
}

void  App_Efuse_EnableChannel1(const struct Efuse *efuse)
{
    efuse->enable_channel1();
}

void  App_Efuse_EnableChannel2(const struct Efuse *efuse)
{
    efuse->enable_channel2();
}

void  App_Efuse_DisableChannel1(const struct Efuse *efuse)
{
    efuse->disable_channel1();
}

void  App_Efuse_DisableChannel2(const struct Efuse *efuse)
{
    efuse->disable_channel2();
}

float App_Efuse_GetCurrentChannel1(const struct Efuse *efuse)
}

float App_Efuse_GetCurrentChannel2(const struct Efuse *efuse)
{
    return efuse->get_current_channel2();
}

bool  App_Efuse_IsInFailSafeMode(const struct Efuse *efuse)
{
    return efuse->is_in_fail_safe_mode();
}
