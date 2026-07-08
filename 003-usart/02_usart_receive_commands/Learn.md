# Learning about USART
2026-07-04

Reading the register descriptions helped me understand what is going on in USART.

Next time: read register descriptions first, next read example code snippet, then read other sections for further clarification.

## Reference

ATmega328p Datasheet

---

## Page 159

### UDRn = USART I/O Data Register n

UDRn Read: RXB[7:0]

UDRn Write: TXB[7:0]

Transmit and receive (read & write) registers share the same io address.

For 5,6,7 bit characters - upper bits unused.

---

### UCSRnA = USART Control and Status Register n A

| Bit           | 7    | 6     | 5     | 4    | 3    | 2    | 1     | 0 |
| -             | -    | -     | -     | -    | -    | -    | -     | - |
|               | RXCn | TXCn  | UDREn | FEn  | DORn | UPEn | U2Xn  | MPCMn |
| Read/Write    | R    | R/W   | R     | R    | R    | R    | R/W   | R/W |
| Initial Value | 0    | 0     | 1     | 0    | 0    | 0    | 0     | 0

Most of the bits here are READ only.

Bit 7 - RXCn: USART Receive Complete

Bit 6 - TXCn: USART Transmit Complete
- Set after entire frame shifted out
- When no new data in transmit buffer (UDRn)
- Automatically cleared when transmit complete interrupt enabled, or cleared by writing 1 to bit location

Bit 5 - UDREn: USART Data Register Empty 

Bit 4 - FEn: Frame Error

Bit 3 - DORn: Data OverRun

Bit 2 - UPEn: USART Parity Error

Bit 1 - U2Xn: Double the USART Transmission Speed
- ONLY HAS AFFECT FOR ASYNCHRONOUS OPERATION
- Synchronous: Write a bit 0
- Asynchronous: Write a bit 1, Reduces baud rate divider from 16 to 8, doubling transfer rate

Bit 0 - MPCMn: Multi-processor Communication Mode
- more info page 158

---

## Page 160

### UCSRnB = USART Control and Status Register n B

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| - | - | - | - | - | - | - | - | - |
| | RXCIEn | TXCIEn | UDRIEn | RXENn | TXENn | UCSZn2 | RXB8n | TXB8n |
| Read/Write | R/W | R/W | R/W | R/W | R/W | R/W | R | R/W |
| Initial Value | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0

Bit 7 - RX Complete Interrupt (n/a)

Bit 6 - TX Complete Interrupt (n/a)

Bit 5 - USART Data Register Empty Interrupt Enable (n/a)

Bit 4 - Receiver Enable (**IMPORTANT**)
- set 0b1 to enable
- overrides normal port (pin) operation of RxDn pin

Bit 3 - Transmitter Enable (**IMPORTANT**)
- set 0b1 to enable
- overrides normal port (pin) operation of TxDn pin

Bit 2 - UCSZn2 Character Size (n/a)
- Used in addition to UCSZn1:0 in UCSRnC Register
- This bit can be used in acheiving 9-bit char option (table shown page 162)

Bit 1 - RXB8n Receive Data Bit 8 (n/a)
- The 9th bit when using 9 bit serial frames
- Note to self: Called bit 8, because 8:0 is 9 bits

Bit 0 - TXB8n Transmit Data Bit 8 (n/a)
- The 9th bit when using 9 bit serial frames

---

## Page 161

Note: I put the register tables twice since I wanted to see what looks better in Markdown.

### UCSRnC = USART Control and Status Register n C

```Markdown
Bit:  7       6       5     4     3     2      1      0
      ------------------------------------------------------------
      UMSELn1 UMSELn0 UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
```

### UCSRnC = USART Control and Status Register n C

| 7       | 6       | 5     | 4     | 3     | 2      | 1      | 0      |
| ------- | ------- | ----- | ----- | ----- | ------ | ------ | ------ |
| UMSELn1 | UMSELn0 | UPMn1 | UPMn0 | USBSn | UCSZn1 | UCSZn0 | UCPOLn |
| 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 |

NOTE: Values above are the one's I have set by going through settings listed below. In code, there are some values that are not manipulated/accessed since the register starts with a set of default values (listed in chart on datasheet).

#### UCSRnC 7:6
First two bits are to select USART mode.
For this project, 0b00 will be selected to use Asynchronous mode USART.

#### UCSRnC 5:4
- Next two are Parity Mode bits.
- Disable: set bits to 0b00.

#### UCSRnC 3
- Stop Bit Select, number of stop bits transmitter inserts.
- Two stop bits: set USBS0 0b1

#### UCSRnC 2:1
- Sets a size of a character in the data frame.
- 8-bit: set to 0b11 (use UCSZ00 and write a 3).


#### UCSRnC 0
- Clock Polarity Setting, either rising or falling.
- Used for synchronous mode, if using asynchronous just set a 0.


---

## Page 162

UBRR = USART Baud Rate Registers

UBRR has 16 bits total. UBRR15:12 is reserved for future compatibility

Of UBRR11:0
UBRRnH = Most significant 4 bits
UBRRnL = Least significant 8 bits

---
