#include "ssteper.h"


// Used to initiate timerA 
void init_ssteper(void){
    asm __volatile__("mov %0, r8" ::"r"(0xcaca) : "r8");


    return;
}