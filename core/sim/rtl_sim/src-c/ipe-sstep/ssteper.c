#include "ssteper.h"


#define RESET_TACTL TACTL |= TACLR


// Used to initiate timerA 
void init_ssteper(void){
    asm __volatile__("mov %0, r8" ::"r"(0xcaca) : "r8");

    /*
        TASSEL_2: TimerA is getting its clock from the submain clock
        MC_2: Enable continious mode so we can know how much time has elapsed since the interrupt was send
        TACL: clears the module
        TAIE: enables sending interrupts when overflows
    */
    TACTL = TASSEL_2 | MC_2 | TACLR | TAIE;

    /*
        CCIE: we enable interrupts
    */
    TACCTL0 = CCIE;
    TACCR1 = 0xa;

    return;
}


void readTACCR0(void){
    return;
}

#pragma vector=TIMERA0_VECTOR
__interrupt void timera0_isr(void){

    asm __volatile__("mov %0, r8" ::"r"(0xABA) : "r8");

    readTACCR0();
    RESET_TACTL;
}

