#include <msp430.h>
#include "../framework/libipe/ipe_support.h"
#include "output/generated_ipe_header.h"
#include "ssteper.h"

DECLARE_IPE_STRUCT;


uint16_t IPE_VAR private_key = 0b0101010101010101;


int main(void)
{
    uint16_t result;
    WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog
    __enable_interrupt();

    asm __volatile__("mov %0, r8" ::"r"(0xdead) : "r8");
    
    init_ssteper();

    result = simple_branch(0b0101010101010101);

    asm __volatile__("mov %0, r7" :: "r"(result) : "r7"); 
    asm __volatile__("mov %0, r8" ::"r"(0xbeef) : "r8");   
    
    while (1)
    {
        __no_operation();
    }
    return 0;
}

 __attribute__((section(".ipe_entry"))) uint16_t simple_branch_internal(uint16_t entry)
{
  int result = 0;
  if (entry == private_key)
  {
    result += 5;
  }
  else
  {
     asm __volatile__("nop\n\tnop");
  }
  return result;
}

