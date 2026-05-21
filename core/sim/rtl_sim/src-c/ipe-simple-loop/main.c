#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"

DECLARE_IPE_STRUCT;


enum RSA_OPERATION {
    ENCODE,
    DECODE,
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    apply_rsa(ENCODE, 6541);
    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");

    while (1)
    {
        __no_operation();
    }
    return 0;
}


int IPE_ENTRY apply_rsa(enum RSA_OPERATION op, int text){
    switch(op){
        case ENCODE:
            break;

        case DECODE:
            break;

        default:
            break;
    }
    return 0;
}

