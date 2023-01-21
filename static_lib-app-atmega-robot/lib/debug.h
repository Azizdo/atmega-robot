
#include <uart.h>

Uart uart;

#define DEBUG
#ifdef DEBUG

# define DEBUG_PRINTDATA(x) uart.transmitData(X) // ou par RS-232
# define DEBUG_PRINTSTRING(x) uart.transmitString(x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort


#endif