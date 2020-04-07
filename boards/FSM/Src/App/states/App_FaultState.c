#include "states/App_FaultState.h"

#include "App_SharedMacros.h"

static void FaultStateRunOnEntry(struct StateMachine *state_machine)
{
    struct FsmWorld *world = App_SharedStateMachine_GetWorld(state_machine);
    struct FSMCanTxInterface *can_tx_interface = App_FsmWorld_GetCanTx(world);
    App_CanTx_SetPeriodicSignal_STATE(
        can_tx_interface, CANMSGS_DCM_STATE_MACHINE_STATE_FAULT_CHOICE);
}

static void FaultStateRunOnTick(struct StateMachine *state_machine)
{
    UNUSED(state_machine);
}

static void FaultStateRunOnExit(struct StateMachine *state_machine)
{
    UNUSED(state_machine);
}

const struct State *App_GetFaultState()
{
    static struct State fault_state = {
        .name         = "FAULT",
        .run_on_enter = FaultStateRunOnEntry,
        .run_on_tick  = FaultStateRunOnTick,
        .run_on_exit  = FaultStateRunOnExit,
    };

    return &fault_state;
}
