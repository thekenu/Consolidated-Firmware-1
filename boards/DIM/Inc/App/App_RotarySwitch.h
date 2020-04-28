#pragma once

#include <stdint.h>
#include "App_ErrorCode.h"

struct RotarySwitch;

/**
 * Allocate and initialize a rotary switch with the given number of positions
 * @param get_switch_position A function that can be called to get the switch
 *                            position
 * @param num_switch_positions The total number of switch positions
 * @return The created rotary switch, whose ownership is given to the caller
 */
struct RotarySwitch *App_RotarySwitch_Create(
    uint32_t (*get_switch_position)(void),
    uint32_t num_switch_positions);

void App_RotarySwitch_Destroy(struct RotarySwitch *rotary_switch);

/**
 * Get the switch position for the given rotary switch
 * @param rotary_switch The rotary switch to get switch position for
 * @param returned_switch_position Buffer to hold the switch position
 * @return EXIT_CODE_OUT_OF_RANGE If the switch position exceeds the total
 *                                number of switch positions
 */
ExitCode App_RotarySwitch_GetSwitchPosition(
    const struct RotarySwitch *rotary_switch,
    uint32_t *                 returned_switch_position);
