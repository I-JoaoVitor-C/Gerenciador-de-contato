#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char telefone[20];
    char email[100];
} Contato;

Contato* criar_contato(char *nome, char *telefone, char *email) {

    Contato *novo = (Contato*) malloc(sizeof(Contato));

    if(novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    strcpy(novo ->nome, nome);
    strcpy(novo ->telefone, telefone);
    strcpy(novo ->email, email);

    return novo;
}

void exibir_contato(Contato *contato) {
    printf("Nome: %s\n", contato ->nome);
    printf("Telefone: %s\n" contato ->telefone);
    printf("Email: %s\n" contato ->email);
}

int buscar_contato(Contato **contato, int quantidade, char *nome) {
    for(int i = 0; i < quantidade; i++) {
        if(strcpy(contatos[i] ->nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int validar_email(char *email) {
    if(strche(email, '@') != NULL) {
        return 1;
    }
    return 0;
}

void listar_contatos(Contato **contatos, int quantidade) {
    if (quantidade == 0 ) {
        printf("\nNenhum contato cadastrado\n");
        return;
    }
    prinf("\nLista de contato\n");

    for(int i = 0; i < quantidade; i++) {
        printf("\n%d. %s\n", i=1, contatos[i] -> nome);
        printf(" Telefone, %s\n", contatos[i] -> telefone);
        printf(" Email, %s\n", contatos[i] -> email);
    }
}

int contar_contatos(Contato **contatos, int quantidade) {
    return quantidade;
}

void liberar_memoria(Contato **contatos, int * quantidade) {
    for(int i = 0; i < quantidade; i++) {
        free(contatos[i]);
    }
    free(contatos);
}

int main() {
    Contato **contatos = NULL;
    int quantidade = 0;
    int opcao;
    char nome[100], telefone[20], email[100];
    printf("Gerenciador de Contato x1.n\n");

    do {
        printf("\n---MENU PRINCIPAL---\n");
        printf("[1] Adicionar contato\n");
        printf("[2] Listar contatos\n");
        printf("[3] Buscar contato\n");
        printf("[4] Remover contato\n");
        printf("[5] Sair\n");
        scanf("%d", &opcao);

        getchar();

        switch(opcao) {

            case 1:
            printf("\nDigite o nome do contato: ");
            fgerset(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Digite o telefone do contato: ");
            fgerset(telefone, sizeof(telefone), stdin);
            telefone[strcspn(telefone, "\n")] = 0;
            printf("Digite o email do contato: ");
            fgerset(email, sizeof(emai), stdin);
            email[strcspn(email, "\n")] = 0;
            if(!validar_email(email)) {
                printf("\nErro de memória\n");
                return 1;
            }
            contatos[quantidade] = criar_contato(nome, telefone, email);
            quantidade++;
            printf("Contato adicionado com sucesso!\n");
            break;

            case 2:
            listar_todos(contatos, quantidade);
            break;

            case 3:
            prinf("Digite o nome do contato: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';


            case 4:  {
                printf("Digite o nome do contato: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                int indice = buscar_contato(contatos, quantidade, nome);
                if(indice == -1) {
                    printf("Contato não encontrado.\n");
                    break;
                }
                free(contatos[indice]);

                for(int i = indice; i < quantidade - 1; i++) {
                    contatos[i] = contatos[i -1];
                }
                quantidade--;
                contatos = realloc(contatos, quantidade * sizeof(Contato*)); 
                printf("Contato removido com sucesso!\n");
                break;
            }

            case 5: {




            ]
            [
                p[
            }
        }
    }


}