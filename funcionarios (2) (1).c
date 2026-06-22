#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FUNCIONARIOS 100
#define TAM_NOME 100
#define TAM_CARGO 50
#define NOME_ARQUIVO "funcionarios.txt"

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    char cargo[TAM_CARGO];
    float salario;
} Funcionario;

/* ---------- Protótipos das funções ---------- */
void limparBufferEntrada(void);
int buscarIndicePorCodigo(Funcionario *funcionarios, int quantidade, int codigo);

void cadastrarFuncionario(Funcionario *funcionarios, int *quantidade);
void listarFuncionarios(Funcionario *funcionarios, int quantidade);
void buscarFuncionario(Funcionario *funcionarios, int quantidade);
void alterarFuncionario(Funcionario *funcionarios, int quantidade);
void removerFuncionario(Funcionario *funcionarios, int *quantidade);
void salvarArquivo(Funcionario *funcionarios, int quantidade);
void carregarArquivo(Funcionario *funcionarios, int *quantidade);

void exibirMenu(void);

/* ============================================================
   FUNÇÃO PRINCIPAL
   ============================================================ */
int main(void) {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int quantidade = 0;
    int opcao;

    do {
        exibirMenu();
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida ou fim dos dados. Encerrando o sistema...\n");
            break;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarFuncionario(funcionarios, &quantidade);
                break;
            case 2:
                listarFuncionarios(funcionarios, quantidade);
                break;
            case 3:
                buscarFuncionario(funcionarios, quantidade);
                break;
            case 4:
                alterarFuncionario(funcionarios, quantidade);
                break;
            case 5:
                removerFuncionario(funcionarios, &quantidade);
                break;
            case 6:
                salvarArquivo(funcionarios, quantidade);
                break;
            case 7:
                carregarArquivo(funcionarios, &quantidade);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}

/* ============================================================
   FUNÇÕES AUXILIARES
   ============================================================ */

/* Limpa o \n que sobra no buffer de entrada apos um scanf */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Retorna o indice do funcionario com o codigo informado, ou -1 se nao existir */
int buscarIndicePorCodigo(Funcionario *funcionarios, int quantidade, int codigo) {
    int i;
    for (i = 0; i < quantidade; i++) {
        if (funcionarios[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void exibirMenu(void) {
    printf("===== SISTEMA DE GERENCIAMENTO DE FUNCIONARIOS =====\n");
    printf("1 - Cadastrar funcionario\n");
    printf("2 - Listar funcionarios\n");
    printf("3 - Buscar funcionario\n");
    printf("4 - Alterar funcionario\n");
    printf("5 - Remover funcionario\n");
    printf("6 - Salvar em arquivo\n");
    printf("7 - Carregar do arquivo\n");
    printf("0 - Sair\n");
    printf("=====================================================\n");
}

/* ============================================================
   CADASTRAR (usa ponteiros para o vetor e para a quantidade)
   ============================================================ */
void cadastrarFuncionario(Funcionario *funcionarios, int *quantidade) {
    Funcionario novo;

    if (*quantidade >= MAX_FUNCIONARIOS) {
        printf("Limite maximo de funcionarios atingido!\n");
        return;
    }

    printf("--- Cadastro de funcionario ---\n");

    printf("Codigo: ");
    scanf("%d", &novo.codigo);
    limparBufferEntrada();

    if (buscarIndicePorCodigo(funcionarios, *quantidade, novo.codigo) != -1) {
        printf("Ja existe um funcionario cadastrado com esse codigo!\n");
        return;
    }

    printf("Nome: ");
    fgets(novo.nome, TAM_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Cargo: ");
    fgets(novo.cargo, TAM_CARGO, stdin);
    novo.cargo[strcspn(novo.cargo, "\n")] = '\0';

    printf("Salario: ");
    scanf("%f", &novo.salario);
    limparBufferEntrada();

    funcionarios[*quantidade] = novo;
    (*quantidade)++;

    printf("Funcionario cadastrado com sucesso!\n");
}

/* ============================================================
   LISTAR
   ============================================================ */
void listarFuncionarios(Funcionario *funcionarios, int quantidade) {
    int i;

    if (quantidade == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    printf("\n%-8s %-25s %-20s %12s\n", "Codigo", "Nome", "Cargo", "Salario");
    printf("--------------------------------------------------------------------\n");
    for (i = 0; i < quantidade; i++) {
        printf("%-8d %-25s %-20s %12.2f\n",
               funcionarios[i].codigo,
               funcionarios[i].nome,
               funcionarios[i].cargo,
               funcionarios[i].salario);
    }
}

/* ============================================================
   BUSCAR
   ============================================================ */
void buscarFuncionario(Funcionario *funcionarios, int quantidade) {
    int codigo, idx;

    printf("Digite o codigo do funcionario: ");
    scanf("%d", &codigo);
    limparBufferEntrada();

    idx = buscarIndicePorCodigo(funcionarios, quantidade, codigo);

    if (idx == -1) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    printf("\n--- Funcionario encontrado ---\n");
    printf("Codigo : %d\n", funcionarios[idx].codigo);
    printf("Nome   : %s\n", funcionarios[idx].nome);
    printf("Cargo  : %s\n", funcionarios[idx].cargo);
    printf("Salario: %.2f\n", funcionarios[idx].salario);
}

/* ============================================================
   ALTERAR
   ============================================================ */
void alterarFuncionario(Funcionario *funcionarios, int quantidade) {
    int codigo, idx;

    printf("Digite o codigo do funcionario que deseja alterar: ");
    scanf("%d", &codigo);
    limparBufferEntrada();

    idx = buscarIndicePorCodigo(funcionarios, quantidade, codigo);

    if (idx == -1) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    printf("Novo nome (atual: %s): ", funcionarios[idx].nome);
    fgets(funcionarios[idx].nome, TAM_NOME, stdin);
    funcionarios[idx].nome[strcspn(funcionarios[idx].nome, "\n")] = '\0';

    printf("Novo cargo (atual: %s): ", funcionarios[idx].cargo);
    fgets(funcionarios[idx].cargo, TAM_CARGO, stdin);
    funcionarios[idx].cargo[strcspn(funcionarios[idx].cargo, "\n")] = '\0';

    printf("Novo salario (atual: %.2f): ", funcionarios[idx].salario);
    scanf("%f", &funcionarios[idx].salario);
    limparBufferEntrada();

    printf("Funcionario alterado com sucesso!\n");
}

/* ============================================================
   REMOVER (usa ponteiro para a quantidade)
   ============================================================ */
void removerFuncionario(Funcionario *funcionarios, int *quantidade) {
    int codigo, idx, i;

    printf("Digite o codigo do funcionario que deseja remover: ");
    scanf("%d", &codigo);
    limparBufferEntrada();

    idx = buscarIndicePorCodigo(funcionarios, *quantidade, codigo);

    if (idx == -1) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    /* desloca os elementos seguintes uma posicao para tras */
    for (i = idx; i < *quantidade - 1; i++) {
        funcionarios[i] = funcionarios[i + 1];
    }
    (*quantidade)--;

    printf("Funcionario removido com sucesso!\n");
}

/* ============================================================
   SALVAR EM ARQUIVO
   ============================================================ */
void salvarArquivo(Funcionario *funcionarios, int quantidade) {
    FILE *arquivo;
    int i;

    arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "%d\n", quantidade);
    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n%s\n%s\n%.2f\n",
                funcionarios[i].codigo,
                funcionarios[i].nome,
                funcionarios[i].cargo,
                funcionarios[i].salario);
    }

    fclose(arquivo);
    printf("Dados salvos em '%s' com sucesso!\n", NOME_ARQUIVO);
}

/* ============================================================
   CARREGAR DO ARQUIVO
   ============================================================ */
void carregarArquivo(Funcionario *funcionarios, int *quantidade) {
    FILE *arquivo;
    int total, i;

    arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Arquivo '%s' nao encontrado.\n", NOME_ARQUIVO);
        return;
    }

    fscanf(arquivo, "%d", &total);
    getc(arquivo); /* consome o \n que sobra apos o fscanf */

    *quantidade = 0;
    for (i = 0; i < total && i < MAX_FUNCIONARIOS; i++) {
        fscanf(arquivo, "%d", &funcionarios[i].codigo);
        getc(arquivo);

        fgets(funcionarios[i].nome, TAM_NOME, arquivo);
        funcionarios[i].nome[strcspn(funcionarios[i].nome, "\n")] = '\0';

        fgets(funcionarios[i].cargo, TAM_CARGO, arquivo);
        funcionarios[i].cargo[strcspn(funcionarios[i].cargo, "\n")] = '\0';

        fscanf(arquivo, "%f", &funcionarios[i].salario);
        getc(arquivo);

        (*quantidade)++;
    }

    fclose(arquivo);
    printf("Dados carregados de '%s' com sucesso! (%d funcionario(s))\n", NOME_ARQUIVO, *quantidade);
}
