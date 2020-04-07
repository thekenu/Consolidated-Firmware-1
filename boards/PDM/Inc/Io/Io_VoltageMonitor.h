#include "auto_generated/App_CanTx.h"

struct VoltageMonitor;

/**
 * Initialize the callback functions shared among all voltage monitors
 * @param can_tx_interface CAN TX interface
 */
void Io_VoltageMonitor_Init(struct PDMCanTxInterface *can_tx_interface);

/**
 * Error callback function for VBAT
 * @param voltage_monitor The voltage monitor that triggered the error
 */
void Io_VoltageMonitor_VbatErrorCallback(
    struct VoltageMonitor *voltage_monitor);

/**
 * Error callback function for 24V AUX
 * @param voltage_monitor The voltage monitor that triggered the error
 */
void Io_VoltageMonitor_24vAuxErrorCallback(
    struct VoltageMonitor *voltage_monitor);

/**
 * Error callback function for 24V ACC
 * @param voltage_monitor The voltage monitor that triggered the error
 */
void Io_VoltageMonitor_24vAccErrorCallback(
    struct VoltageMonitor *voltage_monitor);

/**
 * Get VBAT voltage from the ADC
 * @return VBAT voltage
 */
float Io_VoltageMonitor_GetVbatVoltage(void);

/**
 * Get the minimum threshold for VBAT voltage
 * @return Minimum threshold for VBAT voltage
 */
float Io_VoltageMonitor_GetVbatMinVoltage(void);
/**
 * Get the minimum threshold for VBAT voltage
 * @return Minimum threshold for VBAT voltage
 */
float Io_VoltageMonitor_GetVbatMaxVoltage(void);

/**
 * Get 24V AUX voltage from the ADC
 * @return 24V AUX voltage
 */
float Io_VoltageMonitor_Get24vAuxVoltage(void);

/**
 * Get the minimum threshold for 24V AUX voltage
 * @return Minimum threshold for 24V AUX voltage
 */
float Io_VoltageMonitor_Get24vAuxMinVoltage(void);

/**
 * Get the maximum threshold for 24V AUX voltage
 * @return Maximum threshold for 24V AUX voltage
 */
float Io_VoltageMonitor_Get24vAuxMaxVoltage(void);

/**
 * Get 24V ACC voltage from the ADC
 * @return 24V ACC voltage
 */
float Io_VoltageMonitor_Get24vAccVoltage(void);

/**
 * Get the minimum threshold for 24V ACC voltage
 * @return Minimum threshold for 24V ACC voltage
 */
float Io_VoltageMonitor_Get24vAccMinVoltage(void);

/**
 * Get the maximum threshold for 24V ACC voltage
 * @return Maximum threshold for 24V ACC voltage
 */
float Io_VoltageMonitor_Get24vAccMaxVoltage(void);
