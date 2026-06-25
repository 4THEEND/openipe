#include "sim_io.h"

/*
 * Override the default printf()/puts() backend: MSP430-GCC's stdio calls
 * write() with the finalized string, which we route to the UART peripheral.
 */
int write(int fd, const char *buf, int len)
{
    (void)fd;
    for (int i = 0; i < len; i++)
        *UART_TXD = (uint8_t)buf[i];
    return len;
}
