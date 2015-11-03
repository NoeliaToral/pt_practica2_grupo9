#include "protocol.h"

void reloj(char fecha[]){
	TIME_ZONE_INFORMATION tziOld;
	DWORD dwRet;
	time_t t;
	struct tm *tm;
	char fechayhora[1024];
	dwRet = GetTimeZoneInformation(&tziOld);

	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora,1024, "%a, %d %b %Y %X", tm);
	sprintf_s(fechayhora,sizeof(fechayhora),"%s %d",fechayhora,dwRet);
	strcpy(fecha,fechayhora);
}
void head(){
	printf("\t\t    +---------------------------------+\r\n");
	printf("\t\t    |Bienvenido a nuestro cliente SMTP|\r\n");
	printf("\t\t    +---------------------------------+\r\n\n");
}
