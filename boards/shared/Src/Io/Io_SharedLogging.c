/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Io/Io_SharedLogging.h"
#include "SEGGER_RTT_Conf.h"

/******************************************************************************
 * Module Preprocessor Constants
 ******************************************************************************/
// RTT channel 0 is always present and reserved for Terminal usage. Name is
// fixed to "Terminal".
#define SEGGER_RTT_TERMINAL_CHANNEL (0)

/******************************************************************************
 * Module Preprocessor Macros
 ******************************************************************************/

/******************************************************************************
 * Module Typedefs
 ******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 ******************************************************************************/

/******************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Private Function Definitions
 ******************************************************************************/

/******************************************************************************
 * Function Definitions
 ******************************************************************************/
void Io_SharedLogging_Printf(const char *sFormat, ...)
{
    va_list ParamList;

    va_start(ParamList, sFormat);
    (void)SEGGER_RTT_vprintf(SEGGER_RTT_TERMINAL_CHANNEL, sFormat, &ParamList);
    va_end(ParamList);
}
