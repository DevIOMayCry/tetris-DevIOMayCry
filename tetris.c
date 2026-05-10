#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_FILA 5
#define CAPACIDADE_PILHA 3 // Nova capacidade para a reserva

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// --- Estruturas (Nível Novato e Aventureiro) ---
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca itens[CAPACIDADE_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Estrutura da Pilha Linear (Reserva)
typedef struct {
    Peca itens[CAPACIDADE_PILHA];
    int topo;
} Pilha;

// --- Protótipos das Funções ---
// Funções da Fila
void inicializarFila(Fila *f);
int filaCheia(Fila *f); 
int filaVazia(Fila *f); 
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void mostrarFila(Fila *f);

// Funções da Pilha
void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca p_nova);
Peca pop(Pilha *p);
void mostrarPilha(Pilha *p);

// Funções Gerais
char sortearTipoTetris();
void limparBuffer();


int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.
    
    srand(time(NULL)); // Garante peças aleatórias em cada partida

    // Inicialização da Fila
    Fila filaProximas;
    inicializarFila(&filaProximas);
    
    // Inicialização da Pilha
    Pilha pilhaReserva;
    inicializarPilha(&pilhaReserva);
    
    int proximo_id = 1; 
    int opcao;

    // Preenche a fila inicial com 5 peças
    while (filaCheia(&filaProximas) == 0) {
        Peca novaPeca;
        novaPeca.tipo = sortearTipoTetris();
        novaPeca.id = proximo_id++;
        enqueue(&filaProximas, novaPeca);
    }

    do {
        printf("\n========================================\n");
        printf("        TETRIS - CONTROLE DE PECAS      \n");
        printf("========================================\n");
        
        mostrarFila(&filaProximas);
        mostrarPilha(&pilhaReserva);

        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Jogar peca (Remover da frente)\n");
        printf("2 - Enviar peca da fila para a reserva (Pilha)\n");
        printf("3 - Usar peca da reserva (Remover do topo da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (filaVazia(&filaProximas) == 0) {
                    // Remove a peça da frente
                    Peca pecaJogada = dequeue(&filaProximas);
                    printf("\n>>> Peca Jogada: [%c] (ID: %d) caiu no tabuleiro! <<<\n", pecaJogada.tipo, pecaJogada.id);

                    // Gera uma nova peça para o final da fila
                    Peca novaPeca;
                    novaPeca.tipo = sortearTipoTetris();
                    novaPeca.id = proximo_id++;
                    
                    // Insere a nova peça
                    enqueue(&filaProximas, novaPeca);
                    printf("Uma nova peca [%c] (ID: %d) entrou no final da fila.\n", novaPeca.tipo, novaPeca.id);
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
                
            case 2:
                // 🧠 Nível Aventureiro: Adição da Pilha de Reserva (Mover para Pilha)
                if (filaVazia(&filaProximas) == 0 && pilhaCheia(&pilhaReserva) == 0) {
                    Peca pecaMover = dequeue(&filaProximas);
                    push(&pilhaReserva, pecaMover);
                    printf("\n>>> Peca [%c] (ID: %d) enviada para a Reserva! <<<\n", pecaMover.tipo, pecaMover.id);

                    // Repondo a fila com uma nova peça gerada para manter 5 itens
                    Peca novaPeca;
                    novaPeca.tipo = sortearTipoTetris();
                    novaPeca.id = proximo_id++;
                    enqueue(&filaProximas, novaPeca);
                    printf("A fila foi reposta com a peca [%c] (ID: %d).\n", novaPeca.tipo, novaPeca.id);
                } else {
                    printf("\nErro: Pilha de reserva cheia ou fila vazia!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3:
                // 🧠 Nível Aventureiro: Usar da Reserva (Remover da Pilha)
                if (pilhaVazia(&pilhaReserva) == 0) {
                    Peca pecaUsada = pop(&pilhaReserva);
                    printf("\n>>> Peca da Reserva Jogada: [%c] (ID: %d) caiu no tabuleiro! <<<\n", pecaUsada.tipo, pecaUsada.id);
                } else {
                    printf("\nErro: A reserva (pilha) ja esta vazia!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nEncerrando o jogo. Game Over!\n");
                break;
                
            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    return 0;
}

// ============================================================================
// --- Implementação das Funções (Nível Novato) ---
// ============================================================================

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    if (f->quantidade == CAPACIDADE_FILA) {
        return 1; // Verdadeiro
    }
    return 0; // Falso
}

int filaVazia(Fila *f) {
    if (f->quantidade == 0) {
        return 1; // Verdadeiro
    }
    return 0; // Falso
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f) == 1) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % CAPACIDADE_FILA; // Logica da Fila Circular
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca pecaRemovida = {' ', -1}; 
    if (filaVazia(f) == 1) {
        printf("Erro: Fila vazia!\n");
        return pecaRemovida;
    }
    
    pecaRemovida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE_FILA; // Logica da Fila Circular
    f->quantidade--;
    
    return pecaRemovida;
}

void mostrarFila(Fila *f) {
    printf("\n[ FILA DE PROXIMAS PECAS ] -> (Capacidade: %d/%d)\n", f->quantidade, CAPACIDADE_FILA);
    printf("Inicio -> ");
    
    for (int i = 0; i < f->quantidade; i++) {
        int index = (f->inicio + i) % CAPACIDADE_FILA;
        printf("[%c|id:%d] ", f->itens[index].tipo, f->itens[index].id);
        
        if (i < f->quantidade - 1) {
            printf("- ");
        }
    }
    printf("<- Fim\n");
}

// ============================================================================
// --- Implementação das Funções (Nível Aventureiro) ---
// ============================================================================

void inicializarPilha(Pilha *p) {
    p->topo = -1; // -1 indica que a pilha está vazia
}

int pilhaCheia(Pilha *p) {
    if (p->topo == CAPACIDADE_PILHA - 1) {
        return 1;
    }
    return 0;
}

int pilhaVazia(Pilha *p) {
    if (p->topo == -1) {
        return 1;
    }
    return 0;
}

void push(Pilha *p, Peca p_nova) {
    if (pilhaCheia(p) == 1) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = p_nova;
}

Peca pop(Pilha *p) {
    Peca pecaRemovida = {' ', -1};
    if (pilhaVazia(p) == 1) {
        printf("Erro: Pilha vazia!\n");
        return pecaRemovida;
    }
    pecaRemovida = p->itens[p->topo];
    p->topo--;
    return pecaRemovida;
}

void mostrarPilha(Pilha *p) {
    printf("[ PILHA DE RESERVA ]   -> (Capacidade: %d/%d)\n", p->topo + 1, CAPACIDADE_PILHA);
    printf("Base -> ");
    
    if (pilhaVazia(p) == 1) {
        printf("(vazia) ");
    } else {
        for (int i = 0; i <= p->topo; i++) {
            printf("[%c|id:%d] ", p->itens[i].tipo, p->itens[i].id);
            if (i < p->topo) {
                printf("- ");
            }
        }
    }
    printf("<- Topo\n");
}

// ============================================================================
// --- Funções Gerais ---
// ============================================================================

char sortearTipoTetris() {
    char tipos[7] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int indice = rand() % 7;
    return tipos[indice];
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}