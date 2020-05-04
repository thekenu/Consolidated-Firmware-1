#pragma once

#define STATIC_DEFINE_APP_SET_PERIODIC_CAN_SIGNALS_IN_RANGE_CHECK(           \
    CAN_INTERFACE_TYPE)                                                      \
    static void App_SetPeriodicCanSignals_InRangeCheck(                      \
        struct CAN_INTERFACE_TYPE *const can_tx,                             \
        const struct InRangeCheck *const in_range_check,                     \
        void (*const can_signal_setter)(struct CAN_INTERFACE_TYPE *, float), \
        void (*const out_of_range_setter)(                                   \
            struct CAN_INTERFACE_TYPE *, uint8_t),                           \
        uint8_t in_range_choice, uint8_t underflow_choice,                   \
        uint8_t overflow_choice)                                             \
    {                                                                        \
        float                    value;                                      \
        enum InRangeCheck_Status status =                                    \
            App_InRangeCheck_GetValue(in_range_check, &value);               \
                                                                             \
        switch (status)                                                      \
        {                                                                    \
            case VALUE_IN_RANGE:                                             \
            {                                                                \
                out_of_range_setter(can_tx, in_range_choice);                \
            }                                                                \
            break;                                                           \
            case VALUE_UNDERFLOW:                                            \
            {                                                                \
                out_of_range_setter(can_tx, underflow_choice);               \
            }                                                                \
            break;                                                           \
            case VALUE_OVERFLOW:                                             \
            {                                                                \
                out_of_range_setter(can_tx, overflow_choice);                \
            }                                                                \
            break;                                                           \
        }                                                                    \
                                                                             \
        can_signal_setter(can_tx, value);                                    \
    }
