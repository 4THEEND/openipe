#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"

DECLARE_IPE_STRUCT;


char IPE_CONST private_key[10] = {
    '1', 
    '2',
    'A',
    '4',
    '5',
    '6',
    '7',
    'B',
    'D',
    '8',
};


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");



    asm __volatile__("mov %0, r7" :: "r"(result) : "r7"); 
    asm __volatile__("mov %0, r8" ::"r"(0xbeef) : "r8");   
    
    while (1)
    {
        __no_operation();
    }
    return 0;
}

void IPE_ENTRY secure_poll_keyboard(void){

}

