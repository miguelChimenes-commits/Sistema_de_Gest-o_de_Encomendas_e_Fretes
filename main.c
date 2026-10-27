#include <stdio.h>
#define MAXIMO_ENCOMENDAS 100

typedef struct{
	int ID;
	int categoria;
	int cupom;
	float valorBruto;
	float valorFinal;
	float peso;
	float distancia;
	char status[12];
}encomendas;


encomendas encomenda[MAXIMO_ENCOMENDAS];

int main() {
	
}
