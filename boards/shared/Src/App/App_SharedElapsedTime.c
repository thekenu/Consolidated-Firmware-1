#include <stdlib.h>
#include <assert.h>
#include "App_SharedElapsedTime.h"

struct ElapsedTime
{
    uint32_t (*get_current_ms)(void);
    uint32_t previous_ms;
};

struct ElapsedTime *
    App_SharedElapsedTime_Create(uint32_t (*get_current_ms)(void))
{
    struct ElapsedTime *elapsed_time = malloc(sizeof(struct ElapsedTime));
    assert(elapsed_time != NULL);

    elapsed_time->get_current_ms = get_current_ms;
    App_SharedElapsedTime_Reset(elapsed_time);

    return elapsed_time;
}

void App_SharedElapsedTime_Destroy(struct ElapsedTime *elapsed_time)
{
    free(elapsed_time);
}

void App_SharedElapsedTime_Reset(struct ElapsedTime *elapsed_time)
{
    elapsed_time->previous_ms = elapsed_time->get_current_ms();
}

uint32_t App_SharedElapsedTime_Get(struct ElapsedTime *elapsed_time)
{
    return elapsed_time->get_current_ms() - elapsed_time->previous_ms;
}
