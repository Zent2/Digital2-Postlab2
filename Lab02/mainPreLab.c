/* 
 * File:   mainLab.c
 * Author: Christian Alessandro Campos L�pez 21760
 *
 * Created on 22 de julio de 2023, 11:40 PM
 */

//******************************************************************************
// Palabra de configuraci�n
//******************************************************************************
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//******************************************************************************
// Librer�as Generales
//******************************************************************************
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
//******************************************************************************
// Librer�as Propias
//******************************************************************************
#include "ADC_config.h"
#include "lcd4.h"
#include "map.h"
//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000     // Frecuencia de oscilador de 8MHz

#define RS RB7
#define EN RB6
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
unsigned int a;
unsigned char valor_adc;
//******************************************************************************
// Prototipos de funci�n
//******************************************************************************
void setup(void);
//******************************************************************************
// Vector de Interrupci�n
//******************************************************************************

void __interrupt() isr(void) {
    if (PIR1bits.ADIF) {
        valor_adc=adc_read(); //Leer ADC y guardar valor en una variable
        
        __delay_us(10); //Peque�o delay de seguridad
        PIR1bits.ADIF=0; //Limpiar bandera ADC
    }
    return;
}
//******************************************************************************
// Funci�n principal
//******************************************************************************

void main(void) {
    setup();
    
    while(1){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("El valor del");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("potenciometro es:");
        __delay_ms(1000);
        // Convertir la variable num�rica a una cadena de caracteres
        Lcd_Clear();
        Lcd_Set_Cursor(2, 1);
        unsigned int pot_value = map(valor_adc, 0, 255, 0, 500);
        char pot_valueR[3]; // Arreglo para almacenar los dígitos individuales

        pot_valueR[0] = (pot_value / 100) + '0'; // Convertir centenas a carácter ASCII
        pot_valueR[1] = ((pot_value / 10) % 10) + '0'; // Convertir decenas a carácter ASCII
        pot_valueR[2] = (pot_value % 10) + '0'; // Convertir unidades a carácter ASCII

        Lcd_Write_Char(pot_valueR[0]); // Mostrar centenas
        Lcd_Write_Char('.'); // Mostrar punto decimal
        Lcd_Write_Char(pot_valueR[1]); // Mostrar decenas
        Lcd_Write_Char(pot_valueR[2]); // Mostrar unidades
        Lcd_Write_String("V"); // Mostrar 'V' para indicar voltios
        ADCON0bits.GO=1;
        __delay_ms(2000);
        ADCON0bits.GO=1;
  }
    return;
}
//******************************************************************************
// Funciones secundarias
//******************************************************************************

void setup(void) {
    // Configuraci�n de los puertos

    TRISD = 0x00;
    TRISB=0x00;
    
    //Oscilador a 8MHz
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 1;
    //Configuraci�n ADC 
    adc_IE(1);
    adc_init(13); //Inicia conversi�n ADC con el canal indicado
    
    //Configuraci�n LCD
    Lcd_Init();

}
