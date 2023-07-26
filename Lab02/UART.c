/* 
 * File:   USART.c
 * Author: Christian Alessandro Campos López 21760
 *
 * Created on 24 de julio de 2023, 10:38 PM
 */
#include "UART.h"
//******************************************************************************
// Variables Internas
//******************************************************************************
#define _XTAL_FREQ 8000000;
//******************************************************************************
// Iniciar UART
//******************************************************************************
void UART_init(char E){
    if (E != 0 && E != 1){
        E=0;
    }
//Configuracion de interrupciones
    PIR1bits.RCIF=0;
    PIE1bits.RCIE=E;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
}
//******************************************************************************
// Configuración baudrate
//******************************************************************************
void UART_baudrate(uint16_t baudrate){
    // Cálculo del valor de SPBRG y SPBRGH para la velocidad de baudios especificada
    SPBRG = (8000000 / (baudrate * 4)) - 1; // Valor para el registro SPBRG
    SPBRGH = ((8000000 / (baudrate * 4)) - 1) << 8; // Valor para el registro SPBRGH (ajustado el desplazamiento)

}
//******************************************************************************
// Configuración canal para recibir datos
//******************************************************************************
void UART_RX_config(uint16_t baudrate) {
    // Configuración del EUSART para recibir (RX)

    TXSTAbits.SYNC = 0; // Modo asíncrono
    TXSTAbits.BRGH = 1; // Alta velocidad de baudios
    
    BAUDCTLbits.BRG16 = 1; // Baud Rate de 16 bits
    

    UART_baudrate(baudrate);

    //SPBRG=207;
    //SPBRGH=0;
    RCSTAbits.SPEN = 1; // Habilitar el módulo EUSART
    RCSTAbits.RX9 = 0;  // Recepción de 8 bits
    RCSTAbits.CREN = 1; // Habilitar recepción continua
    TXSTAbits.TXEN = 1; // Habilitar transmisor
    RCREG=0;
}

//******************************************************************************
// Configuración canal para enviar datos
//******************************************************************************
void UART_TX_config(uint16_t baudrate) {
    
    // Configuración del EUSART para transmitir (TX)
    TXSTAbits.SYNC = 0; // Modo asíncrono
    TXSTAbits.BRGH = 1; // Alta velocidad de baudios
    
    BAUDCTLbits.BRG16 = 1; // Baud Rate de 16 bits
    
    
    UART_baudrate(baudrate);
    //SPBRG=207;
    //SPBRGH=0;
    RCSTAbits.SPEN = 1; // Habilitar el módulo EUSART
    RCSTAbits.RX9 = 0;  // Recepción de 8 bits
    RCSTAbits.CREN = 1; // Habilitar recepción continua
    TXSTAbits.TXEN = 1; // Habilitar transmisor
}

//******************************************************************************
// Función para escribir al UART
//******************************************************************************
void UART_write_char (char c){
    INTCONbits.GIE=0;
    while(!PIR1bits.TXIF); //Esperar a que el registro de transmisión esté disponible
    TXREG = c; //Enviar el carácter actual
    INTCONbits.GIE=1;


}

//******************************************************************************
// Función para escribir cadena
//******************************************************************************
void UART_write_cadena(char *cadena) {
    int i = 0;
    while(*(cadena+i) != '\0') { //Mientras no se alcance el final de la cadena
        while(!PIR1bits.TXIF); //Esperar a que el registro de transmisión esté disponible
        TXREG = *(cadena+i); //Enviar el carácter actual
        i++; //Incrementar el índice para apuntar al siguiente carácter
    }
    while(!PIR1bits.TXIF);
    TXREG=32; //Espacio
}

//******************************************************************************
// Función para leer del UART
//******************************************************************************
char UART_read_char (){
    INTCONbits.GIE=0;
    while (!RCIF); // Esperar a que llegue un carácter
    INTCONbits.GIE=1;
    return RCREG; // Leer el carácter recibido
    

}
