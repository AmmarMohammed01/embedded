# SPI

Section 25 p.933-956

Four signals are used for SPI data exchange:
- UCxSIMO
    - master device is output (TRANSMIT)
    - slave device is input
- UCxSOMI
    - master device is input (RECEIVE)
    - slave device is output
- UCxCLK
    - clock
- UCxSTE
    - enable
    - used in 4-pin mode when there are multiple master devices
    - not used in 3-pin mode

SPI character output code be:
- 7-bits
- 8-bits

This means the protocol can transfer a max of 1 byte at a time.
