# lpc_chip_122x_lib
LPCOPEN chip library for NXP LPC 122x devices

INTRODUCTION
------------

This is a ported LPCOPEN library for NXP LPC122x devices.
I used the lpcopen library a lot with other mcu's, and found it quite useful.
I have been looking for an LPCOPEN library for LPC122x devices for a while, but NXP does not provide LPCOPEN support for these chips officially.
Since I have some spare boards with an LPC1225 mcu, and I was too lazy to write every peripherial driver from scratch, I went on to port one from a similar chip library.
Since the architecture is more or less the same as of the LPC11xx chips, the porting was just copying and modifying register values, structures etc.

WARNING
-------

I have not tested every part of the library, and there are also things (peripherial specific driver parts) that are missing.
I do not take any guarantee that it is working.
I am glad if you can use it, and feel free to contribute.