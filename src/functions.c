#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zapisWynik(struct daneTCP *str)
{
  FILE *plik;
	int x=0;
	plik = fopen("log_1.txt","a");
	while(x == str[x].id)
	{
		fprintf(plik,"%d.%d.%d.%d\t%d\n",str[x].SOURCE_IP[0],str[x].SOURCE_IP[1],str[x].SOURCE_IP[2],str[x].SOURCE_IP[3],str[x].TTL);
		x++;
	}
	fclose(plik);
}
void odczytLog(FILE *log_rd,struct daneTCP *str)
{
	struct daneTCP strBuf;
	int x=1;
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
		
}

int pobierzDane(FILE *plik, struct daneTCP *wsk)
{
	int pozycja;
	int koniec;
	pobierzIP_SOURCE(plik,wsk);
	pobierzIP_TEST(plik,wsk);
	pobierzTTL(plik,wsk);
	pozycja = ftell(plik);
	fseek(plik,0,SEEK_END);
	koniec = ftell(plik);
	if(pozycja > (koniec- 19))
		return 1;
	else
		fseek(plik,pozycja,SEEK_SET);
	return 0;
}

void pobierzIP_SOURCE(FILE *plik, struct daneTCP *wsk)
{
	int x,y,z;

	char sBuf[10];
	for(y=0;y<4;y++)
		{
			sBuf[0] = '0';
			x = 0;
			while(sBuf[x-1] != '.' && sBuf[x-1] != '\t')
			{
				sBuf[x] = fgetc(plik); 
				x++;
			}
			z = atoi(sBuf);
			wsk->SOURCE_IP[y] = z;
		}
}

void pobierzIP_TEST(FILE *plik, struct daneTCP *wsk)
{
	int x,y;
	char sBuf[10];
	for(y=0;y<4;y++)
		{
			sBuf[0] = '0';
			x = 0;
			while(sBuf[x-1] != '.' && sBuf[x-1] != '\t')
			{
				sBuf[x] = fgetc(plik); 
				x++;
			}
			wsk->TEST_IP[y] = atoi(sBuf);
		}
}

void pobierzTTL(FILE *plik, struct daneTCP *wsk)
{
	int x;
			fscanf(plik,"%d",&x);
			wsk->TTL = x;
}

void kopiujStr(struct daneTCP *source,struct daneTCP *dest, int x)
{
	int z;
	dest[x].id = x;
	for(z=0;z<4;z++)
		dest[x].SOURCE_IP[z] = source->SOURCE_IP[z];
	for(z=0;z<4;z++)
		dest[x].TEST_IP[z] = source->TEST_IP[z];
	dest[x].TTL = source->TTL;
}

void wypiszStr(struct daneTCP *wsk,int x)
{
	printf("IP_SOURCE: %d.%d.%d.%d ",wsk[x].SOURCE_IP[0],wsk[x].SOURCE_IP[1],wsk[x].SOURCE_IP[2],wsk[x].SOURCE_IP[3]);
	printf("IP_TEST:%d.%d.%d.%d  ", wsk[x].TEST_IP[0], wsk[x].TEST_IP[1],wsk[x].TEST_IP[2],wsk[x].TEST_IP[3]);
	printf("TTL: %d \n",wsk[x].TTL);
}

int sprawdzStr(struct daneTCP *zap,struct daneTCP *baza,int x)
{
	int z;
	for(z=0;z<x;z++)
	{
		if(baza[z].SOURCE_IP[0] == zap->SOURCE_IP[0] && baza[z].SOURCE_IP[1] == zap->SOURCE_IP[1] && baza[z].SOURCE_IP[2] == zap->SOURCE_IP[2] &&baza[z].SOURCE_IP[3] == zap->SOURCE_IP[3])
		{
			if(zap->TTL > baza[z].TTL)
				baza[z].TTL = zap->TTL;
			return x;
		}
	}
	return -1;
}