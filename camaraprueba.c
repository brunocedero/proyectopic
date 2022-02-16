#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF  

#include <xc.h>
#include <stdint.h>
#include <math.h>
#define _XTAL_FREQ 4000000
#define EMISORSENSOR1 PORTAbits.RA6//SALIDA 
#define EMISORSENSOR2 PORTAbits.RA1 // SALIDA 
#define EMISORSENSOR3 PORTBbits.RB7 //SALIDA 
#define EMISORSENSOR4 PORTBbits.RB5 // SALIDA 
#define RECEPTORSENSOR1 PORTAbits.RA0 // RECEPTOR ES TODO ENTRADA //RECEPTOR ES EL ECHO
#define RECEPTORSENSOR2 PORTAbits.RA7
#define RECEPTORSENSOR3 PORTBbits.RB6
#define RECEPTORSENSOR4 PORTBbits.RB4 
//#define GIROMOTOR1 PORTAbits.RA1
#define LED1 PORTBbits.RB1
#define LED2 PORTBbits.RB2
#define LED3 PORTBbits.RB3
#define LED4 PORTAbits.RA2

int MINIMA_VARIACION = 20;
int temp100ms;
volatile uint32_t contador100us=0;
void __interrupt() rutinaInterrupcion(void){
    //temp100ms=0;
   //Esta función se llama automáticamente cuando ocurre la interrupción
    if(INTCONbits.T0IF != 0){ //Si la interrupción fue por timer
       INTCONbits.T0IF=0;
      // NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
        NOP();NOP();NOP();
       contador100us=contador100us+1;
       
       TMR0=245;//Inicialización, cuenta desde 248 hasta 256 = 8 cuentas = 1ms                       
    }
}

int
abs(int a)
{
	if(a < 0)
		return -a;
	return a;
}

 volatile int tiempoMedido1=0;
 volatile int tiempoMedido1Anterior=0;
 volatile uint32_t tiempoFinalSensor1=0;
 volatile int tiempoMedido2=0;
 volatile int tiempoMedido2Anterior=0;
 volatile uint32_t tiempoFinalSensor2=0;
 volatile int tiempoMedido3=0;
 volatile int tiempoMedido3Anterior=0;
 volatile uint32_t tiempoFinalSensor3=0;
 volatile int tiempoMedido4=0;
 volatile int tiempoMedido4Anterior=0;
 volatile uint32_t tiempoFinalSensor4=0;
 volatile uint32_t X;
 volatile uint32_t Y;
 volatile uint32_t x1;
 volatile uint32_t x2;
 volatile uint32_t y1;
 volatile uint32_t y2;

void main(void){
 
 //CONFIGURACION PUERTOS DE ENTRADAS Y SALIDAS
    TRISB = 0x00;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB4 = 1;
    TRISA = 0x00;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA7 = 1;
    PORTB=0x00; //0000 0000 inicializa puerto en cero 
    
//CONFIGURACION DEL TIMER Y PRESCALER    
    CMCON=0x07; //Apaga comparadores para poder usar i/o digital puerto A
    OPTION_REGbits.T0CS=0;//Fuente de Clock Interna
    OPTION_REGbits.PSA=0; //Utiliza Prescaler en TMR0
    
//Prescaler en 111 para que cuente 1 cada 128 pulsos del clock
    OPTION_REGbits.PS2=0;  
    OPTION_REGbits.PS1=0;
    OPTION_REGbits.PS0=1;
    TMR0=0; //inicializa timer1 contador
    INTCONbits.T0IE=1;  //habilita interrupcion por timer0
    INTCONbits.GIE=1;    //habilita interrupciones generales
    
    //int sensor=0;
    uint32_t TIMEOUT =10000; //5800;
 while (1){
     LED1=0;
     LED2=0;
     LED3=0;
     LED4=0;
  /*   while(RECEPTORSENSOR1==0){ //espera a que el echo este en 1
        
        }
        __delay_ms(30);
        while(RECEPTORSENSOR1==1){
        
        }
        __delay_ms(30); */

                    EMISORSENSOR1 = 1; 
                NOP();
                 NOP();
                  NOP();
                   NOP();
                    NOP();
                     NOP();
                      NOP();
                       NOP();
                        NOP();
                         NOP();
                EMISORSENSOR1 = 0; 
               
 /*  while(RECEPTORSENSOR1 != 0); // primero espera a que el echo se ponga en 0
    LED2=1;                              //llama a la funcion que mide distancia 
    while(RECEPTORSENSOR1 == 0);
    LED3=1; */
    TMR0 = 0;
    contador100us = 0;
    
    while(RECEPTORSENSOR1 == 1){
        if(contador100us>TIMEOUT){
            break;
        }
    }
//        contador100us = 0;                     
        if (contador100us < TIMEOUT) {
                    LED4=1;
                    tiempoMedido1 = contador100us;
         }        
        tiempoFinalSensor1 = abs(tiempoMedido1-tiempoMedido1Anterior);
        //
        if( tiempoFinalSensor1>200/*1500*/ && tiempoMedido1Anterior!=0)
        {
            LED1=1;
           // x1=-0.167*(tiempoMedido1/10)+1.167;
        }
        tiempoMedido1Anterior = tiempoMedido1;
     }
}