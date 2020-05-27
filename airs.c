bool AirPositive_IsClosed(void) {
    return (AIR_POWER_STATUS == 1) && (AIR+_EN == ON);
}

void AirPositive_Open(void) {
    // If we turn off AIR+ just by using AIR+_EN, the TSDM won't
    // discharge the tactive system. To turn off AIR+ and have TSDM
    // discharge the tractive system, we must disable BMS_STATUS as well.
    
    // Set AIR+_EN = OFF
    // Set BMS_STATUS = BAD
}

// Closing the AIR+ requires the AIR shutdown loop to be complete, which
// relies on multiple conditions being fulfilled:
//
//   - All shutdown switches are closed
//   - Tractive system master switch (TSMS) is closed
//   - BMS_STATUS, IMD_STATUS, and BSPD_STATUS are all OK
// 
// The only thing the BMS has control over is BMS_STATUS. In other words,
// BMS can't guarantee the AIR- is closed, hence why this method is called
// _RequestClose() and not just _Close().
//
// To check whether or not AIR+ is actually closed, the caller must use
// the IsClosed() method.
void AirPositive_RequestClose(void) {
    // Set AIR+_EN = ON
    // Set BMS_STATUS = OK
}

bool AirNegative_IsClosed(void) {
    return AIR_POWER_STATUS == 1;
}

void AirNegative_Open(void) {
    // Set BMS_STATUS = BAD
}

// Closing the AIR- requires the AIR shutdown loop to be complete, which
// relies on multiple conditions being fulfilled:
//
//   - All shutdown switches are closed
//   - Tractive system master switch (TSMS) is closed
//   - BMS_STATUS, IMD_STATUS, and BSPD_STATUS are all OK
// 
// The only thing the BMS has control over is BMS_STATUS. In other words,
// BMS can't guarantee the AIR- is closed, hence why this method is called
// _RequestClose() and not just _Close().
//
// To check whether or not AIR- is actually closed, the caller must use
// the IsClosed() method.
void AirNegative_RequestClose(void) {
    // Set BMS_STATUS = OK
}

