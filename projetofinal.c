#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
  #define CLEAR_COMMAND "cls"
#else
  #define CLEAR_COMMAND "clear"
#endif

// ==========================
// CORES ANSIz
// ==========================
#define RESET   "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE   "\033[32m"
#define AMARELO "\033[33m"
#define AZUL    "\033[34m"
#define ROXO    "\033[35m"
#define CIANO   "\033[36m"
#define BRANCO  "\033[37m"

// ==========================
// CONSTANTES
// ==========================
#define MAX 100
#define STRLEN 50
#define INPUT_BUFFER 128

// ==========================
// STRUCT DO PRODUTO
// ==========================
typedef struct {
    int codigo;
    char nome[STRLEN];
    float preco;
    int quantidade;
} Produto;

// ==========================
// FUNÇÕES AUXILIARES
// ==========================

void pause_enter(void) {
    printf(AMARELO "\nPressione ENTER para continuar..." RESET);
    // ler e descartar até \n
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar(); // espera ENTER do usuário
}

void limparTela(void) {
    system(CLEAR_COMMAND);
}

void safe_fgets(char *out, size_t size) {
    if (fgets(out, (int)size, stdin) == NULL) {
        // Em caso de EOF, colocar string vazia
        out[0] = '\0';
        return;
    }
    // remover '\n' final, se existir
    out[strcspn(out, "\n")] = '\0';
}

// Função obrigatória: consulta produto pelo código
int consultarProduto(Produto lista[], int total, int codigoBuscado) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigoBuscado) return i;
    }
    return -1;
}

void header(void) {
    printf(AZUL "===============================================\n" RESET);
    printf(ROXO "     SISTEMA DE CADASTRO E CONSULTA DE PRODUTOS\n" RESET);
    printf(AZUL "===============================================\n\n" RESET);
}

// ==========================
// CRUD DE PRODUTOS
// ==========================
void cadastrarProduto(Produto lista[], int *total) {
    if (*total >= MAX) {
        printf(VERMELHO "Limite maximo de produtos atingido!\n" RESET);
        return;
    }

    char buffer[INPUT_BUFFER];

    printf(VERDE "\n----- CADASTRAR PRODUTO -----\n" RESET);

    // codigo
    while (1) {
        printf("Codigo (inteiro): ");
        safe_fgets(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &lista[*total].codigo) == 1) break;
        printf(VERMELHO "Entrada invalida. Digite um numero inteiro.\n" RESET);
    }

    // nome
    printf("Nome: ");
    safe_fgets(lista[*total].nome, sizeof(lista[*total].nome));

    // preco
    while (1) {
        printf("Preco (ex: 12.50): ");
        safe_fgets(buffer, sizeof(buffer));
        if (sscanf(buffer, "%f", &lista[*total].preco) == 1) break;
        printf(VERMELHO "Entrada invalida. Digite um numero (float).\n" RESET);
    }

    // quantidade
    while (1) {
        printf("Quantidade (inteiro): ");
        safe_fgets(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &lista[*total].quantidade) == 1) break;
        printf(VERMELHO "Entrada invalida. Digite um numero inteiro.\n" RESET);
    }

    (*total)++;
    printf(VERDE "\nProduto cadastrado com sucesso!\n" RESET);
}

void listarProdutos(Produto lista[], int total) {
    printf(CIANO "\n----- LISTA DE PRODUTOS -----\n" RESET);
    if (total == 0) {
        printf(AMARELO "Nenhum produto cadastrado.\n" RESET);
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("\nProduto %d\n", i + 1);
        printf("Codigo: %d\n", lista[i].codigo);
        printf("Nome: %s\n", lista[i].nome);
        printf("Preco: R$ %.2f\n", lista[i].preco);
        printf("Quantidade: %d\n", lista[i].quantidade);
    }
}

void consultar(Produto lista[], int total) {
    char buffer[INPUT_BUFFER];
    int codigo;
    printf(AZUL "\nDigite o codigo do produto: " RESET);
    safe_fgets(buffer, sizeof(buffer));
    if (sscanf(buffer, "%d", &codigo) != 1) {
        printf(VERMELHO "Codigo invalido.\n" RESET);
        return;
    }

    int indice = consultarProduto(lista, total, codigo);
    if (indice == -1) {
        printf(VERMELHO "\nProduto nao encontrado!\n" RESET);
    } else {
        printf(VERDE "\n--- Produto Encontrado ---\n" RESET);
        printf("Codigo: %d\n", lista[indice].codigo);
        printf("Nome: %s\n", lista[indice].nome);
        printf("Preco: R$ %.2f\n", lista[indice].preco);
        printf("Quantidade: %d\n", lista[indice].quantidade);
    }
}

void editarProduto(Produto lista[], int total) {
    char buffer[INPUT_BUFFER];
    int codigo;
    printf(ROXO "\nDigite o codigo do produto a editar: " RESET);
    safe_fgets(buffer, sizeof(buffer));
    if (sscanf(buffer, "%d", &codigo) != 1) {
        printf(VERMELHO "Codigo invalido.\n" RESET);
        return;
    }

    int indice = consultarProduto(lista, total, codigo);
    if (indice == -1) {
        printf(VERMELHO "Produto nao encontrado!\n" RESET);
        return;
    }

    printf(AMARELO "\n--- Editando Produto (deixe em branco para nao alterar) ---\n" RESET);

    printf("Novo nome [%s]: ", lista[indice].nome);
    safe_fgets(buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        strncpy(lista[indice].nome, buffer, STRLEN - 1);
        lista[indice].nome[STRLEN - 1] = '\0';
    }

    printf("Novo preco [%.2f]: ", lista[indice].preco);
    safe_fgets(buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        float f;
        if (sscanf(buffer, "%f", &f) == 1) lista[indice].preco = f;
        else printf(VERMELHO "Preco invalido. Mantendo valor anterior.\n" RESET);
    }

    printf("Nova quantidade [%d]: ", lista[indice].quantidade);
    safe_fgets(buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        int q;
        if (sscanf(buffer, "%d", &q) == 1) lista[indice].quantidade = q;
        else printf(VERMELHO "Quantidade invalida. Mantendo valor anterior.\n" RESET);
    }

    printf(VERDE "\nProduto atualizado com sucesso!\n" RESET);
}

void excluirProduto(Produto lista[], int *total) {
    char buffer[INPUT_BUFFER];
    int codigo;
    printf(VERMELHO "\nDigite o codigo do produto a excluir: " RESET);
    safe_fgets(buffer, sizeof(buffer));
    if (sscanf(buffer, "%d", &codigo) != 1) {
        printf(VERMELHO "Codigo invalido.\n" RESET);
        return;
    }

    int indice = consultarProduto(lista, *total, codigo);
    if (indice == -1) {
        printf(VERMELHO "Produto nao encontrado!\n" RESET);
        return;
    }

    for (int i = indice; i < *total - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*total)--;

    printf(VERDE "\nProduto excluido com sucesso!\n" RESET);
}

// ==========================
// PROGRAMA PRINCIPAL
// ==========================
int main(void) {
    // Configuracoes de local e terminal (UTF-8 no Windows via chcp)
    setlocale(LC_ALL, "");
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    Produto produtos[MAX];
    int total = 0;
    char input[INPUT_BUFFER];

    while (1) {
        limparTela();
        header();
        printf(CIANO "[1] Cadastrar Produto\n" RESET);
        printf(CIANO "[2] Listar Produtos\n" RESET);
        printf(CIANO "[3] Consultar Produto por Codigo\n" RESET);
        printf(CIANO "[4] Editar Produto\n" RESET);
        printf(CIANO "[5] Excluir Produto\n" RESET);
        printf(CIANO "[6] Sair\n" RESET);

        printf(AMARELO "\nEscolha uma opcao: " RESET);
        safe_fgets(input, sizeof(input));

        int opcao = 0;
        if (sscanf(input, "%d", &opcao) != 1) {
            printf(VERMELHO "Entrada invalida. Digite um numero de 1 a 6.\n" RESET);
            pause_enter();
            continue;
        }

        switch (opcao) {
            case 1: cadastrarProduto(produtos, &total); break;
            case 2: listarProdutos(produtos, total); break;
            case 3: consultar(produtos, total); break;
            case 4: editarProduto(produtos, total); break;
            case 5: excluirProduto(produtos, &total); break;
            case 6:
                printf(VERDE "\nSaindo do sistema...\n" RESET);
                return 0;
            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

        pause_enter();
    }

    return 0;
}
