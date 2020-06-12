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
#ifdef __arm__
    StaticSemaphore_t spi_mutex_storage;
    SemaphoreHandle_t spi_mutex;
#elif __unix__
    pthread_mutex_t spi_mutex;
#endif
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
#ifdef __arm__
    efuse->spi_mutex =
        xSemaphoreCreateMutexStatic(&(efuse->spi_mutex_storage));
#elif __unix__
    pthread_mutex_init(&(efuse->spi_mutex), NULL);
#endif

    return efuse;
}

void  App_Efuse_Destroy(struct Efuse *efuse)
{
    free(efuse);
}

void  App_Efuse_EnableChannel1(const struct Efuse *efuse)
{
    // Turn on IN0 pin
    efuse->enable_channel1();
}

void  App_Efuse_EnableChannel2(const struct Efuse *efuse)
{
    // Turn on IN1 pin
    efuse->enable_channel2();
}

void  App_Efuse_DisableChannel1(const struct Efuse *efuse)
{
    // Turn on IN0 pin
    efuse->disable_channel1();
}

void  App_Efuse_DisableChannel2(const struct Efuse *efuse)
{
    // Turn on IN1 pin
    efuse->disable_channel2();
}

float App_Efuse_GetCurrentChannel1(const struct Efuse *efuse)
{
    // 1. SPI transaction that we are reading from channel 1
    // 2. Use ADC to read voltage on CNSN pin
    //
    // @note I think we GetCurrentChannel1 and GetCurrentChannel2 should share
    //       a mutex it's a SPI transaction?
    #ifdef __arm__
    xSemaphoreTake(efuse->spi_mutex, portMAX_DELAY);
#elif __unix__
    pthread_mutex_lock(&(efuse->spi_mutex));
#endif

    const float current = efuse->get_current_channel1();

#ifdef __arm__
    xSemaphoreGive(efuse->spi_mutex);
#elif __unix__
    pthread_mutex_unlock(&(efuse->spi_mutex));
#endif
    
    return current;
}

float App_Efuse_GetCurrentChannel2(const struct Efuse *efuse)
{
    // 1. SPI transaction that we are reading from channel 2
    // 2. Use ADC to read voltage on CNSN pin
    //
    // @note I think we GetCurrentChannel1 and GetCurrentChannel2 should share
    //       a mutex it's a SPI transaction?
    #ifdef __arm__
    xSemaphoreTake(efuse->spi_mutex, portMAX_DELAY);
#elif __unix__
    pthread_mutex_lock(&(efuse->spi_mutex));
#endif

    const float current = efuse->get_current_channel2();

#ifdef __arm__
    xSemaphoreGive(efuse->spi_mutex);
#elif __unix__
    pthread_mutex_unlock(&(efuse->spi_mutex));
#endif
    
    return current;
}

bool  App_Efuse_IsInFailSafeMode(const struct Efuse *efuse)
{
    // Read FSOB pin
    return efuse->is_in_fail_safe_mode();
}
