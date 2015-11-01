#include "protocol.h"

void reloj(char fecha[]){

	time_t t;
	struct tm *tm;
	char fechayhora[100];
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%a, %d %b %Y %X %z", tm);
	strcpy(fecha,fechayhora);


}