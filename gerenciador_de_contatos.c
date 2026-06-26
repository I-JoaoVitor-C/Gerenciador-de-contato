#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];     // ← Até 100 caracteres
    char telefone[20];   // ← Até 20 caracteres
    char email[100];    // ← Até 100 caracteres
} Contato;

// ↓ Função Obrigatória: Cria e aloca um contato individualmente
Contato* criar_contato(char *nome, char *telefone, char *email) {
    Contato *novo = (Contato*) malloc(sizeof(Contato));

    if(novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    strcpy(novo->email, email);

    return novo;
}

// ↓ Função Obrigatória: Exibe as informações de um único contato
void exibir_contato(Contato *contato) {
    if (contato != NULL) {
        printf("Nome: %s\n", contato->nome);
        printf("Telefone: %s\n", contato->telefone);
        printf("Email: %s\n", contato->email);
    }
}

// ↓ Função Obrigatória: Busca o contato pelo nome utilizando strcmp
int buscar_contato(Contato **contatos, int quantidade, char *nome) {
    for(int i = 0; i < quantidade; i++) {
        if(strcmp(contatos[i]->nome, nome) == 0) {
            return i; // ← Retorna o índice onde o contato foi encontrado
        }
    }
    return -1; // ← Retorna -1 se não encontrar
}

// ↓ Função Obrigatória: Valida se o e-mail contém o caractere @
int validar_email(char *email) {
    if(strchr(email, '@') != NULL) {
        return 1; // ← E-mail válido
    }
    return 0; // ← E-mail inválido
}

// ↓ Função Obrigatória: Lista todos os contatos cadastrados
void listar_todos(Contato **contatos, int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhum contato cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE CONTATOS ---\n");
    for(int i = 0; i < quantidade; i++) {
        printf("\nContato #%d:\n", i + 1);
        exibir_contato(contatos[i]);
    }
}

// ↓ Função Obrigatória: Retorna a quantidade atual de contatos
int contar_contatos(Contato **contatos, int quantidade) {
    return quantidade;
}

// ↓ Função Obrigatória: Libera toda a memória dinâmica alocada
void liberar_memoria(Contato **contatos, int quantidade) {
    if (contatos != NULL) {
        for(int i = 0; i < quantidade; i++) {
            free(contatos[i]); // ← Libera cada contato individualmente
        }
        free(contatos); // ← Libera o ponteiro de ponteiros
    }
}

int main() {
    Contato **contatos = NULL;
    int quantidade = 0;
    int opcao;
    char nome[100], telefone[20], email[100];

    printf("Gerenciador de Contatos v1.0\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("[1] Adicionar contato\n");
        printf("[2] Listar todos os contatos\n");
        printf("[3] Buscar contato pelo nome\n");
        printf("[4] Remover contato\n");
        printf("[5] Exibir total de contatos\n");
        printf("[6] Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            break;
        }

        getchar(); // ← Limpa o buffer do teclado para o fgets funcionar corretamente

        switch(opcao) {
            case 1: // ← Adicionar contato
                printf("\nDigite o nome do contato: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o telefone do contato: ");
                fgets(telefone, sizeof(telefone), stdin);
                telefone[strcspn(telefone, "\n")] = '\0';

                printf("Digite o email do contato: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                if(!validar_email(email)) {
                    printf("\nErro: Email invalido! Deve conter '@'. Contato nao cadastrado.\n");
                    break;
                }

                // ↓ Aloca espaço na lista para o novo ponteiro de Contato
                Contato **temp = realloc(contatos, (quantidade + 1) * sizeof(Contato*));
                if (temp == NULL) {
                    printf("Erro de memoria ao expandir a lista!\n");
                    break;
                }
                contatos = temp;

                contatos[quantidade] = criar_contato(nome, telefone, email);
                if (contatos[quantidade] != NULL) {
                    quantidade++;
                    printf("Contato adicionado com sucesso!\n");
                }
                break;

            case 2: // ← Listar contatos
                listar_todos(contatos, quantidade);
                break;

            case 3: // ← Buscar contato
                if (quantidade == 0) {
                    printf("\nA lista esta vazia.\n");
                    break;
                }
                printf("\nDigite o nome do contato para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int encontrado = buscar_contato(contatos, quantidade, nome);
                if(encontrado != -1) {
                    printf("\nContato Encontrado:\n");
                    exibir_contato(contatos[encontrado]);
                } else {
                    printf("\nContato nao encontrado.\n");
                }
                break;

            case 4: // ← Remover contato
                if (quantidade == 0) {
                    printf("\nA lista esta vazia.\n");
                    break;
                }
                printf("\nDigite o nome do contato para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int indice = buscar_contato(contatos, quantidade, nome);
                if(indice == -1) {
                    printf("Contato nao encontrado.\n");
                    break;
                }

                // ↓ Libera a memória do contato específico
                free(contatos[indice]);

                // ↓ Desloca os contatos restantes para preencher o espaço vazio
                for(int i = indice; i < quantidade - 1; i++) {
                    contatos[i] = contatos[i + 1];
                }
                quantidade--;

                // ↓ Realoca o tamanho da lista se ainda restarem contatos
                if (quantidade > 0) {
                    contatos = realloc(contatos, quantidade * sizeof(Contato*)); 
                } else {
                    free(contatos);
                    contatos = NULL;
                }
                printf("Contato removido com sucesso!\n");
                break;

            case 5: // ← Contar contatos
                printf("\nTotal de contatos cadastrados: %d\n", contar_contatos(contatos, quantidade));
                break;

            case 6: // ← Sair
                printf("\nEncerrando o programa e liberando memoria...\n");
                liberar_memoria(contatos, quantidade);
                printf("Programa finalizado com sucesso!\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 6);

    return 0;
}