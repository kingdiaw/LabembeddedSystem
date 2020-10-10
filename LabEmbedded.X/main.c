/*
 * File:   main.c
 * Author: Acer
 *
 * Created on October 10, 2020, 2:45 PM
 */
#include <xc.h>
#define _XTAL_FREQ	64000000L

void setup(void);
void delay(unsigned int x);

void main(void) {
    setup();
    TRISBbits.TRISB0 = 1;
    TRISC = 0;
    INTCONbits.GIE = 1;         // Enable Interrupt System
    INTCONbits.INT0IE = 1;      // Enable EXT0 only
    INTCONbits.INT0IF = 0;      // Clear Interrupt flag
    INTCON2bits.INTEDG0 = 0;    // Falling edge trigger
    
    //Your program start here
    unsigned int x=1;
    while (1) {
        x=x<<1;
        if(x == 256)
            x=1;        
        LATC = x;        
        delay(100);
    }
}
//Your program end here

/*
BAHAGIAN INI JANGAN KACAU :)
 */
void setup(void) {

    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;
    VREFCON0 = 0b10110000; // Fixed Voltage Reference is enabled, x4 (4.096V)
    ADCON1 = 0b00110000; //0b00110000=4.096V 0b00100000=2.048V 0b00000000=Vdd
    ADCON2 = 0b10000011;

    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
}

void delay(unsigned int x) {
    for (; x > 0; x--)__delay_ms(1);
}

static void interrupt ISR(void) {
    if(INTCONbits.INT0IF){
        LATC = 0xFF;
        delay(200);
        LATC = 0x00;
        delay(200);
        LATC = 0xFF;
        delay(200);
        LATC = 0x00;
        delay(200);
    }
    INTCONbits.INT0IF = 0;
}

