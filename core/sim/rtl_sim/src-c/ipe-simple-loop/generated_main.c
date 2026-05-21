#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"

DECLARE_IPE_STRUCT;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    apply_rsa(0, 6541);
    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");

    while (1)
    {
        __no_operation();
    }
    return 0;
}


int IPE_ENTRY apply_rsa(int op, int text){
    return 0;
}

 __attribute__((section(".ipe_entry"))) int apply_rsa_internal(int op, int text)
{
  return 0;
}

