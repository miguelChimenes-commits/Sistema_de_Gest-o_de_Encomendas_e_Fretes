#include <stdio.h>
#include <stdbool.h>


// preparando arquivo texto ==============

FILE *arquivo_texto;

// structs ===============================
typedef struct{
	
	float peso;
	float distancia;
		
}encomendas;

typedef struct{
	
	float tacha;
	float distancia;
	
}tipo;

typedef struct{
	
	float taxa;
	float ml_distancia;

	
}entrega;


// prototipos ============================
int dialogo(int variavel);
int total_pacotes(int variavel);
float meta_diaria(float variavel);
int registar_pacote(int quantidade_de_pacotes, encomendas pacotes[]);

int main(){
	// varivel inportante ================
	float meta_diaria_v = 0;
	int menu = 0;
	
	// variveel do vetor =================
	int quantidade_de_pacotes = 0;
	int novos_pacotes = 0;
	int registrados = 0;
	
	
	// variaveis Categoria de Entrega ====
	entrega padrao = {0.0f, 1.20f};
	entrega expreca = {15.0f, 1.80f};
	entrega prioritaria = {30.0f, 2.50f};
	
	
	// vetores ===========================
	encomendas pacotes[100];

	
	// codigo principal ==================
	for(;;){
		
		// primeiro dialogo ==========
		menu = dialogo(menu);
		
		
		if(menu == 1){
			if(quantidade_de_pacotes >= 100){
				printf("\nLimite de 100 pacotes atingido.\n");
				continue;
			}
				
				
		//quantos pacotes no total ===========
			novos_pacotes = total_pacotes(0);
			
			if(novos_pacotes == 0){
				break;
			}
			
			if(novos_pacotes > 100 - quantidade_de_pacotes){
				printf(
					"\nSo ha espaco para mais %d pacotes.\n",
					100 - quantidade_de_pacotes
				);
				continue;
			}
			
			registrados = registar_pacote(
				novos_pacotes,
				&pacotes[quantidade_de_pacotes]
			);
			
			quantidade_de_pacotes += registrados;
				
				
		}else if(menu == 2){
			printf(
				"\nTotal de pacotes cadastrados: %d\n",
				quantidade_de_pacotes
			);
			
			for(int i = 0; i < quantidade_de_pacotes; i++){
				printf(
					"Pacote [%d]: %.2f kg | %.2f km\n",
					i + 1,
					pacotes[i].peso,
					pacotes[i].distancia
				);
			}
				
				
					
		}else if(menu == 3){
			if(meta_diaria_v == 0){
				meta_diaria_v = meta_diaria(meta_diaria_v);
			}
			
			printf("\nMeta diaria: R$ %.2f\n", meta_diaria_v);
			printf("Os demais indicadores ainda serao implementados.\n");
				
			
		}else if(menu == 4){
			printf("\nPrograma encerrado.\n");
			break;
				
				
		}
				
						
	}
	return 0;	
}
// funçoes =-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-=

// funçao opçoes ==========================================
int dialogo(int menu){
	int resultado;
	int caractere;
	
	for(;;){
		printf("\n");
		printf("1 - Cadastrar e Processar encomenda;\n");
		printf("2 - Exibir Resumo Estatistico do dia;\n");
		printf("3 - Exibir Indicadores;\n");
		printf("4 - Sair;\n");
		printf("\n");
		
		
		printf("Informe a opcao: ");
		resultado = scanf("%d", &menu);
		
		if(resultado == EOF){
			return 4;
		}
		
		while((caractere = getchar()) != '\n' && caractere != EOF);
		
		if(resultado != 1 || menu < 1 || menu > 4){
			printf("\n[ERRO] Entrada invalida! Digite uma opcao de 1 a 4.\n\n");
			
		}else{
			printf("OK: opcao registrada :\n");
			printf("\n");
			return menu;
		}
	}
}

// funçoes opçao 1 =====================================================================
// funçao meta diaria =====================================
float meta_diaria(float meta_diaria_v){
	int resultado;
	int caractere;
	
	for(;;){
		printf("\n");
		printf("Qual a meta de faturamento diario de hoje? ");
		 
		resultado = scanf("%f", &meta_diaria_v);
		
		if(resultado == EOF){
			return 0;
		}
		
		while((caractere = getchar()) != '\n' && caractere != EOF);
		
		if(resultado != 1 || !(meta_diaria_v > 0)){
			printf("\n[ERRO] Entrada inválida! Digite um valor numérico positivo.\n\n");
			
		}else{
			printf("OK: Meta diaria registrada.\n");
			break;
		}
	}
	
	return meta_diaria_v;
}
	
	
//funçao Cadastrar e Processar encomenda ==================
int total_pacotes(int quantidade_de_pacotes){
	//variaveis da funçao =======
	int resultado;
	int caractere;
	
	for(;;){
		printf("quantos pacotes no tatal :");
		resultado = scanf("%d", &quantidade_de_pacotes);
		
		if(resultado == EOF){
			return 0;
		}
		
		while((caractere = getchar()) != '\n' && caractere != EOF);
		
		if(resultado != 1 || quantidade_de_pacotes <= 0 || quantidade_de_pacotes > 100){
			printf("\n[ERRO] Entrada invalida! Digite um valor entre 1 e 100.\n\n");
		}else{
			return quantidade_de_pacotes;
		}
	}
}


//funçao cadastrar e registar pacote ======================
int registar_pacote(int quantidade_de_pacotes, encomendas pacotes[]){
	FILE *arquivo = fopen("logistica.txt", "a");
	int resultado;
	int caractere;
	int registrados = 0;
	float peso;
	float distancia;
	
	if(arquivo == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		return 0;
	}
	
	for(int i = 0; i < quantidade_de_pacotes; i++){
		for(;;){
			printf("qual o peso do pacote [%d] :", i + 1);
			resultado = scanf("%f", &peso);
			
			if(resultado == EOF){
				fclose(arquivo);
				return registrados;
			}
			
			while((caractere = getchar()) != '\n' && caractere != EOF);
			
			if(resultado != 1 || !(peso > 0)){
				printf("\n[ERRO] Digite um peso maior que zero.\n");
			}else{
				break;
			}
		}
		
		for(;;){
			printf("Qual a distância a ser percorrida em Km:");
			resultado = scanf("%f", &distancia);
			
			if(resultado == EOF){
				fclose(arquivo);
				return registrados;
			}
			
			while((caractere = getchar()) != '\n' && caractere != EOF);
			
			if(resultado != 1 || !(distancia > 0)){
				printf("\n[ERRO] Digite uma distancia maior que zero.\n");
			}else{
				break;
			}
		}
		
		if(fprintf(arquivo, "%.2f|%.2f\n", peso, distancia) < 0){
			printf("\nErro ao escrever no arquivo.\n");
			fclose(arquivo);
			return registrados;
		}
		
		if(fflush(arquivo) == EOF){
			printf("\nErro ao salvar no arquivo.\n");
			fclose(arquivo);
			return registrados;
		}
		
		pacotes[i].peso = peso;
		pacotes[i].distancia = distancia;
		registrados++;
		
		printf("\nPacote cadastrado com sucesso.\n\n");
	}
	
	if(fclose(arquivo) == EOF){
		printf("\nErro ao fechar o arquivo.\n");
	}
		
	return registrados;
}

