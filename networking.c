
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>


/**
*@brief Affiche un message sur la sortie d'erreur standard.
*
*@param char* message Le message à afficher sur la sortie d'erreur.
*
*@ return int retourne le code d'erreur -1.
*
*/

int die(const char* message)
{
	fputs(message, stderr );
	return -1;
}


/**
*@brief Crée une socket en mode flux attachée à une adresse IPV4.
*
*@param char* hostname Le nom de la machine hôte (NULL pour localhost INADDR_ANY).
*@param unsigned short port Le port à utiliser (0 pour laisser le noyau choisir).
*@param char* protocole Le nom du protocole à utiliser.
*
*@return int Une socket en mode flux attachée à l'adresse IPV4 correspondant aux paramètres.
*
*/
int cree_socket_stream(const char* hostname, unsigned short port, const char* protocole)
{
	int sock;
	struct sockaddr_in adresse;
	int taille = sizeof(struct sockaddr_in);
	struct hostent* hostentry;
	struct protoent* protoentry;

	
	memset(&adresse, 0, taille);
	adresse.sin_family = AF_INET;


	if(hostname == NULL){
		adresse.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	else { 
		if((hostentry = gethostbyname(hostname)) == NULL){
			die("gethostbyname");
		}
		
		adresse.sin_addr.s_addr = ((struct in_addr*)(hostentry->h_addr))->s_addr;
	}


	if((protoentry = getprotobyname(protocole)) == NULL){
		die("getprotobyname");
	}


	adresse.sin_port = htons(port);


	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		die("socket");
	}

	if((bind(sock, (struct sockaddr*)&adresse, taille)) < 0) {
		close(sock);
		die("bind");
	}

	return sock;
}

/**
*@brief Affiche l'adresse IP est le port utilisé par une socket internet.
*
*@param int sock La socket dont on veut afficher l'adresse.
*
*@return int EXIT_SUCCES en cas de succès, -1 sinon.
*
*/
int afficher_adresse_socket(int sock)
{
	struct sockaddr_in adresse;
	socklen_t taille;

	taille = sizeof(struct sockaddr_in);

	if((getsockname(sock, (struct sockaddr*)&adresse, &taille)) < 0){
		die("getsockname");
	}

	fprintf(stdout, "IP = %s, Port = %u \n", inet_ntoa(adresse.sin_addr), ntohs(adresse.sin_port));

	return EXIT_SUCCESS;
}

