#include "ssteper.h"


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


void __attribute__((interrupt(16))) TimerA_ISR(void){
    RESET_TACTL;
    asm __volatile__("mov %0, r8" ::"r"(0xABA) : "r8");
    ENABLE_TACTL;
}

