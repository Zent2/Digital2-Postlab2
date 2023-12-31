/* 
 * File:   lcd.h
 * Author: Christian Alessandro Campos L�pez 21760
 *
 * Created on 22 de julio de 2023, 09:18 PM
 *  * Se utiliz� y se adaptaron las librer�as de Ligo George 
 * de la p�gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * ADAPTADO POR: Pablo Mazariegos (supongo xd)
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD4_H
#define	LCD4_H

#ifndef RS
#define RS RB6
#endif

#ifndef EN
#define EN RB7
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif

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
// FUNCI�N SIN RETORNO Y SIN VARIABLES
//******************************************************************************

//******************************************************************************
// Lcd_Port: Escoge la posici�n del LCD
//******************************************************************************
void Lcd_Port(char a);
//******************************************************************************
// Lcd_Cmd: Habilita y desabilita el LCD para mandar datos
//******************************************************************************
void Lcd_Cmd(char a);
//******************************************************************************
// Lcd_Clear: Limpia el LCD
//******************************************************************************
void Lcd_Clear(void);
//******************************************************************************
// Lcd_Set_Cursor: Escoge la posici�n del LCD
//******************************************************************************
void Lcd_Set_Cursor(char a, char b);
//******************************************************************************
// Lcd_Init: Inicia la configuraci�n del LCD
//******************************************************************************
void Lcd_Init(void);
//******************************************************************************
// Lcd_Write_Char: Manda los valores que se quieren desplegar (char)
//******************************************************************************
void Lcd_Write_Char(char a);
//******************************************************************************
// Lcd_Write_String: Manda los valores que se quieren despelgar (cadenas)
//******************************************************************************
void Lcd_Write_String(char *a);
//******************************************************************************
// Lcd_Shift_Right: Genera movimiento hacia la derecha
//******************************************************************************
void Lcd_Shift_Right(void);
//******************************************************************************
// Lcd_Shift_Right: Genera movimiento hacia la izquierda
//******************************************************************************
void Lcd_Shift_Left(void);


#endif	/* LCD4_H */

