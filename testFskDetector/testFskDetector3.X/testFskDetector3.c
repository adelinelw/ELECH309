/*
 * File:   main.c
 * Author: M. Os�e
 *
 * V1.0		09/10/2013
 */


#include "xc.h"
#include "init.h"
#include "../fskDetector/FskDetector.h"
#include "uart1.h"
#include <stdio.h>


int16_t parity(int16_t data) {
    int16_t cnt = 0;
    int16_t i;

    for (i=0; i<10; i++) {
        cnt += (data >> i) & 1;
    }
    return (cnt%2);
}


int main(void) {
    int16_t messageRecu;    // message d�cod� par FskDetector()
    int16_t messageEmis;    // message initial
	int16_t trame;          // trame � fournir � FskDetector()
    int16_t bitNb, sampNb;		// index de boucle
	int16_t detLow, detHigh;	// sorties des d�tecteurs


    oscillatorInit();
    RPOR3bits.RP7R = 3;     // connecte U1TX � RP5
    RPINR18bits.U1RXR = 6;  // connecte U1RX � RP4
    uart1Init(115200, 40000000);
    
    // on attend de recevoir un caract�re pour d�marrer
    uart1GetChar();
    printf("D�but du test\n");
    // On va "envoyer" tous les messages possibles
    for (messageEmis = 0; messageEmis < 0x3FF; messageEmis++) {
        // On commence par cr�er la trame
        trame = messageEmis << 2;   // on place le message au bon endroit
        // on donne la bonne valeur au bit de parit�
        if (parity(messageEmis) == 1) {
            trame |= 2;
        }
        // Remarque : pour les start/stop bit, il n'y a rien � faire puisqu'ils valent 0
        
        // on envoie les 13 bits de la trame de poids faible en commencant par le MSB
        for (bitNb=12; bitNb>=0; bitNb--) {
            if (trame & (1<<bitNb)) {
                detLow = 0;
                detHigh = 1;
            } else {
                detLow = 1;
                detHigh = 0;
            }
            for(sampNb=0; sampNb<OSR; sampNb++){
                messageRecu = fskDetector(detLow, detHigh);
            }
            if ( (messageRecu != 0) && (messageRecu != messageEmis) ) {
                printf("message �mis : %X\n", messageEmis);
                printf("Message re�u : %X\n", messageRecu);
            }
        }
    }
    printf("Test termin�\n");
    while(1);
    return (0);
}
