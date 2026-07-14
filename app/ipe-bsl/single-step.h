#ifndef SINGLE_STEP_H
#define SINGLE_STEP_H

#ifndef BOOTCODE_HANDLING_LATENCY
#define BOOTCODE_HANDLING_LATENCY 0xA
#endif


// Should be > BOOTCODE_HANDLING_LATENCY + 1
#ifndef INIT_LATENCY
#define INIT_LATENCY 0x27 // Start of the function we need to interrupt
#endif

#ifndef SSTEP_LATENCY
#define SSTEP_LATENCY 0x2B // Should be 2B when interrupting IPE
#endif

#ifndef NB_INSTR
#define NB_INSTR 873 // Number of consecutive instructions we want to interrupt
#endif

void init_ssteper(void);

#endif
