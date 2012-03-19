#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main(int argc, int *argv[])
{
  FILE *log_rd,log_wr;
	char cNazwa[200];
	struct daneTCP *str=NULL,strBuf;
	int x=1;

	printf("Podaj sciezke pliku:");
	scanf("%s",&cNazwa);
	if(strlen(cNazwa) < 3 ) strcpy(cNazwa,"log.txt");
	else{
		if(cNazwa[strlen(cNazwa)-1] == '/')
			strcat(cNazwa,"log.txt");
		else
			strcat(cNazwa,"/log.txt");
	}

	log_rd = fopen(cNazwa,"rb");
	
	if(log_rd == NULL){ 
		perror("Nie udalo sie otworzyc pliku:");
		exit(1);
	}
	str = malloc(sizeof(strBuf)+x);
	/// Pobieranie danych z log.txt i sprawdzenie TLL
		while(!pobierzDane(log_rd,&strBuf))
		{
			if((sprawdzStr(&strBuf,str,x-1)) == -1)
			{
				kopiujStr(&strBuf,str,x-1);
				wypiszStr(str,x-1);
				x++;
				str = realloc(str,sizeof(strBuf)*(x+1));				
			}		
		}	

	fclose(log_rd);
	zapisWynik(str);

free(str);
system("pause");
	return 0;
}