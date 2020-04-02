/*!
 * @file uart.h
 * @author Kevin De Cuyper
 * @brief Header file pour la configuration des UART
 */

#ifndef UART_H
#define	UART_H


// initialise l'uart1 en mode 8bits de donn�es, pas de parit�, 1 stop bit
// le param�tre baudrate indique � la fonction le baudrate d�sir�, en Hz
void uart1Init(float baudrate, uint32_t fcy);

// renvoie 1 si il y a une donn�e qui attend d'�tre lue dans le buffer de r�ception, 0 sinon
int16_t uart1RxDataAvailable(void);

// renvoie 1 si le buffer d'�mission n'est pas plein
int16_t uart1TxReady(void);

// envoie un char sur l'uart1. Cette fonction est bloquante. En effet, si le buffer d'�mission est plein,
// elle attendra qu'il se vide pour envoyer son octet
void uart1SendChar(uint8_t data);

// re�oit un char par l'uart1. Cette fonction est bloquante. En effet, si il n'y a rien � lire dans le buffer,
// elle attendra qu'un octet soit recu par l'uart1 pour le lire
uint8_t uart1GetChar(void);

#endif	/* UART_H */

