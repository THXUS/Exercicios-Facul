#define _XTAL_FREQ 4000000    // Oscilador de 4 MHz

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.intermed.h"

#pragma config FOSC = HS        // Oscilador interno
#pragma config WDT = OFF        // Watchdog Timer desligado
#pragma config MCLRE = OFF      // Master Clear desabilitado

int contador, tempdisp;
char temperature[8];
char stp[8];

float temperatura, tensao;
float setpoint;


void setupADC(void) {
    
    TRISA = 0b00000111;         // Habilita pino A0-A2 como entrada
    
    ADCON1 = 0b00001100;        // pinos analogicos e refer�ncia
    
    ADCON2bits.ADCS = 0b110;    // Clock do AD: Fosc/64
    ADCON2bits.ACQT = 0b100;    // Tempo de aquisi��o: 8 Tad
    ADCON2bits.ADFM = 0b1;      // Formato: � direita
   
    ADCON0 = 0;                 
    ADCON0bits.CHS = 0b0010;     // Seleciona o canal AN2   
    ADCON0bits.ADON = 1;        // Liga o AD
}


void controle(void) {
    
    
    if (temperatura > setpoint + 1) {         	
    PORTCbits.RC5 = 0;  	//Desliga circuito de aquecimento (RC5))
    PORTCbits.RC2 = 1;   	//Liga circuito de ventila��o (RC2)) 
    }        
    if (temperatura < setpoint - 1)  { 
        PORTCbits.RC2 = 0;  	//Desliga circuito de ventila��o (RC2)) 
        PORTCbits.RC5 = 1;
    }
    
    TMR0L = 5; 

    INTCONbits.TMR0IF = 0;
    
}

void aumentarTemperaturaDesejada() {
    
    INTCON3bits.INT1IF = 0;
    
    setpoint += 0.2f;
    
}

void diminuirTemperaturaDesejada() {
    INTCONbits.INT0IF = 0;
    
    setpoint -= 0.2f;
}


void teste() {
    
    ADCON0bits.GO = 1;                    // Inicia a conversao A/D
    while (ADCON0bits.GO) {          // Aguarda fim da conversao
    }
    contador = (ADRESH * 0x100) + ADRESL;			// Transfere valor para variavel
    tensao = ((5 * contador) * 0.001 );		// Calcula tensao real (/ 1024)
    temperatura = 100 * tensao; // calcula temperatura  
    
    comando_lcd(128);
    imprime_lcd("Temp ");
    
    sprintf(temperature, "%3.2f", temperatura);
    
    imprime_lcd(temperature);
    
    comando_lcd(192);
    
    imprime_lcd("stp ");
    
    sprintf(stp, "%3.2f", setpoint);
    
    imprime_lcd(stp);

    controle();

}


void __interrupt() isr(void) {
        
    if(INTCON3bits.INT1IF) {
        aumentarTemperaturaDesejada();
    }
    
    if(INTCONbits.INT0IF) {
        diminuirTemperaturaDesejada();
    }

    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        teste();
    }
}


void main(void) {
    
     TRISD = 0b00000000;         // Habilita porta D como saida dado LCD  
     TRISE = 0b00000000;        // porta E saida controle do LCD
     TRISC = 0b00000000;
     PORTC = 0b00100100;
     
     
     INTCONbits.GIE = 1;
     
    /*Habilita interrupcao externa por rb0 e rb1
     * RB1 SERA A INTERRUPCAO PARA INCREMENTAR
     * RB0 SERA A INTERRUPCAO PARA DECREMENTAR
    */
    INTCON3bits.INT1IE = 1;
    
    INTCONbits.INT0IE = 1;
    

    INTCON3bits.INT1IF = 0;
    INTCONbits.INT0IF = 0;
    
    INTCON2bits.INTEDG1 = 1;

    comando_lcd(0b00111100);
    comando_lcd(0b00001100);
        
    setpoint = 32.00;
    
    setupADC();

    limpa_lcd( );


    INTCONbits.TMR0IE = 1;
    
    T0CON = 0B11000111;
     
    TMR0L = 5;
while(1) {}

    return;
}
