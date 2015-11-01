/*******************************************************
Protocolos de Transporte
Grado en Ingeniería Telemática
Dpto. Ingeníería de Telecomunicación
Univerisdad de Jaén

Fichero: cliente.c
Versión: 1.1
Fecha: 17/10/2015
Descripción:
	Cliente de eco sencillo TCP mejorado.

Autor: Juan Carlos Cuevas Martínez, Emilio Sánchez Catalán, Noelia Toral Jimenez

*******************************************************/

#include "protocol.h"

int main(int *argc, char *argv[])
{
	//Declaracion de variables
	SOCKET sockfd;
	struct sockaddr_in server_in;
	char buffer_in[2048],comprueba[1024], buffer_out[1024];
	int recibidos=0,enviados=0;
	int fallo_len=0;
	int estado;
	char option;
	int intentos;
	char username[30],destinatario[30],asunto[30],fecha[100],mensaje[1024]="",entrada [1024]=".";
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

    char ipdest[16];
	char default_ip[16]="127.0.0.1";
	system("color 0F");
	//Inicialización Windows sockets
	wVersionRequested=MAKEWORD(1,1);
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
		return(0);

	if(LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		return(0);
	}
	//Fin: Inicialización Windows sockets

	do{
		system("cls");
		
		sockfd=socket(AF_INET,SOCK_STREAM,0);	//Creación del socket

		if(sockfd==INVALID_SOCKET)//Comprobación de posible fallo				
		{
			printf("CLIENTE> ERROR AL CREAR SOCKET\r\n");
			exit(-1);
		}
		else
		{
			printf("CLIENTE> SOCKET CREADO CORRECTAMENTE\r\n");

			printf("CLIENTE> Introduzca la IP destino (pulsar enter para IP por defecto): ");
			gets(ipdest);

			if(strcmp(ipdest,"")==0)	//Caso por defecto
				strcpy(ipdest,default_ip);

			//Parametros iniciales
			server_in.sin_family=AF_INET;	//Familia IP
			server_in.sin_port=htons(TCP_SERVICE_PORT);		//Puerto Que vamos a usar
			server_in.sin_addr.s_addr=inet_addr(ipdest);	//IP del servidor
			
			enviados=0;
			estado=S_HELO;
			intentos=0;
		
			// establece la conexion de transporte
			if(connect(sockfd,(struct sockaddr*)&server_in,sizeof(server_in))==0)
			{
				//Recibo
				recibidos=recv(sockfd,buffer_in,512,0);
				if(recibidos<=0){
					DWORD error=GetLastError();
					if(recibidos<0)
					{
						printf("CLIENTE> Error %d en la recepción de datos\r\n",error);
						estado=S_QUIT;
					}
					else
					{
						printf("CLIENTE> Conexión con el servidor cerrada\r\n");
						estado=S_QUIT;
					}
				}
				buffer_in[recibidos]=0x00;
				//Presentacion del resto de datos recibidos
				printf(buffer_in);
				do{
					//MAQUINA DE ESTADOS
					switch(estado)
					{
					case S_HELO:
						sprintf_s(buffer_out,sizeof(buffer_out),"%s%s",HI,CRLF);
						break;
					case S_USER:
						printf("tu nombre de usuario: ");
						gets(username);
						sprintf_s(buffer_out,sizeof(buffer_out),"MAIL FROM:<%s>%s",username,CRLF);
						break;
					case S_ADDRESSEE:
						printf("Para: ");
						gets(destinatario);
						sprintf_s(buffer_out,sizeof(buffer_out),"RCPT TO:<%s>%s",destinatario,CRLF);
						break;
					case S_DATA:
						sprintf_s(buffer_out,sizeof(buffer_out),"DATA%s",CRLF);
						break;
					case S_MENSAJE:
						
						//Fecha origen
						reloj(fecha);

						//Asunto
						printf("Asunto: ");
						gets(asunto);

						//Cabeceras  del mensaje
						sprintf_s(mensaje,sizeof(mensaje),"Date: %s%sFrom: %s%sTo: %s%sSubject: %s%s",fecha,CRLF,username,CRLF,destinatario,CRLF,asunto,CRLF);
						printf("MENSAJE: \r\n");
						do{
							gets(entrada);
							sprintf_s(mensaje,sizeof(mensaje),"%s%s%s",mensaje,CRLF,entrada);
						}while(strncmp(entrada,".",1)!=0);
						sprintf_s(buffer_out,sizeof(mensaje),"%s%s",mensaje,CRLF);


						break;
					case 6:
						break;
					}
					
					
					//Envio
					
					enviados=send(sockfd,buffer_out,(int)strlen(buffer_out),0);
					
					if (enviados<0){
						DWORD error=GetLastError();
						
							printf("CLIENTE> Error %d en el envio de datos%s",error,CRLF);
							break;
					}

					//Recibo
					recibidos=recv(sockfd,buffer_in,512,0);
					if(recibidos<=0){
						DWORD error=GetLastError();
						if(recibidos<0)
						{
							printf("CLIENTE> Error %d en la recepción de datos\r\n",error);
							estado=S_QUIT;
						}
						else
						{
							printf("CLIENTE> Conexión con el servidor cerrada\r\n");
							estado=S_QUIT;
						}
					}

					//Presentacion  de datos recibidos
					buffer_in[recibidos]=0x00;
					printf(buffer_in);

					//Avance de estado
					if (strncmp(buffer_in,"2",1)==0 || strncmp(buffer_in,"3",1)==0){
						estado++;
					}
					
					
				}while(estado!=S_QUIT);
			
			}
			else	//Error al Conectar
			{
				printf("CLIENTE> ERROR AL CONECTAR CON %s:%d\r\n",ipdest,TCP_SERVICE_PORT);
			}		
			// fin de la conexion de transporte
			closesocket(sockfd);
			
		}

		printf("-----------------------\r\n\r\nCLIENTE> Volver a conectar (S/N)\r\n");
		option=_getche();	//realizar otra conexión

	}while(option!='n' && option!='N');

	
	
	return(0);

}
