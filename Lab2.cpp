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
   // FIX THIS
    PINMODE1 |= (1<<5) | (1<<6); // red sw1 (port 0, bits 20-21)
    PINMODE1 |= (1<<7) | (1<<8); // red sw2 (port 0, bits 22-23)
    PINMODE3 |= (1<<5) | (1<<6); // grn sw1 (port 1, bits 20-21)
    PINMODE3 |= (1<<5) | (1<<6); // grn sw2 (port 1, bits 22-23)
    PINMODE4 |= (1<<10) | (1<<11); // blue sw1 (port 2, bits 10-11)
    PINMODE4 |= (1<<12) | (1<<13); // blue sw2 (port 2, bits 12-13)
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

if (readBSW1() == 1) {
    int count++;
}
if (readBSW2() == 1) {
    int count++;
}
if (readGSW1() == 1) {
    int count++;
}
if (readGSW2() == 1) {
    int count++;
}
if (readRSW1() == 1) {
    int count++;
}
if (readRSW2() == 1) {
    int count++;
}

int  main() {


  configPins();
    
    // rope position at start of game (LED2, LED3 ON)
    startPos();
    
    do {
        // read switch states once per loop
        rsw = readRSW();
        gsw = readGSW();
        
        if (rsw != prevRsw) {
            pos--;
            wait(0.02);
        }
        
        if (gsw != prevGsw) {
            pos++;
            wait(0.02);
        }
        
        switch (pos) {
            case -3: rPos3(); break;
            case -2: rPos2(); break;
            case -1: rPos1(); break;
            case 0: startPos(); break;
            case 1: gPos1(); break;
            case 2: gPos2(); break;
            case 3: gPos3(); break;
        }
        
        prevRsw = rsw;
        prevGsw = gsw;
    } while(pos >= -2 && pos <= 2);

}



