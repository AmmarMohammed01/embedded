2026-08-08
----------
21.9.2 **TWCR** - TWI Control Register (page 199)
*TWSTA*: application writes bit to one when it desires to become a master on 2-wire serial bus.
*TWSTO*: Writing a 1 to this in master mode STOPS TWI exchange. Automatically set to 0 afterwards.
*TWEN* - Enables TWI.

21.9.3 **TWSR** - TWI Status Register (page 200)
TWS [7:3]: TWI STATUS.
TWPS: Prescaler Bits.
- NOTE: Application designer should _mask the prescaler bits_ when trying to read the TWI status bits.
- Prescaler table 21-8 @ page 200

21.9.4 TWDR - TWI Data Register
- Contains data. TWI can be in _transmit_ or _receive_ mode!

21.9.5 TWAR - TWI (Slave) Adress Register (page 201)
[7:1] TWA: TWI (Slave) Address Register
- Loaded w/ a 7-bit slave address (2^7: 0-127)
[0] TWGCE: TWI General Call Recognition Enable Bit ** ??? **

21.9.6 TWAMR - TWI (Slave) Address Mask Register
[7:1] TWAM: TWI Address Mask ??

---

TMP1075 Datasheet Page 8
6.7 Timing Requirements: TMP1075

FAST MODE (MHz)
| MIN | MAX |
| --- | --- |
| 0.001 | 0.4 |

HIGH-SPEED MODE (MHz)
| MIN | MAX |
| --- | --- |
| 0.001 | 2.56 |

0.4 * 10^6 = 400kHz
0.001 * 10^6 = 1kHz

I will choose 400kHz.

400,000 = 16,000,000 / (16 + 2(TWBR) x (Prescaler=64))

TWBR =

---

TMP1075 Datasheet Page 13
7.3 Feature Description
7.3.1 Digital Temperature Output

Table with binary to temperature celsius conversion.

---

Read about I2C in ATmega328P datasheet.

As soon as SCL is above LOW, data is transferred at stable levels - exceptions for START and STOP conditions.

START & STOP CONDITIONS (page 175)
- MASTER _initiates_ and _terminates_ a data transmission.
- MASTER issues START condition to _initiate_ transmission.
- MASTER issues STOP condition to _terminate_ transmission.
- Between START & STOP condition, bus is considered busy. (no other master should try to seize control of bus)
- REPEATED START: when same master doesn't want to lose control of bus, but wants to send newer/different data

- START: HIGH TO LOW
- STOP: LOW TO HIGH

NTS (Note To Self):
- What does START and STOP look in data packets?
- How does data look like?

ADDRESS PACKET FORMAT (page 175)
- 9 bits long: 7 bits of address, 1 READ/WRITE control bit, and an acknowledge bit
    - If READ/WRITE bit set: read operation. packet called SLA+R
    - else: write operation. packet called SLA+W (slave address + write)
- Slave being addressed, acknowledge by pulling SDA low in the ninth SCL (ACK) cycle.
    - If slave doesn't pull it low (busy or used by other master), SDA line remains high

All addresses can be used by slaves except 0000 000. This is **general call**.
- During general call: all slaves respond by pulling the SDA line low in ACK cycle.
- general call used by master to: transmit same message to several slaves in teh system.

2026-08-09
DATA PACKET FORMAT (page 176)
- 9 bits long: 1 data byte (8 bits), 1 acknowledge bit

- NTS: How is SDA different (always HIGH, then LOW on acknowledge bit) on receiver when it is connected to Transmitter sending a different SDA signal?

COMBINING ADDRESS AND DATA PACKETS INTO A TRANSMISSION (page 176)
Transmission consists of:
1. START condition,
2. One or more data packets,
3. STOP condition.

- Empty message (just start and stop condition) is illegal

OVERVIEW OF TWI COMPONENTS - (PAGE 179-181)

**HELPFUL!!!!** 21.6 Using the TWI (Page 181)
- Page 181-182 runs through a **step-by-step** procedure on how to interface TWI
- Table 21-2 shows really useful C code on how to interface w/ TWI (page 183)

Status Codes

21.7.6 Combining Several TWI Modes
- Switch from Master Transmitter to Master Receiver during the same connection

---

~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/compat/twi.h


~/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/util/twi.h

---

2026-08-13

## TWI on ATmega328P Info
Apparently, the TWDR register is used a lot when dealing with both TRANSMIT and RECEIVE modes in TWI.

How to read status register TWSR?
TWSR status is in first five bits. Prescaler bits occupy last 2 bits.
| 7    | 6    | 5    | 4    | 3    | 2 | 1     | 0     |
| ---- | ---- | ---- | ---- | ---- | - | ----- | ----- |
| TWS7 | TWS6 | TWS5 | TWS4 | TWS3 | - | TWPS1 | TWPS0 |

1111 1000 = 0xF8
TWSR & 0xF8 = TWSR[7:3] followed by 000

Page 189 - Table 21-4 Status Codes for Master Receiver Mode
- Mentions prescaler bits are 0. So my decision to & 0xF8 works. One-to-one translation. That's why the last hex digit is only ever an 8 (1 000) or 0 (0 000). The 3 zeros are from the prescaler.
```text
0x08 [ 8] = START condition transmitted
0x10 [16] = REPEATED START condition transmitted
0x38 [56] = Arbitration lost in SLA+R or NOT ACK bit

0x40 [64] = SLA+R has been transmitted; ACK has been received
0x48 [72] = SLA+R has been transmitted; NOT ACK has been received
0x50 [80] = Data byte has been received; ACK has been returned
0x58 [88] = Data byte has been received; NOT ACK has been returned
```

Page 186 - Table 21-3 Status Codes for Master Transmitter Mode
```text
0x08 [ 8] = START condition transmitted
0x10 [16] = REPEATED START condition transmitted

0x18 [24] = SLA+W has been transmitted; ACK has been received
0x20 [32] = SLA+W has been transmitted; NOT ACK has been received
0x28 [40] = Data byte has been transmitted; ACK has been returned
0x30 [48] = Data byte has been transmitted; NOT ACK has been returned

0x38 [56] = Arbitration lost in SLA+W or data bytes
```

Page 175 Address Packet Format
R/W
- When R/W is set, read is performed (1). otherwise write (0).


## TMP1075 Info
### Page 14:
I found out that the TMP1075 I2C address can be changed by setting the address pins: A2, A1, A0.
- I will just leave A0 to ground: which gives the device a 7-bit address of (100 1000) 0x48 (page 14)

### Page 15:
- The TMP1075 has 4 registers, shown in Figure 7-2.
- "Temperature Register" contains the temperature data.
- Just write to the "Pointer register" once telling what register you want to read. This value is remembered during repeated START (read operations) and only changes with a write operation.

In beginning:
- MCU is transmitter
- TMP1075 is receiver

Then:
- MCU is receiver
- TMP1075 is transmitter

