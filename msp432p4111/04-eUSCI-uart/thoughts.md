# Learning UART on MSP432
2026-09-22

UART communication is a mode accessible on the MSP432's Enchanced Universal Serial Communication Interface (eUSCI).

- eUSCI_A UART
- eUSCI_A & eUSCI_B SPI
- eUSCI_B I^2C

Meaning: eUSCI_A can support UART or SPI communications

The UART mode section 24: p.903-932
1. eUSCI_A overview p.904
2. eUSCI_A Introduction - UART Mode p.904-905
3. eUSCI_A Operation - UART Mode p.906-921
4. eUSCI_A UART Registers p.922-932

**Figure 24-1 eUSCI_Ax Block Diagram - UART Mode (UCSYNC = 0)**

Skimming the section. Familiarizing myself to the concepts of section 24.

**Table 24-7 eUSCI_A UART Registers**

Reading register names.
Reading register descriptions.

Next step, write setup register code.
