#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um arquivo ou pasta
typedef struct Node {
    char nome[100];
    int verificaPasta; // 1 se for pasta, 0 se for arquivo
    struct Node* pai;
    struct Node* filho;
    struct Node* irmao;
} Node;

// Função para criar um novo nó
Node* criarNo() {
Node* novoNo = (Node*)malloc(sizeof(Node));
novoNo->verificaPasta = 1;
novoNo->pai = NULL;
novoNo->filho = NULL;
novoNo->irmao = NULL;
return novoNo;
}

// Função para adicionar um nó filho a um nó pai
void adicionarFilho(Node* pai, Node* filho) {
    if (pai == NULL || filho == NULL) {
        return;
    }
    
    filho->pai = pai;
    
    if (pai->filho == NULL) {
        pai->filho = filho;
    } else {
        Node* atual = pai->filho;
        while (atual->irmao != NULL) {
            atual = atual->irmao;
        }
        atual->irmao = filho;
    }
}

// mostrar caminho

// Função para mostrar o conteúdo de uma pasta
void mostrarConteudo(Node* pasta ) {
    if (pasta == NULL || pasta->filho == NULL) {
        printf("Pasta vazia\n");
        return;
    }

    printf("Conteúdo da pasta:\n");
    Node* arquivo = pasta->filho; // Pega o primeiro arquivo/pasta filho
    while (arquivo != NULL) {// Enquanto houver arquivos/pastas
        printf("%s%s\n", arquivo->nome, (arquivo->verificaPasta ? "--" : "")); // Adiciona '/' para pastas
        arquivo = arquivo->irmao;
    }
}

// Função para criar um novo arquivo
void criarArquivo(Node* atual, char par) {
    Node* novoArquivo = criarNo(par, atual, 0); // Cria um novo nó para o arquivo
    adicionarFilho(atual, novoArquivo);// Adiciona o arquivo como filho do nó atual
    printf("Arquivo criado com sucesso!\n");
}

// Função para acessar uma pasta
Node* acessarPasta(Node *pasta, char par[]) {
    if (strcmp(par, "..") == 0) {
        return (pasta->pai != NULL) ? pasta->pai : pasta;
    }
    Node *atual = pasta->filho;
    while (atual != NULL) {
        if (atual->verificaPasta && strcmp(atual->nome, par) == 0) {
            return atual;
        }
        atual = atual->irmao;
    }
    return NULL;
}


// Função para apagar um nó e seus descendentes
void apagarNode(Node* node) {
        if (node == NULL) {
            return;
        }

        apagarNode(node->filho);
        
        if (node->pai != NULL) {
            Node* parent = node->pai;
            if (parent->filho == node) {
                parent->filho = node->irmao;
            } else {
                Node* aux = parent->filho;
                while (aux->irmao != node) {
                    aux = aux->irmao;
                }
               aux->irmao = node->irmao;
            }
        }
        
        free(node);
    }


// Função para remover um arquivo ou pasta
void remover(Node* node) {

    if (node == NULL) {
        printf("Arquivo ou pasta não encontrada\n");
        return;
    }

    if (node->verificaPasta) {
        apagarNode(node);
        printf("Pasta removida com sucesso!\n");
    } else {
        if (node->pai != NULL) {
            Node* parent = node->pai;
            if (parent->filho == node) {
                parent->filho = node->irmao;
            } else {
                Node* aux = parent->filho;
                while (aux->irmao != node) {
                    aux = aux->irmao;
                }
                aux->irmao = node->irmao;
            }
        }
        free(node);
        printf("Arquivo removido com sucesso!\n");
    }
}

void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

int main() {
    char str[14],cmd[3],par[11];

    Node* raiz = criarNo("raiz", NULL, 1);
    Node* atual = raiz;

    do{
        imprimirCaminho(atual);
        
        fflush(stdin);
        gets(str);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        
        if (strcmp(cmd, "ma") == 0) { //criar
            criarArquivo(atual, *par);
        } else if (strcmp(cmd, "rm") == 0) { //remover
            remover(atual); 
        } else if (strcmp(cmd, "mp") == 0){ //criar pasta
            criarNo();
        }
         else if (strcmp(cmd, "ls") == 0) { //mstrar conteudo pasta
            mostrarConteudo(atual); 

        } else if (strcmp(cmd, "ex") == 0) { //sair
            printf("Encerrando o programa...\n");
        } else {
            printf("Comando inválido\n");
        }

    }while(strcmp(cmd,"ex")!=0);
    return 0;
    
}

           