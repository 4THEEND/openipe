#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"
#include "ssteper.h"

DECLARE_IPE_STRUCT;

#define ENCODE 0
#define DECODE 1

// In theory we're not supposed to use the same key twice but yeah 
// In fact we're using a xor cipher rather than an otp but nvm it's otp on Z/2Z
uint16_t IPE_VAR private_key = 0b0101010101010101;


uint64_t IPE_FUNC custom_16_xor(uint16_t n, uint16_t m){
    uint16_t result = 0;

    for(int i = 0; i < 16; i++){
        if((n & 1) != (m & 1)){
            result += (1 << i);
        }

        n >>= 1;
        m >>= 1;
    }
    return result;
}

uint16_t IPE_FUNC otp_encode(uint16_t plain){
    return custom_16_xor(private_key, plain);
}


uint16_t IPE_FUNC otp_decode(uint16_t cipher){
    return private_key ^ cipher;
}


int main(void)
{
    uint16_t result;
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");
    
    init_ssteper();

    result = apply_otp(ENCODE, 0);

    asm __volatile__("mov %0, r7" :: "r"(result) : "r7"); 
    asm __volatile__("mov %0, r8" ::"r"(0xbeef) : "r8");   
    
    while (1)
    {
        __no_operation();
    }
    return 0;
}

 __attribute__((section(".ipe_entry"))) uint16_t apply_otp_internal(int otp_operation, uint16_t text)
{
  if (otp_operation == 0)
  {
    return otp_encode(text);
  }
  else
    if (otp_operation == 1)
  {
    return otp_decode(text);
  }
  else
  {
    return - 1;
  }
}

