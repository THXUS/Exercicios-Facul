#pragma config FOSC = HS        

#pragma config WDT = OFF        

#pragma config MCLRE = ON  



#define _XTAL_FREQ 4000000


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.intermed.h";

char temperature[8];

float temperatura; 



void imprimeTemperaturaAtual() {
    
    limpa_lcd( );

    __delay_ms(1000);

    comando_lcd(128);

    imprime_lcd("Temperatura");

    comando_lcd(192);

    sprintf(temperature, "%3.2f", temperatura);

    imprime_lcd(temperature);   

    __delay_ms(1000);
}

int isTemperaturaNoLimite() {
    return temperatura >= 30.0 && temperatura <= 40.0 ? 1 : 0;
}


void avisaLimiteMinimo() {
    
    limpa_lcd( );

    __delay_ms(1000);

    comando_lcd(128);

    imprime_lcd("Limite");

    comando_lcd(192);

    imprime_lcd("Minimo");

    __delay_ms(1000);
    
}


void avisaLimiteMaximo() {
    
    limpa_lcd( );

    __delay_ms(1000);

    comando_lcd(128);

    imprime_lcd("Limite");

    comando_lcd(192);

    imprime_lcd("Maximo");

    __delay_ms(1000);
    
}


void checarTemperatura() {
    
    if(isTemperaturaNoLimite()) {
        
        imprimeTemperaturaAtual();
       
    }else {
        
        if (temperatura > 40) {
            avisaLimiteMaximo();
        }
        
        if(temperatura < 30.0) {
            
            avisaLimiteMinimo();
          
        }
        
         temperatura = 30.0;
     
    }
    
  
    TMR0L = 5; 

    INTCONbits.TMR0IF = 0; 
    
}
    
   
void aumentarTemperatura() {
    
    INTCON3bits.INT1IF = 0;
    
    temperatura += 0.5f;
    
}

void diminuirTemperatura() {
    INTCONbits.INT0IF = 0;
    
    temperatura -= 0.5f;
}


void __interrupt() isr(void) {
    
    
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        checarTemperatura();
    }
    
    
    if(INTCON3bits.INT1IF) {
        aumentarTemperatura();
    }
    
    if(INTCONbits.INT0IF) {
        diminuirTemperatura();
    }
     
}



int main() {
        
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 15;

    INTCONbits.GIE = 1;

    /*Habilita interrupção externa por rb0 e rb1
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

    
    temperatura = 30.0;
    
    PORTAbits.RA4 = 0; 

    INTCONbits.GIE =1;
    
    INTCONbits.TMR0IE = 1;
    
    T0CON = 0B11000111;
     
    TMR0L = 5;
     
    while (1) {

    }
    
}
