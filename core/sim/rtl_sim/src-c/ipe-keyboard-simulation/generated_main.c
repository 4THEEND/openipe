#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"

DECLARE_IPE_STRUCT;

#define ENCODE 0
#define DECODE 1


int rsa_n = 57677;
int rsa_e = 11;
int IPE_VAR private_key = 20771; // 0b0101000100100011


uint16_t IPE_FUNC multiply_mod(uint16_t a, uint16_t b, uint16_t n){
    return (a * b) % n;
}


uint16_t IPE_FUNC modpow(uint16_t a, uint16_t e, uint16_t n){
    uint16_t result = 1;

    while(e > 0){
        // The branch we'll try to gain information on
        if(e & 1){ 
            result = multiply_mod(result, a, n); 
            e--;
        } 
        else{ 
            a = multiply_mod(a, a, n); 
            e /= 2;
        }
    }

    return 0;
}

// Could be outside of ipe since only use non secret values
uint16_t IPE_FUNC rsa_encode(int plain){
    return modpow(plain, rsa_e, rsa_n);
}


uint16_t IPE_FUNC rsa_decode(int cipher){
    return modpow(cipher, private_key, rsa_n);
}


int main(void)
{
    int result = 2;
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog

    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");

    result = apply_rsa(ENCODE, 0);

    asm __volatile__("mov %0, r7" :: "r"(result) : "r7"); 
    asm __volatile__("mov %0, r8" ::"r"(0xbeef) : "r8");   
    
    while (1)
    {
        __no_operation();
    }
    return 0;
}

 __attribute__((section(".ipe_entry"))) int apply_rsa_internal(int rsa_operation, int text)
{
  if (rsa_operation == 0)
  {
    return rsa_operation * text;
  }
  else
    if (rsa_operation == 1)
  {
    return rsa_decode(text);
  }
  else
  {
    return - 1;
  }
}

