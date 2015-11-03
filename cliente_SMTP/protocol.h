#ifndef protocolostpte_practicas_headerfile
#define protocolostpte_practicas_headerfile
#endif

#include <stdio.h>
#include <winsock.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
//FUNCIONES
int check(char pass[],char user[]);
// COMANDOS DE APLICACION
#define SC "USER"  // SOLICITUD DE CONEXION USER usuario 
#define PW "PASS"  // Password del usuario  PASS password
#define SD  "QUIT"  // Finalizacion de la conexion de aplicacion
#define HI "HELO"	//Saludo inicial
#define RS "RSET"	//Reseteo de estado de sesion
// RESPUESTAS A COMANDOS DE APLICACION
#define OK  "200"
#define ER  "500"

//Boolean
#define TRUE 1
#define FALSE 0
//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_RSET -1
#define S_HELO 0
#define S_USER 1
#define S_ADDRESSEE 2
#define S_DATA 3
#define S_MENSAJE 4
#define S_QUIT 5

//PUERTO DEL SERVICIO
#define TCP_SERVICE_PORT	25
void reloj(char fecha[]);
void head();
// NOMBRE Y PASSWORD AUTORIZADOS
#define USER		"alumno"
#define PASSWORD	"asd"