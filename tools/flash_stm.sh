#!/bin/bash

echo "Flash STM chip"
st-flash write output/stm32f411re_nucleo.bin 0x8000000