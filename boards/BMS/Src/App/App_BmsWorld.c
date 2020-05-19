#include <stdlib.h>
#include <assert.h>

#include "App_BmsWorld.h"

struct BmsWorld
{
    struct BmsCanTxInterface *can_tx_interface;
    struct BmsCanRxInterface *can_rx_interface;
    struct Imd *              imd;
    struct HeartbeatMonitor * heartbeat_monitor;
    struct RgbLedSequence *   rgb_led_sequence;
    struct LatchStatus *      bms_ok;
    struct LatchStatus *      imd_ok;
    struct LatchStatus *      bspd_ok;
};

struct BmsWorld *App_BmsWorld_Create(
    struct BmsCanTxInterface *const can_tx_interface,
    struct BmsCanRxInterface *const can_rx_interface,
    struct Imd *const               imd,
    struct HeartbeatMonitor *const  heartbeat_monitor,
    struct RgbLedSequence *const    rgb_led_sequence,
    struct LatchStatus *const       bms_ok,
    struct LatchStatus *const       imd_ok,
    struct LatchStatus *const       bspd_ok)
{
    struct BmsWorld *world = (struct BmsWorld *)malloc(sizeof(struct BmsWorld));
    assert(world != NULL);

    world->can_tx_interface  = can_tx_interface;
    world->can_rx_interface  = can_rx_interface;
    world->imd               = imd;
    world->heartbeat_monitor = heartbeat_monitor;
    world->rgb_led_sequence  = rgb_led_sequence;
    world->bms_ok            = bms_ok;
    world->imd_ok            = imd_ok;
    world->bspd_ok           = bspd_ok;

    return world;
}

void App_BmsWorld_Destroy(struct BmsWorld *world)
{
    free(world);
}

struct BmsCanTxInterface *
    App_BmsWorld_GetCanTx(const struct BmsWorld *const world)
{
    return world->can_tx_interface;
}

struct BmsCanRxInterface *
    App_BmsWorld_GetCanRx(const struct BmsWorld *const world)
{
    return world->can_rx_interface;
}

struct Imd *App_BmsWorld_GetImd(const struct BmsWorld *const world)
{
    return world->imd;
}

struct HeartbeatMonitor *
    App_BmsWorld_GetHeartbeatMonitor(const struct BmsWorld *const world)
{
    return world->heartbeat_monitor;
}

struct RgbLedSequence *
    App_BmsWorld_GetRgbLedSequence(const struct BmsWorld *const world)
{
    return world->rgb_led_sequence;
}

struct LatchStatus *App_BmsWorld_GetBmsOk(const struct BmsWorld *const world)
{
    return world->bms_ok;
}

struct LatchStatus *App_BmsWorld_GetImdOk(const struct BmsWorld *const world)
{
    return world->imd_ok;
}

struct LatchStatus *App_BmsWorld_GetBspdOk(const struct BmsWorld *const world)
{
    return world->bspd_ok;
}
