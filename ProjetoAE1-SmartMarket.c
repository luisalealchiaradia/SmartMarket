// Projeto: SMART MARKET - Sistema de Gestao e Analise de Supermercado.
// Descricao: Sistema completo para gerenciamento de produtos, estoque,
//            calculos financeiros e analise de desempenho de supermercado
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define MAX_NOME 50
#define MAX_CATEGORIA 30
#define MESES 12

// Struct principal, representa cada produto do supermercado com seus dados essenciais.
typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char categoria[MAX_CATEGORIA];
    int quantidade;
    int estoque_minimo;
    float preco_custo;
    float preco_venda;
    float lucro_unitario;
    int ativo;
} Produto;




Produto estoque[MAX_PRODUTOS];  // Vetor com capacidade para 100 produtos
int total_cadastrados = 0;      // Contador de produtos cadastrados
float lucros_mensais[MESES];    // Vetor para armazenar lucros de cada mes
char nomes_meses[12][15] = {    // Nomes dos meses para relatorios
    "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
    "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
};


//Declaracoes de funcoes
void menu_principal();
void gerenciar_produtos();
void controle_estoque();
void calculos_financeiros();
void relatorios_financeiros();
void analise_produtos();
void analise_anual();
void dashboard();

void inserir_produto();
void listar_produtos();
void editar_produto();
void excluir_produto();
void pesquisar_produto();
void atualizar_quantidade();
void alerta_estoque_baixo();
void relatorio_reposicao();

void limpar_tela();
void pausar();
void inicializar_sistema();
void selecionar_categoria(char *destino);

// Funcao auxiliar para limpar o buffer de forma portatil
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    inicializar_sistema();
    menu_principal();
    return 0;
}

// Inicializa o sistema: zera lucros mensais e marca todos produtos como inativos
void inicializar_sistema() {
    int i;

    for(i = 0; i < MESES; i++) {
        lucros_mensais[i] = 0.0;
    }

    for(i = 0; i < MAX_PRODUTOS; i++) {
        estoque[i].ativo = 0;
    }
}


// Limpa a tela do console (compativel com Windows e Linux)
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Pausa a execucao ate o usuario pressionar Enter
void pausar() {
    printf("\n   Pressione Enter para continuar...");
    limpar_buffer();
    getchar();
}


// Menu principal com opcoes de acesso a 7 funcionalidades do sistema
// Usa do-while para manter o programa em execucao ate sair (opcao 0)
void menu_principal() {
    int opcao;
    int valido;

    do {
        limpar_tela();
        printf("   ====================================================\n");
        printf("   ||        SISTEMA DE GESTAO DE SUPERMERCADO       ||\n");
        printf("   ====================================================\n\n");
        printf("   1. Gerenciamento de Produtos\n");
        printf("   2. Controle de Estoque\n");
        printf("   3. Calculos de Precos e Lucros\n");
        printf("   4. Relatorios Financeiros Gerais\n");
        printf("   5. Analise de Produtos (Destaques)\n");
        printf("   6. Analise de Desempenho Anual\n");
        printf("   7. Dashboard Gerencial\n");
        printf("   0. Sair do Sistema\n\n");
        printf("   ----------------------------------------------------\n");

        valido = 0;
        do {
            printf("   Escolha uma opcao: ");

            if(scanf("%d", &opcao) != 1) {
                limpar_buffer();
                printf("   ERRO: Digite um numero valido (0 a 7)!\n");
                continue;
            }

            if(opcao >= 0 && opcao <= 7) {
                valido = 1;
            } else {
                printf("   ERRO: Opcao invalida! Digite um numero de 0 a 7.\n");
            }
        } while(!valido);

        switch(opcao) {
            case 1:
                gerenciar_produtos();
                break;

            case 2:
                controle_estoque();
                break;

            case 3:
                calculos_financeiros();
                break;

            case 4:
                relatorios_financeiros();
                break;

            case 5:
                analise_produtos();
                break;

            case 6:
                analise_anual();
                break;

            case 7:
                dashboard();
                break;

            case 0:
                printf("\n   Encerrando... Ate logo!\n");
                break;
        }
    } while(opcao != 0);
}

// Menu para operacoes com produtos: inserir, listar, pesquisar, editar, excluir
void gerenciar_produtos() {
    int opcao;
    int valido;

    do {
        limpar_tela();
        printf("   ---------------------------------\n");
        printf("   |   GERENCIAMENTO DE PRODUTOS   |\n");
        printf("   ---------------------------------\n\n");
        printf("   1. Inserir Novo Produto\n");
        printf("   2. Lista de Produtos\n");
        printf("   3. Pesquisar Produto\n");
        printf("   4. Editar Produto\n");
        printf("   5. Excluir Produto\n");
        printf("   0. Voltar ao Menu Principal\n\n");

        valido = 0;
        do {
            printf("   Escolha: ");

            if(scanf("%d", &opcao) != 1) {
                limpar_buffer();
                printf("   ERRO: Digite um numero valido (0 a 5)!\n");
                continue;
            }

            if(opcao >= 0 && opcao <= 5) {
                valido = 1;
            } else {
                printf("   ERRO: Opcao invalida! Digite um numero de 0 a 5.\n");
            }
        } while(!valido);

        if(opcao == 0) {
            return;
        }

        switch(opcao) {
            case 1:
                inserir_produto();
                break;

            case 2:
                listar_produtos();
                break;

            case 3:
                pesquisar_produto();
                break;

            case 4:
                editar_produto();
                break;

            case 5:
                excluir_produto();
                break;
        }
    } while(opcao != 0);
}


// Funcao auxiliar: Permite ao usuario selecionar uma categoria predefinida
// ou criar uma categoria personalizada. Usa switch-case para validar opcoes.
void selecionar_categoria(char *destino) {
    int cat_opc;
    char custom_confirm;
    int valido;

    printf("\n   --- SELECAO DE CATEGORIA ---\n\n");
    printf("   1. Acougue\n");
    printf("   2. Padaria\n");
    printf("   3. Higiene\n");
    printf("   4. Bebidas\n");
    printf("   5. Bebidas Alcoolicas\n");
    printf("   6. Limpeza\n");
    printf("   7. Comidas\n");
    printf("   8. Congelados\n");
    printf("   9. Laticinios\n");
    printf("   10. Hortifruti\n");
    printf("   11. Outra (Personalizada)\n\n");

    valido = 0;
    do {
        printf("   Escolha a categoria (1-11): ");

        if(scanf("%d", &cat_opc) != 1) {
            limpar_buffer();
            printf("   ERRO: Digite um numero valido (1 a 11)!\n");
            continue;
        }

        if(cat_opc >= 1 && cat_opc <= 11) {
            valido = 1;
        } else {
            printf("   ERRO: Categoria invalida! Digite um numero de 1 a 11.\n");
        }
    } while(!valido);

    switch(cat_opc) {
        case 1:
            strcpy(destino, "Acougue");
            break;

        case 2:
            strcpy(destino, "Padaria");
            break;

        case 3:
            strcpy(destino, "Higiene");
            break;

        case 4:
            strcpy(destino, "Bebidas");
            break;

        case 5:
            strcpy(destino, "Bebidas Alcoolicas");
            break;

        case 6:
            strcpy(destino, "Limpeza");
            break;

        case 7:
            strcpy(destino, "Comidas");
            break;

        case 8:
            strcpy(destino, "Congelados");
            break;

        case 9:
            strcpy(destino, "Laticinios");
            break;

        case 10:
            strcpy(destino, "Hortifruti");
            break;

        case 11:
            printf("\n   Deseja adicionar uma categoria nova? (S/N): ");
            scanf(" %c", &custom_confirm);

            if(toupper(custom_confirm) == 'S') {
                printf("   Escreva a nova categoria: ");
                scanf(" %[^\n]s", destino);
            } else {
                strcpy(destino, "Nao Definida");
            }
            break;
    }
}


// Insere um novo produto no vetor de estoque
// Valida: capacidade maxima, marca como ativo, calcula preco de venda e lucro
void inserir_produto() {
    int i, vaga = -1;
    float margem;

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 0) {
            vaga = i;
            break;
        }
    }

    if(vaga == -1) {
        printf("\n   ERRO: Capacidade maxima atingida!\n");
        pausar();
        return;
    }

    limpar_tela();
    printf("   -----------------------------\n");
    printf("   |    CADASTRO DE PRODUTO    |\n");
    printf("   -----------------------------\n\n");

    printf("   Codigo Identificador: ");
    scanf("%d", &estoque[vaga].codigo);

    printf("   Nome do Produto: ");
    scanf(" %[^\n]s", estoque[vaga].nome);

    selecionar_categoria(estoque[vaga].categoria);

    printf("\n   Quantidade em Estoque: ");
    scanf("%d", &estoque[vaga].quantidade);

    printf("   Estoque Minimo para Alerta: ");
    scanf("%d", &estoque[vaga].estoque_minimo);

    printf("   Preco de Custo (R$): ");
    scanf("%f", &estoque[vaga].preco_custo);

    printf("   Margem de Lucro Desejada (%%): ");
    scanf("%f", &margem);

    estoque[vaga].preco_venda = estoque[vaga].preco_custo * (1 + margem / 100);
    estoque[vaga].lucro_unitario = estoque[vaga].preco_venda - estoque[vaga].preco_custo;
    estoque[vaga].ativo = 1;

    printf("\n   Produto cadastrado com sucesso!\n");
    pausar();
}


// Lista todos os produtos ativos em uma tabela formatada
// Usa for para percorrer o vetor e exibe apenas ativo==1
void listar_produtos() {
    int i, encontrados = 0;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                          LISTA DE PRODUTOS                                      |\n");
    printf("   =====================================================================================\n\n");
    printf("   %-10s | %-25s | %-20s | %-10s | %-12s\n", "CODIGO", "NOME", "CATEGORIA", "QUANTIDADE", "PRECO");
    printf("   =====================================================================================\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1) {
            printf("   %-10d | %-25s | %-20s | %-10d | R$ %-10.2f\n",
                   estoque[i].codigo, estoque[i].nome, estoque[i].categoria,
                   estoque[i].quantidade, estoque[i].preco_venda);
            encontrados++;
        }
    }

    if(encontrados == 0) {
        printf("\n   Nenhum produto ativo no sistema.\n");
    }

    printf("   =====================================================================================\n");
    pausar();
}


// Pesquisa um produto pelo codigo
// Usa for para percorrer e if para validar ativo==1 e codigo igual
void pesquisar_produto() {
    int cod, i, encontrado = 0;

    limpar_tela();
    printf("   -----------------------------\n");
    printf("   |     PESQUISAR PRODUTO     |\n");
    printf("   -----------------------------\n\n");
    printf("   Digite o codigo para pesquisa: ");
    scanf("%d", &cod);

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].codigo == cod) {
            printf("\n   --- RESULTADO ---\n\n");
            printf("   Nome: %s\n", estoque[i].nome);
            printf("   Categoria: %s\n", estoque[i].categoria);
            printf("   Quantidade: %d\n", estoque[i].quantidade);
            printf("   Preco Venda: R$ %.2f\n", estoque[i].preco_venda);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\n   ERRO: Produto nao encontrado.\n");
    }

    pausar();
}


// Edita um produto existente pelo codigo
// Permite alterar nome, categoria, preco de custo e margem de lucro
void editar_produto() {
    int cod, i, encontrado = 0;
    float margem;

    limpar_tela();
    printf("   -----------------------------\n");
    printf("   |      EDITAR PRODUTO       |\n");
    printf("   -----------------------------\n\n");
    printf("   Codigo do produto: ");
    scanf("%d", &cod);

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].codigo == cod) {
            printf("\n   Editando: %s\n\n", estoque[i].nome);

            printf("   Novo Nome: ");
            scanf(" %[^\n]s", estoque[i].nome);

            selecionar_categoria(estoque[i].categoria);

            printf("\n   Novo Preco Custo: ");
            scanf("%f", &estoque[i].preco_custo);

            printf("   Nova Margem de Lucro (%%): ");
            scanf("%f", &margem);

            estoque[i].preco_venda = estoque[i].preco_custo * (1 + margem / 100);
            estoque[i].lucro_unitario = estoque[i].preco_venda - estoque[i].preco_custo;

            encontrado = 1;
            printf("\n   Dados atualizados!\n");
            break;
        }
    }

    if(!encontrado) {
        printf("\n   ERRO: Produto nao encontrado.\n");
    }

    pausar();
}


// Exclui um produto por remocao logica (marca ativo=0)
// Nao apaga fisicamente do vetor, apenas marca como inativo
void excluir_produto() {
    int cod, i, encontrado = 0;
    char confirma;

    limpar_tela();
    printf("   -----------------------------\n");
    printf("   |      EXCLUIR PRODUTO      |\n");
    printf("   -----------------------------\n\n");
    printf("   Codigo do produto: ");
    scanf("%d", &cod);

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].codigo == cod) {
            printf("\n   Deseja excluir '%s'? (S/N): ", estoque[i].nome);
            scanf(" %c", &confirma);

            if(toupper(confirma) == 'S') {
                estoque[i].ativo = 0;
                printf("\n   Produto removido!\n");
            } else {
                printf("\n   Operacao cancelada.\n");
            }

            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\n   ERRO: Produto nao encontrado.\n");
    }

    pausar();
}


// Menu para operacoes de estoque: atualizar, alertas, reposicao
void controle_estoque() {
    int opcao;
    int valido;

    do {
        limpar_tela();
        printf("   -----------------------------\n");
        printf("   |    CONTROLE DE ESTOQUE    |\n");
        printf("   -----------------------------\n\n");
        printf("   1. Atualizar Quantidade (Entrada/Venda)\n");
        printf("   2. Ver Alertas de Estoque Baixo\n");
        printf("   3. Relatorio de Reposicao\n");
        printf("   0. Voltar ao Menu Principal\n\n");

        valido = 0;
        do {
            printf("   Escolha: ");

            if(scanf("%d", &opcao) != 1) {
                limpar_buffer();
                printf("   ERRO: Digite um numero valido (0 a 3)!\n");
                continue;
            }

            if(opcao >= 0 && opcao <= 3) {
                valido = 1;
            } else {
                printf("   ERRO: Opcao invalida! Digite um numero de 0 a 3.\n");
            }
        } while(!valido);

        if(opcao == 0) {
            return;
        }

        switch(opcao) {
            case 1:
                atualizar_quantidade();
                break;

            case 2:
                alerta_estoque_baixo();
                break;

            case 3:
                relatorio_reposicao();
                break;
        }
    } while(opcao != 0);
}


// Atualiza quantidade de produto (entrada positiva ou venda negativa)
// Se venda: registra lucro no mes informado
void atualizar_quantidade() {
    int cod, qtd, i, mes, encontrado = 0;
    int valido;

    limpar_tela();
    printf("   -----------------------------\n");
    printf("   |   ATUALIZAR QUANTIDADE    |\n");
    printf("   -----------------------------\n\n");
    printf("   Codigo do produto: ");
    scanf("%d", &cod);

    printf("   Quantidade (positivo: entrada | negativo: venda): ");
    scanf("%d", &qtd);

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].codigo == cod) {
            if(qtd < 0) {
                if((estoque[i].quantidade + qtd) < 0) {
                    printf("\n   ERRO: Estoque insuficiente!\n");
                } else {
                    valido = 0;
                    do {
                        printf("\n   Informe o mes da venda (1-12): ");

                        if(scanf("%d", &mes) != 1) {
                            limpar_buffer();
                            printf("   ERRO: Digite um numero valido (1 a 12)!\n");
                            continue;
                        }

                        if(mes >= 1 && mes <= 12) {
                            valido = 1;
                        } else {
                            printf("   ERRO: Mes invalido! Digite um numero de 1 a 12.\n");
                        }
                    } while(!valido);

                    lucros_mensais[mes - 1] += (estoque[i].lucro_unitario * (qtd * -1));
                    estoque[i].quantidade += qtd;
                    printf("\n   Venda registrada em %s!\n", nomes_meses[mes - 1]);
                }
            } else {
                estoque[i].quantidade += qtd;
                printf("\n   Estoque abastecido!\n");
            }

            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\n   ERRO: Produto nao encontrado.\n");
    }

    pausar();
}


// Exibe alertas de produtos com estoque abaixo do minimo
// Usa for e if para verificar quantidade <= estoque_minimo
void alerta_estoque_baixo() {
    int i, count = 0;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                         ALERTAS DE ESTOQUE                                      |\n");
    printf("   =====================================================================================\n\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].quantidade <= estoque[i].estoque_minimo) {
            printf("   ALERTA: %-30s | Atual: %-5d | Minimo: %-5d\n",
                   estoque[i].nome, estoque[i].quantidade, estoque[i].estoque_minimo);
            count++;
        }
    }

    if(count == 0) {
        printf("\n   Estoque em niveis normais.\n");
    }

    printf("   =====================================================================================\n");
    pausar();
}


// Gera relatorio de reposicao sugerindo quantidade a comprar
// Calcula: (estoque_minimo * 2) - quantidade_atual
void relatorio_reposicao() {
    int i, nec;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                      RELATORIO DE REPOSICAO                                     |\n");
    printf("   =====================================================================================\n\n");
    printf("   %-30s | %-15s | %-15s\n", "Produto", "Quantidade Atual", "Quantidade Comprar");
    printf("   =====================================================================================\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1 && estoque[i].quantidade <= estoque[i].estoque_minimo) {
            nec = (estoque[i].estoque_minimo * 2) - estoque[i].quantidade;
            printf("   %-30s | %-15d | %-15d\n", estoque[i].nome, estoque[i].quantidade, nec);
        }
    }

    printf("   =====================================================================================\n");
    pausar();
}


// Exibe tabela com calculos de lucro por produto
// Mostra: preco venda, lucro unitario, valor investido, valor potencial
void calculos_financeiros() {
    int i;
    float investido, potencial;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                        CALCULOS DE LUCROS                                       |\n");
    printf("   =====================================================================================\n\n");
    printf("   %-25s | %-12s | %-12s | %-12s | %-12s\n", "Nome", "Venda", "Lucro Un.", "Investido", "Potencial");
    printf("   =====================================================================================\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1) {
            investido = estoque[i].quantidade * estoque[i].preco_custo;
            potencial = estoque[i].quantidade * estoque[i].preco_venda;
            printf("   %-25s | %-12.2f | %-12.2f | %-12.2f | %-12.2f\n",
                   estoque[i].nome, estoque[i].preco_venda, estoque[i].lucro_unitario, investido, potencial);
        }
    }

    printf("   =====================================================================================\n");
    pausar();
}


// Exibe resumo financeiro geral do supermercado
// Calcula: capital total investido, valor total de venda, lucro potencial total
void relatorios_financeiros() {
    int i;
    float total_investido = 0, total_potencial = 0;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                       RELATORIO FINANCEIRO                                      |\n");
    printf("   =====================================================================================\n\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1) {
            total_investido += (estoque[i].quantidade * estoque[i].preco_custo);
            total_potencial += (estoque[i].quantidade * estoque[i].preco_venda);
        }
    }

    printf("   Capital Total Investido:    R$ %.2f\n", total_investido);
    printf("   Valor Total de Venda:       R$ %.2f\n", total_potencial);
    printf("   Lucro Potencial Total:      R$ %.2f\n", total_potencial - total_investido);

    printf("   =====================================================================================\n");
    pausar();
}

// Analisa e exibe produtos em destaque
// Encontra: mais caro, mais barato, maior lucro, maior estoque
void analise_produtos() {
    int i, primeiro = 1;
    int p_caro, p_barato, p_lucro_max, p_lucro_min, p_est_max, p_est_min;

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                       ANALISE DE PRODUTOS                                       |\n");
    printf("   =====================================================================================\n\n");

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1) {
            if(primeiro) {
                p_caro = p_barato = p_lucro_max = p_lucro_min = p_est_max = p_est_min = i;
                primeiro = 0;
            } else {
                if(estoque[i].preco_venda > estoque[p_caro].preco_venda) {
                    p_caro = i;
                }

                if(estoque[i].preco_venda < estoque[p_barato].preco_venda) {
                    p_barato = i;
                }

                if(estoque[i].lucro_unitario > estoque[p_lucro_max].lucro_unitario) {
                    p_lucro_max = i;
                }

                if(estoque[i].lucro_unitario < estoque[p_lucro_min].lucro_unitario) {
                    p_lucro_min = i;
                }

                if(estoque[i].quantidade > estoque[p_est_max].quantidade) {
                    p_est_max = i;
                }

                if(estoque[i].quantidade < estoque[p_est_min].quantidade) {
                    p_est_min = i;
                }
            }
        }
    }

    if(primeiro) {
        printf("   Nao ha produtos para analisar.\n");
    } else {
        printf("   Produto Mais Caro:          %s (R$ %.2f)\n", estoque[p_caro].nome, estoque[p_caro].preco_venda);
        printf("   Produto Mais Barato:        %s (R$ %.2f)\n", estoque[p_barato].nome, estoque[p_barato].preco_venda);
        printf("   Maior Lucro Unitario:       %s (R$ %.2f)\n", estoque[p_lucro_max].nome, estoque[p_lucro_max].lucro_unitario);
        printf("   Maior Volume em Estoque:    %s (%d un.)\n", estoque[p_est_max].nome, estoque[p_est_max].quantidade);
    }

    printf("   =====================================================================================\n");
    pausar();
}

// Analisa desempenho anual: lucro total, melhor mes, ranking de lucros
// Usa bubble sort para ordenar meses por lucro decrescente
void analise_anual() {
    float total_anual = 0;
    int melhor_mes = 0;
    int i, j, temp, indices[MESES];

    limpar_tela();
    printf("   =====================================================================================\n");
    printf("   |                    ANALISE DE DESEMPENHO ANUAL                                  |\n");
    printf("   =====================================================================================\n\n");

    for(i = 0; i < MESES; i++) {
        total_anual += lucros_mensais[i];

        if(lucros_mensais[i] > lucros_mensais[melhor_mes]) {
            melhor_mes = i;
        }

        indices[i] = i;
    }

    printf("   Faturamento Total: R$ %.2f\n", total_anual);
    printf("   Melhor Mes:        %s\n\n", nomes_meses[melhor_mes]);

    printf("   LISTAGEM MENSAL:\n");
    for(i = 0; i < MESES; i++) {
        printf("   Mes %02d (%-10s): R$ %10.2f\n", i + 1, nomes_meses[i], lucros_mensais[i]);
    }

    // Bubble Sort para ordenar meses por lucro decrescente
    for(i = 0; i < MESES - 1; i++) {
        for(j = 0; j < MESES - i - 1; j++) {
            if(lucros_mensais[indices[j]] < lucros_mensais[indices[j + 1]]) {
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\n   RANKING DE LUCRO:\n");
    for(i = 0; i < 3 && i < MESES; i++) {
        printf("   %do Lugar: %s (R$ %.2f)\n", i + 1, nomes_meses[indices[i]], lucros_mensais[indices[i]]);
    }

    printf("   =====================================================================================\n");
    pausar();
}

// Dashboard executivo com KPIs principais do supermercado
// Exibe: total de produtos, itens, estoque baixo, capital investido, lucro
void dashboard() {
    int i, ativos = 0, total_itens = 0, criticos = 0;
    float investido = 0, potencial = 0;

    for(i = 0; i < MAX_PRODUTOS; i++) {
        if(estoque[i].ativo == 1) {
            ativos++;
            total_itens += estoque[i].quantidade;
            investido += (estoque[i].quantidade * estoque[i].preco_custo);
            potencial += (estoque[i].quantidade * estoque[i].preco_venda);

            if(estoque[i].quantidade <= estoque[i].estoque_minimo) {
                criticos++;
            }
        }
    }

    limpar_tela();
    printf("   ====================================================\n");
    printf("   ||              DASHBOARD GERENCIAL               ||\n");
    printf("   ====================================================\n\n");
    printf("   >> Produtos Ativos:          %d\n", ativos);
    printf("   >> Total de Itens:           %d\n", total_itens);
    printf("   >> Itens em Estoque Baixo:   %d\n\n", criticos);
    printf("   ====================================================\n");
    printf("   >> Capital Investido:        R$ %.2f\n", investido);
    printf("   >> Faturamento Estimado:     R$ %.2f\n", potencial);
    printf("   >> Lucro Estimado:           R$ %.2f\n", potencial - investido);
    printf("   ====================================================\n");

    pausar();
}

