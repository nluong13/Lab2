/* ASSIGNMENT 2
Hardware:
- Output: 3 blue LED (row1), 5 grn LED (row2), 7 red LED (row3)
- Input: 6 switches

Software:
- Start: all LEDs on
- Everytime switch is pressed, one LED turns off
- NO cheating: player chooses one row, switches for other rows ignored
*/

// LEDs connected to Port 
// Registers for Port 0
#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)

// Registers connected to Port 1
#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)

// Registers connected to Port 2
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)

// Pairs of bits in the PINMODE registers control the 
// resistor mode for particular port bits: 
//    00 pull-up <-- this is the default 
//    01 repeater 
//    10 resistor disabled (PullNone) 
//    11 pull-down 
// PINMODE0 : port 0, bits 0-15 
// PINMODE1 : port 0, bits 16-31 
// PINMODE2 : port 1, bits 0-15 
// PINMODE3 : port 1, bits 16-31 
// PINMODE4 : port 2, bits 0-15 
#define PINMODE0 (*(volatile unsigned int *)0x4002c040) 
#define PINMODE1 (*(volatile unsigned int *)0x4002c044) 
#define PINMODE2 (*(volatile unsigned int *)0x4002c048) 
#define PINMODE3 (*(volatile unsigned int *)0x4002c04c) 
#define PINMODE4 (*(volatile unsigned int *)0x4002c050) 

// wait function
void wait(float seconds) {
    volatile int count = seconds * 21.33e6;
    while (count > 0) count--;
}

// write external LED functions
static inline void writeBLED1(int state) {
    if (state == 1) FIO0PIN |= (1<<1);
    else FIO0PIN &= ~(1<<1);
}
static inline void writeBLED2(int state) {
    if (state == 1) FIO0PIN |= (1<<2);
    else FIO0PIN &= ~(1<<2);
}
static inline void writeBLED3(int state) {
    if (state == 1) FIO2PIN |= (1<<3);
    else FIO2PIN &= ~(1<<3);
}
static inline void writeGLED1(int state) {
    if (state == 1) FIO2PIN |= (1<<4);
    else FIO2PIN &= ~(1<<3);
}
static inline void writeGLED2(int state) {
    if (state == 1) FIO0PIN |= (1<<24);
    else FIO0PIN &= ~(1<<24);
}
static inline void writeGLED3(int state) {
    if (state == 1) FIO0PIN |= (1<<25);
    else FIO0PIN &= ~(1<<25);
}
static inline void writeGLED4(int state) {
    if (state == 1) FIO2PIN |= (1<<2);
    else FIO2PIN &= ~(1<<2);
}
static inline void writeGLED5(int state) {
    if (state == 1) FIO2PIN |= (1<<3);
    else FIO2PIN &= ~(1<<3);
}static inline void writeRLED1(int state) {
    if (state == 1) FIO0PIN |= (1<<24);
    else FIO0PIN &= ~(1<<24);
}
static inline void writeRLED2(int state) {
    if (state == 1) FIO0PIN |= (1<<25);
    else FIO0PIN &= ~(1<<25);
}
static inline void writeRLED3(int state) {
    if (state == 1) FIO2PIN |= (1<<2);
    else FIO2PIN &= ~(1<<2);
}
static inline void writeRLED4(int state) {
    if (state == 1) FIO2PIN |= (1<<3);
    else FIO2PIN &= ~(1<<3);
}static inline void writeRLED5(int state) {
    if (state == 1) FIO0PIN |= (1<<24);
    else FIO0PIN &= ~(1<<24);
}
static inline void writeRLED6(int state) {
    if (state == 1) FIO0PIN |= (1<<25);
    else FIO0PIN &= ~(1<<25);
}
static inline void writeRLED7(int state) {
    if (state == 1) FIO2PIN |= (1<<2);
    else FIO2PIN &= ~(1<<2);
}

// read switch functions
static inline int readBSW1(void) {
    return((FIO0PIN >> 24) & 1);
}
static inline int readBSW2(void) {
    return((FIO0PIN >> 25) & 1);
}
static inline int readGSW1(void) {
    return((FIO1PIN >> 30) & 1);
}
static inline int readGSW2(void) {
    return((FIO1PIN >> 32) & 1);
}
static inline int readRSW1(void) {
    return((FIO0PIN >> 26) & 1);
}
static inline int readRSW2(void) {
    return((FIO0PIN >> 2) & 1);
}

// starting game configuration function - all LEDs ON
void startCon() {
    writeBLED1(1); wait(0.01);
    writeBLED2(1); wait(0.01);
    writeBLED3(1); wait(0.01);
    writeGLED1(1); wait(0.01);
    writeGLED2(1); wait(0.01);
    writeGLED3(1); wait(0.01);
    writeGLED4(1); wait(0.01);
    writeGLED5(1); wait(0.01);
    writeRLED1(1); wait(0.01);
    writeRLED2(1); wait(0.01);
    writeRLED3(1); wait(0.01);
    writeRLED4(1); wait(0.01);
    writeRLED5(1); wait(0.01);
    writeRLED6(1); wait(0.01);
    writeRLED7(1); wait(0.01);
}

// setup pin configurations
void configPins() {
    // output external LEDs
    FIO2DIR |= (1<<0) | (1<<1) | (1<<2) | (1<<3); // g5, b1, b2, b3
    FIO0DIR |= (1<<4) | (1<<5) | (1<<10) | (1<<11) | (1<<9) | (1<<8) | (1<<7) | (1<<6) | (1<<0) | (1<<1) | (1<<18); // g1, g2, g3, g4, r1, r2, r3, r4, r5, r6, r7
    
    // read input switches
    FIO0DIR &= ~(1<<24) & ~(1<<25) & ~(1<<26) & ~(1<<2); // bsw1, bsw2, rsw1, rsw2
    FIO1DIR &= ~(1<<30) & ~(1<<31); // gsw 1, gsw 2

    // configure PINMODE - pull down (active high)
    /* get PINMODE register & bit:
        - Multiply port and bit numbers by 2
        - If the resulting bit number exceeds 31, subtract 32 from it 
          and add 1 to the PINMODE number
    */
    PINMODE0 |= (1<<10) | (1<<11); // blue sw1 (port 0, bits 16-17)
    PINMODE0 |= (1<<12) | (1<<13); // blue sw2 (port 0, bits 18-19)
    PINMODE3 |= (1<<28) | (1<<29); // grn sw1 (port 1, bits 28-29)
    PINMODE3 |= (1<<30) | (1<<31); // grn sw2 (port 1, bits 30-31)
    PINMODE1 |= (1<<20) | (1<<21); // red sw1 (port 0, bits 20-21)
    PINMODE0 |= (1<<4) | (1<<5); // red sw2 (port 0, bits 4-5)
}



int  main() {
    int countBlu = 0;  // count of blue switch presses
    int countGrn = 0; // count of green switch presses
    int countRed = 0; // count of red switch presses
    int totalCount = 0; // total count of switch presses
    int maxBlu = 3;
    int maxGrn = 5;
    int maxRed = 7;
    int maxTotal = 15;
    int bsw1 = 0;
    int bsw2 = 0;
    int gsw1 = 0;
    int gsw2 = 0;
    int rsw1 = 0;
    int rsw2 = 0;
    int prevBsw1 = bsw1;
    int prevBsw2 = bsw2;
    int prevGsw1 = gsw1;
    int prevGsw2 = gsw2;
    int prevRsw1 = rsw1;
    int prevRsw2 = rsw2;

    // set up input/output pins
    configPins();
    
    // start of game (all LEDs ON)
    startCon();
    
    do {
        // read switch states once per loop
        bsw1 = readBSW1();
        bsw2 = readBSW2();
        gsw1 = readGSW1();
        gsw2 = readGSW2();
        rsw1 = readRSW1();
        rsw2 = readRSW2();

        /* FROM HW6
        if (rsw != prevRsw) {
            pos--;
            wait(0.02);
        }
        if (gsw != prevGsw) {
            pos++;
            wait(0.02);
        }
        */

        // when switch is pressed, increment count
        if (bsw1 == 1) {
            countBlu++; wait(0.02);
            writeBLED1(0);
            if (countBlu > maxBlu){

            }
        }
        if (bsw2 == 1) {
            countBlu++; wait(0.02);
        }
        if (gsw1 == 1) {
            countGrn++; wait(0.02);
        }
        if (gsw2 == 1) {
            countGrn++; wait(0.02);
        }
        if (rsw1 == 1) {
            countRed++; wait(0.02);
        }
        if (rsw2 == 1) {
            countRed++; wait(0.02);
        }
        
        /* HW 6
        switch (pos) {
            case -3: rPos3(); break;
            case -2: rPos2(); break;
            case -1: rPos1(); break;
            case 0: startPos(); break;
            case 1: gPos1(); break;
            case 2: gPos2(); break;
            case 3: gPos3(); break;
        }
        */

        // update previous switch states
        prevBsw1 = bsw1;
        prevBsw2 = bsw2;
        prevGsw1 = gsw1;
        prevGsw2 = gsw2;
        prevRsw1 = rsw1;
        prevRsw2 = rsw2;

        totalCount++;
    } while(totalCount >= 0 && totalCount <= maxTotal);

}



