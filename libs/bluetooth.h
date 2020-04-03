//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//	bluetooth.h, cr�� le 13/01/2013 par M. Os�e												//
//																						//
//	Cette librairie de fonction interace le dsPIC avec le module Bluetooth AMB2300		//
//	Elle est �crite pour la famille dsPIC33FJxxMCx02/04									//
//	Elle utilise le module UART2														//
//																						//
//	V1.0 : cr�ation																		//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H


	#define BT_NO_ERR						 0
	#define BT_HOST_NOT_CONNECTED_ERR		-1
	#define BT_TX_BUFFER_FULL				-2
	#define BT_RX_BUFFER_EMPTY				-3
	#define BT_HARDWARE_ERR					-4


	// defines wireless module reset pin
	#define LAT_AMB2300_RESET		_LATB2
	#define TRIS_AMB2300_RESET		_TRISB2


	// Configure l'UART2 et le PPS pour pouvoir communiquer avec le module AMB2300
	int16_t btInit(void);

	// Donne la place encore disponible dans le buffer d'�mission, en octets
	// 2 cas possibles :
	//	- Aucun h�te n'est connect� : la fonction retourne RADIO_HOST_NOT_CONNECTED_ERR
	//	- Sinon, la fonction retourne le nombre d'octets qui peuvent encore �tre �crit dans le buffer d'�mission
	int16_t btGetTxBufferSpace(void);

	// Ecrit des donn�es dans le buffer d'�mission
	// Le 1er param�tre est un pointeur vers les donn�es � envoyer, consid�r�es comme un vecteur de char
	// le 2�me param�tre est le nombre de char � �crire
	// 3 cas possibles :
	//	- Aucun h�te n'est connect� : la fonction ne fait rien et retourne RADIO_HOST_NOT_CONNECTED_ERR
	//	- un h�te est connect�, mais il n'y a pas assez de place dans le buffer d'�mission : la fonction ne fait rien et retourne RADIO_TX_BUFFER_FULL
	//	- sinon (cas nominal) : la fonction copie les nb octets point16_t�s par data dans le buffer d'�mission et retourne RADIO_NO_ERR.
	int16_t btSendData(int8_t* data, int nb);

	// Donne le nombre d'octets encore � traiter dans le buffer de r�ception
	// 2 cas possibles :
	//	- Aucun h�te n'est connect� : la fonction retourne RADIO_HOST_NOT_CONNECTED_ERR
	//	- Sinon, la fonction retourne le nombre d'octets disponibles dans le buffer de r�ception
	int16_t btGetRxBufferSpace(void);

	// Lit des donn�es dans le buffer de r�ception
	// Le 1er param�tre est un pointeur vers la variable � remplir avec les donn�es (consid�r�e comme un vecteur de char)
	// le 2�me param�tre est le nombre de char � lire
	// 3 cas possibles :
	//	- Aucun h�te n'est connect� : la fonction ne fait rien et retourne RADIO_HOST_NOT_CONNECTED_ERR
	//	- un h�te est connect�, mais il n'y a pas assez d'octets � lire dans le buffer de r�ception : la fonction ne fait rien
	//	  et retourne RADIO_RX_BUFFER_EMPTY
	//	- sinon (cas nominal) : la fonction copie nb octets du le buffer de r�ception dans la variable point�e par data et retourne RADIO_NO_ERR.
	int16_t btGetData(int8_t *data, int nb);


#endif
