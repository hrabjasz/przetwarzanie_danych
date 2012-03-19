#define program_tcp
#ifdef program_tcp
#include <stdio.h>

struct daneTCP{
  unsigned int id;
	unsigned char SOURCE_IP[4];
	unsigned char TEST_IP[4];
	unsigned char TTL;
};

void odczytLog(FILE *log_rd,struct daneTCP *str);
void zapisWynik(struct daneTCP *str);
int pobierzDane(FILE *plik,struct daneTCP *wsk);
void pobierzIP_SOURCE(FILE *plik,struct daneTCP *wsk);
void pobierzIP_TEST(FILE *plik,struct daneTCP *wsk);
void pobierzTTL(FILE *plik,struct daneTCP *wsk);
void kopiujStr(struct daneTCP *source,struct daneTCP *dest,int x);
void wypiszStr(struct daneTCP *wsk,int x);
int sprawdzStr(struct daneTCP *zap,struct daneTCP *baza,int z);

#endif