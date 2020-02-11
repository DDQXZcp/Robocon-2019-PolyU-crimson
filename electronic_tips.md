# Some electronic_tips:

## SRAM and flash of MCU

### SRAM - CANNOT store memory when power off, slow

Static random-access memory (static RAM or SRAM) is a type of semiconductor random-access memory (RAM) that uses bistable latching circuitry (flip-flop) to store each bit. SRAM exhibits data remanence,[1] 
but it is still volatile in the conventional sense that data is eventually lost when the memory is not powered.

### flash - can store memory when power off, fast(compared to flash)

Flash memory is an electronic (solid-state) non-volatile computer memory storage medium that can be electrically erased and reprogrammed. The two main types of flash memory are named after the NAND and NOR logic gates. The individual flash memory cells, consisting of floating-gate MOSFETs (floating-gate metal-oxide-semiconductor field-effect transistors), 
exhibit internal characteristics similar to those of the corresponding gates

### Comparison

SRAM - CANNOT store memory when power off, slow

We usually store variables in SRAM

flash - can store memory when power off, fast(compared to flash)

We usually store code in flash

A supplementary answer:

To answer your question, the sole purpose of flash is to store "code".  It is true that access to flash is much slower as compared to SRAM and hence certain microcontrollers provide an option to transfer part or full code to SRAM in order to avoid this delay of access latency of flash. 
You are right  that in the case where MCU is always on, there is no need to go to sleep mode, therefore SRAM will be suitable memory for the MCU, but there would always be a  "first time" during Power ON when you would need to load the SRAM which can only be done from flash. Another reason why flash would be needed as any power down/brown out/battery fail condition would leave the SRAM contents in "Indeterminate state" and would need a restart/reset and reload of SRAM where the flash is helpful. Hope this answers your query.

### Conclusion

For some running model that need to store a lot of variables, the limitation is SRAM.

### Nucleo board information

F103RB 128kb flash, 20KB SRAM, 72MHz max CPU frequency

F446RE 512 KB Flash, 128 KB SRAM, 180 MHz max CPU frequency
