#ifndef SIM_IO_H
#define SIM_IO_H

#include "ipe_support.h"

/* NOTE: we don't include the full <stdio.h> here so as to not crash pycparser */
int puts(const char *s);
int printf(const char *restrict format, ...);

/* UART_TXD at byte address 0x0084 (omsp_uart_print BASE_ADDR=0x0080, TXD offset=4) */
#define UART_TXD ((volatile uint8_t *)0x0084)

/* Implemented in sim_io.c: routes the printf()/puts() backend to the UART. */
int write(int fd, const char *buf, int len);

#define ASSERT(cond, msg) \
    do { if (!(cond)) { puts("FAIL: " msg); EXIT(); } puts("ok:   " msg); } while (0)

#define PASS() do { puts("PASS"); EXIT(); } while (0)

#endif /* SIM_IO_H */
