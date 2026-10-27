#include <stdio.h>
#define MAXIMO_ENCOMENDAS 100

typedef struct
{
    int ID;
    int categoria;
    int opcao_cupom;
    double valorBruto;
    double valorFinal;
    double peso;
    double distancia;
    char status[12];
} encomendas;

encomendas encomenda[MAXIMO_ENCOMENDAS];
double frete_bruto(double dist, double peso, int opcao, int cupom);

int main()
{
    int ij = 0;

    char data_exportacao[3];
    int quantidade_de_pacotes = 0;
    int tipo_de_entrega = 0;
    double desc_cupom = 0;

    char escolha;
    double meta_diaria;

    int total_encomendas = 0;
    double faturamento_total = 0.0;
    double soma_pesos = 0.0;
    double soma_distancias = 0.0;
    double maior_frete = 0.0; 
    double menor_frete = 999999.0;
    int total_isencoes = 0;

    int qtd_padrao = 0;
    int qtd_expressa = 0;
    int qtd_prioritaria = 0;

    for (;;)
    {
        printf("Qual a meta de faturamento diária? ");

        if (scanf("%lf", &meta_diaria) != 1 || meta_diaria < 0)
        {
            printf("\n[ERRO] Entrada inválida! Digite um valor numérico positivo.\n\n");
            while (getchar() != '\n');
                
        }
        else
        {
            printf("-> OK: Meta diária registrada.\n");
            break;
        }

        for (;;)
        {

            printf("LOGTECH SGEF - VERSAO 2.0\n");
            printf("=====================================================\n");
            printf("1-Cadastrar e Processar Encomenda\n");
            printf("2-Listar Encomendas Registradas\n");
            printf("3-Buscar Encomendas por ID\n");
            printf("4-Cancelar Encomenda\n");
            printf("5-Exibir Resumo Estatistico e Indicadores\n");
            printf("6-Exportar Relatorio Diario (.txt)\n");
            printf("7-Limpar/Reiniciar Historico do Dia\n");
            printf("8-Sair\n");
            printf("=====================================================\n");
            printf("Escolha uma opcao: ");

            scanf(" %c", &escolha);
        }

        switch (escolha)
        {

        case 1:

            for (;;)
            {
                printf("Qual o peso de cada pacote em Kg? ");
                if (scanf("%lf", &encomenda[ij].peso) != 1 || encomenda[ij].peso <= 0)
                {
                    printf("\n[ERRO] Peso inválido! O peso deve ser maior que zero.\n\n");
                    while (getchar() != '\n');
                        
                }
                else
                {
                    printf("-> OK: Peso registrado.\n\n");
                    break;
                }
            }

            for (;;)
            {
                printf("Quantos pacotes no total? ");
                if (scanf("%d", &quantidade_de_pacotes) != 1 || quantidade_de_pacotes > 100 || quantidade_de_pacotes <= 0)
                {
                    printf("\n[ERRO] Quantidade inválida! Informe um valor limite entre 1 e 100.\n\n");
                    while (getchar() != '\n')
                        ;
                }
                else
                {
                    printf("-> OK: Número de pacotes registrado.\n\n");
                    break;
                }
            }

            for (;;)
            {
                printf("Qual a distância a ser percorrida em Km? ");
                if (scanf("%lf", &encomenda[ij].distancia) != 1 || encomenda[ij].distancia <= 0)
                {
                    printf("\n[ERRO] Distância inválida! Informe um valor maior que zero.\n\n");
                    while (getchar() != '\n')
                        ;
                }
                else
                {
                    printf("-> OK: Distância registrada.\n\n");
                    break;
                }
            }

            printf("================================================================================\n");
            printf("Opção | Categoria de Entrega   | Taxa Adicional | Multiplicador de Distância\n");
            printf("1     | Padrão                 | R$ 0,00        | R$ 1,20/km\n");
            printf("2     | Expressa               | R$ 15,00       | R$ 1,80/km\n");
            printf("3     | Prioritária            | R$ 30,00       | R$ 2,50/km\n");
            printf("================================================================================\n");

            for (;;)
            {
                printf("Qual opção deseja? ");
                if (scanf("%d", &tipo_de_entrega) != 1)
                {
                    printf("\n[ERRO] Opção inválida! Digite um número de 1 a 3.\n\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (tipo_de_entrega == 1)
                {
                    printf("-> OK: Entrega do tipo Padrão selecionada.\n");
                    qtd_padrao++;
                    break;
                }
                else if (tipo_de_entrega == 2)
                {
                    printf("-> OK: Entrega do tipo Expressa selecionada.\n");
                    qtd_expressa++;
                    break;
                }
                else if (tipo_de_entrega == 3)
                {
                    printf("-> OK: Entrega do tipo Prioritária selecionada.\n");
                    qtd_prioritaria++;
                    break;
                }
                else
                {
                    printf("\n[ERRO] Opção de entrega inválida! Escolha 1, 2 ou 3.\n\n");
                }
            }

            printf("\n");

            printf("\n=============================================================================\n");
            printf(" CUPOM | NOME DO CUPOM |   REGRA\n");
            printf("=============================================================================\n");
            printf("[1020] |   LOG10       | 10%% de desconto.\n");
            printf("[2030] | DESCONTO15    | R15,00 de desconto (não pode ser menor que R$ 0,00 )\n");
            printf("-----------------------------------------------------------------------------\n");

            for (;;)
            {

                printf("CUPOM: ");
                if (scanf("%d", &encomenda[ij].opcao_cupom) != 1 || &encomenda[ij].opcao_cupom <= 0)
                {
                    printf("\n[ERRO] cupom inválido!.\n\n");
                    while (getchar() != '\n')
                        ;
                }
                else if (encomenda[ij].opcao_cupom == 1020 || encomenda[ij].opcao_cupom == 2030)
                {
                    printf("-> OK: cupom aplicado.\n\n");
                    break;
                }
                else
                {

                    printf("\n[ERRO] cupom inválido!.\n\n");
                }
            }

            double saida = frete_bruto(encomenda[ij].distancia, encomenda[ij].peso, tipo_de_entrega, encomenda[ij].opcao_cupom);

            if (encomenda[ij].opcao_cupom == 1020)
            {

                desc_cupom = saida * 0.1;
                desc_cupom = desc_cupom + saida;
            }
            else if (encomenda[ij].opcao_cupom == 2030)
            {

                desc_cupom = saida - 15;
            }

            printf("\n>> Valor do frete bruto calculado: R$ %.2f <<\n", desc_cupom);

            total_encomendas = total_encomendas + 1;
            faturamento_total = faturamento_total + saida;
            soma_pesos = soma_pesos + encomenda[ij].peso;
            soma_distancias = soma_distancias + encomenda[ij].distancia;

            if (saida == 0.0)
            {
                total_isencoes = total_isencoes + 1;
            }
            if (saida > maior_frete)
            {
                maior_frete = saida;
            }
            if (saida < menor_frete)
            {
                menor_frete = saida;
            }

            break;

        case 2:

            if (total_encomendas == 0)
            {
                printf("\n[ALERTA] Nenhuma encomenda cadastrada ainda!\n");
            }
            else
            {
                printf("\n=========================================\n");
                printf("     LOGTECH SGEF - VERSAO 2.0     \n");
                printf("=========================================\n");
                printf("Total de Encomendas Processadas : %d\n", total_encomendas);
                printf("Total de Encomendas Ativas      : %d\n", total_encomendas - total_isencoes);
                printf("Total de Encomendas Canceladas  : %d\n", 0); // Placeholder, replace with actual value if available
                printf("-----------------------------------------\n");
                printf("Faturamento Total em Fretes     : R$ %.2f\n", faturamento_total);
                printf("Media de peso (Encomendas Ativas): %.2f kg\n", (total_encomendas - total_isencoes) > 0 ? soma_pesos / (total_encomendas - total_isencoes) : 0);
                printf("Media de distancia (Ativas)     : %.2f km\n", (total_encomendas - total_isencoes) > 0 ? soma_distancias / (total_encomendas - total_isencoes) : 0);
                printf("-----------------------------------------\n");
                printf("Maior frete individual cobrado  : R$ %.2f\n", maior_frete);
                printf("Menor frete individual cobrado  : R$ %.2f\n", menor_frete);
                printf("Total de isencoes (Frete Gratis): %d encomendas\n", total_isencoes);
                printf("=========================================\n");
                break;

            case 3:

                if (total_encomendas == 0)
                {
                    printf("\n[ALERTA] Nenhuma encomenda cadastrada ainda!\n");
                }
                else
                {

                    char mais_usada[] = "Nenhuma";
                    if (qtd_padrao >= qtd_expressa && qtd_padrao >= qtd_prioritaria && total_encomendas > 0)
                    {
                    }

                    printf("=========================================\n");
                    printf("     LOGTECH LOGISTICS - RELATORIO DIARIO\n");
                    printf("=========================================\n");
                    printf("Data da Exportacao              : %s\n", data_exportacao);
                    printf("Total de Encomendas Processadas : %d\n", total_encomendas);
                    printf("Total de Encomendas Ativas      : %d\n", total_encomendas - total_isencoes);
                    printf("Total de Encomendas Canceladas  : %d\n", 0); // Placeholder, replace with actual value if available
                    printf("-----------------------------------------\n");
                    printf("Faturamento Total em Fretes     : R$ %.2f\n", faturamento_total);
                    printf("Media de Peso (Encomendas Ativas): %.2f kg\n", (total_encomendas - total_isencoes) > 0 ? soma_pesos / (total_encomendas - total_isencoes) : 0);
                    printf("Media de Distancia (Ativas)     : %.2f km\n", (total_encomendas - total_isencoes) > 0 ? soma_distancias / (total_encomendas - total_isencoes) : 0);
                    printf("-----------------------------------------\n");
                    printf("Maior Frete Individual Cobrado  : R$ %.2f\n", maior_frete);
                    printf("Menor Frete Individual Cobrado  : R$ %.2f\n", menor_frete);
                    printf("Total de Isencoes (Frete Gratis): %d encomenda(s)\n", total_isencoes);
                    printf("-----------------------------------------\n");
                    printf("   INDICADORES E ALERTAS OPERACIONAIS    \n");
                    printf("-----------------------------------------\n");

                    break;

                case 4:

                    printf("\nObrigado por acessar nosso sistema!\n");
                    break;

                default:
                    printf("\n[ERRO] Opção inválida. Tente novamente.\n");
                    while (getchar() != '\n')
                        ;
                }
            }
        }
    }

    return 0;
}

double frete_bruto(double dist, double peso, int opcao, int cupom)
{
    double multiplicadorDist = 0.0;
    double taxaAdd = 0.0;
    double vPeso = 0.0;
    double desc_cupom;

    switch (opcao)
    {
    case 1:
        taxaAdd = 0.00;
        multiplicadorDist = 1.20;
        break;
    case 2:
        taxaAdd = 15.00;
        multiplicadorDist = 1.80;
        break;
    case 3:
        taxaAdd = 30.00;
        multiplicadorDist = 2.50;
    }

    if (peso > 5.00)
    {
        vPeso = 3.50;
    }
    else
    {
        vPeso = 2.00;
    }

    double calculo_Frete_Bruto = (dist * multiplicadorDist) + (peso * vPeso) + taxaAdd;

    return calculo_Frete_Bruto;
}
