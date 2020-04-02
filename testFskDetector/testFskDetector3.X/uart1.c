#include <xc.h>
#include "init.h"
#include "uart1.h"


#define ABS(x) ((x) < 0 ? - (x) : (x))

void uart1Init(float baudrate, uint32_t fcy) {
	float tmp;

    U1MODEbits.UARTEN = 0;      // on d�sactive l'UART avant de l configurer (au cas o�)
    U1MODE = 0;                 // on veut fonctionner en 8N1
    
    // on va essayer d'utiliser le mode "standard" pour le baudrate
    tmp = fcy/(16*baudrate) - 1;    // on calcule la valeur exacte � placer dans le UxBRG
    if (tmp > 0xFFFF) {             // on v�rifie que le baudrate n'est pas trop lent
        while(1);                   // pour le dsPIC
    }
    U1BRG = (unsigned int)(tmp+0.5);        // on assigne la valeur calcul�e, en arrondissant
    tmp = fcy/(16*(float)(U1BRG + 1));      // on calcule le baudrate r�el correspondant
    /* on v�rifie si l'erreur d'arrondi n'est pas trop grande.
     * L'erreur max admissible est 2%. En effet, une trame comprend 10 bits.
     * => � la fin de la trame, le d�calage est alors de 20% d'un bit */
    if (ABS(tmp-baudrate) < baudrate/50) {
        U1MODEbits.BRGH = 0;
    }
    else {      // sinon, on passe en mode "high speed"
        U1MODEbits.BRGH = 1;
        tmp = fcy/(4*baudrate) - 1;
        U1BRG = (unsigned int)(tmp+0.5);
        // on v�rifie si l'erreur n'est pas trop grande
        tmp = fcy/(4*(float)(U1BRG + 1)); 
        if (ABS(tmp-baudrate) < baudrate/50) {
            while(1);
        }
    }
    U1MODEbits.UARTEN = 1;  // on active l'UART
    U1STAbits.UTXEN = 1;    // on active l'�mission (Attention, cela active aussi U1TXIF)
}


void uart1SendChar(uint8_t data) {
	while(U1STAbits.UTXBF);
	U1TXREG = data;
}


uint8_t uart1GetChar(void) {
	while(U1STAbits.URXDA == 0);
	return (U1RXREG);
}


int16_t uart1RxDataAvailable(void) {
	return (U1STAbits.URXDA);
}


int16_t uart1TxReady(void) {
	return !U1STAbits.UTXBF;
}
