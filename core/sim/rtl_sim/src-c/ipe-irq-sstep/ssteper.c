#include "ssteper.h"

#define RESET_TACTL (TA0CTL = TACLR | MC_0)
#define TACTL_PARAMS_ENABLE (TASSEL_2 | MC_1 | TACLR | TAIE)
#define ENABLE_TACTL (TA0CTL = TACTL_PARAMS_ENABLE)

#define INIT_LATENCY 0xA
#define SSTEP_LATENCY 0x50
// Should be 2B

#define BOOTCODE_HANDLING_LATENCY 0xA


// Used to initiate timerA 
void init_ssteper(void){
    asm __volatile__("mov %0, r8" ::"r"(0xcaca) : "r8");
    /*
        CCIE: we enable interrupts
    */
    TA0CCR0 = INIT_LATENCY;

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
        ".include \"../../bin/template_defs.asm\"\n\t"
 
        // HERE's the code to mesure
        "mov &TAR, r11\n\t"
        "sub %0, r11\n\t"
        "mov #0xcacb, r12\n\t"
        // Should find another way

        // Reset TimerA
        "mov %1, &TACCR0\n\t"
        "mov %2, &TACTL\n\t"
        "reti"
        :: 
            "i"(BOOTCODE_HANDLING_LATENCY) ,
            "i"(SSTEP_LATENCY), 
            "i"(TACTL_PARAMS_ENABLE):
    );
}

