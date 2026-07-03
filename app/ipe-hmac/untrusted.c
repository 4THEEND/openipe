#include <msp430.h>

#include "libipe/ipe_support.h"
#include "libipe/sim_io.h"


int IPE_ENTRY attest(void);

uint8_t mac_region[33] = {0};

int signal_done(int a) {
    return a + 1;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog

    /* Free-running Timer_A (SMCLK, ~1 tick/cycle) to time the IPE call;
     * note TAR is 16-bit so counts wrap after 65535 cycles. */
    TACTL = TASSEL_2 | MC_2 | TACLR;          // SMCLK, continuous mode, clear
    uint16_t t0 = TAR;
    puts("running IPE HMAC calculation..");
    attest();
    uint16_t cycles = TAR - t0;
    printf("IPE took %u cycles\n", cycles);

    ASSERT(mac_region[24] != 0, "mac_region[24] != 0");

    PASS();
}
