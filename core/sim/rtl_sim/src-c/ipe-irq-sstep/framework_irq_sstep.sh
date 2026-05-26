#!/bin/bash

set -ex

# run framework on initial input file
cd /openipe/core/sim/rtl_sim/src-c/ipe-irq-sstep
../framework/translator.py main.c

# copy main.c to generated_main.c
cp main.c generated_main.c

# remove original entry function from the generated file and replace it with the translator-generated one
sed -i '/uint16_t IPE_ENTRY simple_branch(uint16_t entry)/Q' generated_main.c
cat output/main.c >> generated_main.c

# run simulation
cd /openipe/core/sim/rtl_sim/run/
./run_c_irq ipe-irq-sstep
