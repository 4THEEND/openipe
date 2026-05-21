#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"

DECLARE_IPE_STRUCT;

#define ENCODE 0
#define DECODE 1

// In theory we're not supposed to use the same key twice but yeah 
uint16_t IPE_VAR private_key = 0b0101010101010101;


uint16_t IPE_FUNC otp_encode(int plain){
    return 0;
}


uint16_t IPE_FUNC otp_decode(int cipher){
    return 1;
}


int main(void)
{
    int result;
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");

    result = apply_otp(ENCODE, 0);

    asm __volatile__("mov %0, r7" :: "r"(result) : "r7"); 
    asm __volatile__("mov %0, r8" ::"r"(0xbeef) : "r8");   
    
    while (1)
    {
        __no_operation();
    }
    return 0;
}

uint16_t IPE_ENTRY apply_otp(int otp_operation, uint16_t text){
    if(otp_operation == ENCODE){
        return otp_encode(text);
    } 
    else if(otp_operation == DECODE)  {
        return otp_decode(text);
    } else {
        return -1;
    }
}

