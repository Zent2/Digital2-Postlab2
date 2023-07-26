/* 
 * File:   UART.h
 * Author: Christian Alessandro Campos López 21760
 *
 * Created on 24 de julio de 2023, 10:36 PM
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  

/** Para el ReadMe
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
//******************************************************************************
// Iniciar UART
//******************************************************************************
void UART_init(char E);
//******************************************************************************
// Configuración canal para recibir datos
//******************************************************************************
void UART_RX_config (uint16_t baudrate);

//******************************************************************************
// Configuración canal para enviar datos
//******************************************************************************
void UART_TX_config (uint16_t baudrate);

//******************************************************************************
// Función para escribir al UART
//******************************************************************************
void UART_write_char (char c);

//******************************************************************************
// Función para escribir cadena
//******************************************************************************
void UART_write_cadena (char *cadena);

//******************************************************************************
// Función para leer del UART
//******************************************************************************
char UART_read_char ();
#endif	/* UART_H */

