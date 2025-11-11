#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_FILA 5

typedef struct Peca {
    char nome[2];
    int id;
} Peca;

typedef struct FilaCircular {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int contador;
    int proximo_id;
} FilaCircular;

void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->contador = 0;
    fila->proximo_id = 1;
    srand(time(NULL));
    printf("Fila de pecas inicializada com capacidade para %d elementos.\n", TAMANHO_FILA);
}

Peca gerarPeca(FilaCircular *fila) {
    const char *tipos = "TOIL";
    int indice = rand() % 4;
    
    Peca novaPeca;
    novaPeca.nome[0] = tipos[indice];
    novaPeca.nome[1] = '\0';
    novaPeca.id = fila->proximo_id++;
    
    return novaPeca;
}

int estaCheia(FilaCircular *fila) {
    return fila->contador == TAMANHO_FILA;
}

int estaVazia(FilaCircular *fila) {
    return fila->contador == 0;
}

int inserirPeca(FilaCircular *fila) {
    if (estaCheia(fila)) {
        printf("\nERRO: Fila cheia. Nao e possivel inserir mais pecas.\n");
        return 0;
    }
    
    Peca novaPeca = gerarPeca(fila);
    
    fila->pecas[fila->tras] = novaPeca;
    
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->contador++;
    
    printf("\nSUCESSO: Peca [%s %d] inserida na fila.\n", novaPeca.nome, novaPeca.id);
    return 1;
}

int jogarPeca(FilaCircular *fila) {
    if (estaVazia(fila)) {
        printf("\nERRO: Fila vazia. Nao ha pecas para jogar.\n");
        return 0;
    }
    
    Peca pecaRemovida = fila->pecas[fila->frente];
    
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->contador--;
    
    printf("\nSUCESSO: Peca [%s %d] jogada (removida da fila).\n", pecaRemovida.nome, pecaRemovida.id);
    return 1;
}

void exibirFila(FilaCircular *fila) {
    printf("\n=====================================\n");
    printf(" ESTADO ATUAL DA FILA DE PEÇAS \n");
    printf("=====================================\n");
    
    if (estaVazia(fila)) {
        printf("Fila vazia. Tamanho: 0/%d\n", TAMANHO_FILA);
        return;
    }

    printf("Fila de pecas (%d/%d):\n", fila->contador, TAMANHO_FILA);
    
    int i = fila->frente;
    int count = 0;
    while (count < fila->contador) {
        printf("[%s %d] ", fila->pecas[i].nome, fila->pecas[i].id);
        i = (i + 1) % TAMANHO_FILA;
        count++;
    }
    printf("\n");
    printf("-------------------------------------\n");
    printf("Frente (Dequeue) esta na posicao: [%d]\n", fila->frente);
    printf("Tras (Enqueue) esta na posicao: [%d]\n", fila->tras);
}

void exibirMenu() {
    printf("\nOpcoes de acao:\n");
    printf(" 1 - Jogar peca (dequeue)\n");
    printf(" 2 - Inserir nova peca (enqueue)\n");
    printf(" 0 - Sair\n");
    printf("Escolha uma acao: ");
}

int main() {
    FilaCircular fila;
    int opcao;
    
    inicializarFila(&fila);
    
    inserirPeca(&fila);
    inserirPeca(&fila);
    
    do {
        exibirFila(&fila);
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while (getchar() != '\n');
        }
        
        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila);
                break;
            case 0:
                printf("\nEncerrando o programa. Bom jogo!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                while (getchar() != '\n');
                break;
        }
    } while (opcao != 0);
    
    return 0;
}
