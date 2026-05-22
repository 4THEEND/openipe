#include "ssteper.h"


#define RESET_TACTL (TACTL |= TACLR)
#define INIT_LATENCY 0xffff
#define SSTEP_LATENCY 


// Used to initiate timerA 
void init_ssteper(void){
    asm __volatile__("mov %0, r8" ::"r"(0xcaca) : "r8");

    /*
        TASSEL_2: TimerA is getting its clock from the submain clock
        MC_2: Enable continious mode so we can know how much time has elapsed since the interrupt was send
        TACL: clears the module
        TAIE: enables sending interrupts when overflows
    */
    TA0CTL = TASSEL_2 | MC_2 | TACLR | TAIE;

    /*
        CCIE: we enable interrupts
    */
    TA0CCTL0 = CCIE;
    TA0CCR0 = INIT_LATENCY;
    RESET_TACTL;

    return;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timera0_isr(void){

    asm __volatile__("mov %0, r8" ::"r"(0xABA) : "r8");
    
    RESET_TACTL;
}


// Useless ?
#pragma vector=TIMER0_A1_VECTOR
__interrupt void timera1_isr(void){}

