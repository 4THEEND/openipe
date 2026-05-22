#include "ssteper.h"

#define __IPE_CUSTOM_IVT

#define RESET_TACTL (TA0CTL = TACLR | MC_0)
#define ENABLE_TACTL (TA0CTL = TASSEL_2 | MC_1 | TACLR | TAIE)
#define TIMER_LATENCY 0x50
#define SSTEP_LATENCY 0xE


// Used to initiate timerA 
void init_ssteper(void){
    asm __volatile__("mov %0, r8" ::"r"(0xcaca) : "r8");
    /*
        CCIE: we enable interrupts
    */
    TA0CCR0 = TIMER_LATENCY;

    /*
        TASSEL_2: TimerA is getting its clock from the submain clock
        MC_1: Count to CCR0 then reset
        TACL: clears the module
        TAIE: enables sending interrupts when overflows
    */
    ENABLE_TACTL;
    return;
}

// __attribute__((naked)) is mandatory since we have a special way of handling isr with ipe
__attribute__((naked, interrupt(16))) void TimerA_ISR(void){
    asm __volatile__(
        "push #0x8134\n\t" // Try to go directly there
        
        // INSERT PUSH HERE

        "push #0x8008\n\t"
        "push #0x0000\n\t"
        "reti"
    );
}

