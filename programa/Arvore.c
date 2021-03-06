#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct tree {
    char info;
    struct tree *left;
    struct tree *right;
};

struct tree *root; /* o primeiro nó da árvore */

struct tree *stree(struct tree *, struct tree *, char);
void inorder(struct tree *), preorder(struct tree *), postorder(struct tree *);
void print_tree(struct tree *, int);
struct tree *search_tree(struct tree *, char);

main(void) {
setlocale(LC_ALL,""); 
    char s[80];
    struct tree *result;

    root = NULL; /* inicializa a raiz */

    do {
        printf("insira uma letra: ");
        gets(s);
        if (!root)
            root = stree(root, root, *s);
        else
            stree(root, root, *s);
    } while(*s);

    printf("Árvore\n");
    print_tree(root, 0);

    printf("\n\nOrdenada\n");
    inorder(root);

    printf("\n\nPré-ordenada\n");
    preorder(root);

    printf("\n\nPós-ordenada\n");
    postorder(root);
    
    result = search_tree(root, 'a');
    if (result) printf("\n\nEncontrado: %c\n", result->info);
    else printf("\n\nLetra 'a' não encontrada.\n");
    
}

struct tree *stree(struct tree *root, struct tree *r, char info) {
    if (!r) {
        /* aloca espaço para o novo nó */
        r = (struct tree *)malloc(sizeof(struct tree));
        if (!r) {
            printf("sem memória\n");
            exit(0);
        }

        /* Um novo nó ainda não tem filhos */
        r->left = NULL;
        r->right = NULL;
        r->info = info;

        if (!root) return r; /* primeira entrada */

        /* coloca o nó abaixo da raiz esquerda ou direita de acordo com o conteúdo */
        if (info < root->info)
            root->left = r;
        else
            root->right = r;

        return r;
    }

    /* se chama recursivamente até encontrar a posição adequada para o novo elemento */
    if (info < r->info)
        stree(r, r->left, info);
    else
        stree(r, r->right, info);
}

/* Percorre a arvore de forma ordenada */
void inorder(struct tree *root) {
    if (!root) return; /* se encontrar um nó terminal retorna */

    inorder(root->left);
    if (root->info) printf("%c ", root->info);
    inorder(root->right);
}

/* Percorre a lista de forma pré-ordenada */
void preorder(struct tree *root) {
    if (!root) return; /* se encontrar um nó terminal retorna */

    if (root->info) printf("%c ", root->info);
    preorder(root->left);
    preorder(root->right);
}

/* Percorre a lista de forma pós-ordenada */
void postorder(struct tree *root) {
    if (!root) return; /* se encontrar um nó terminal retorna */

    postorder(root->left);
    postorder(root->right);
    if (root->info) printf("%c ", root->info);
}

/* Imprime a árvora no formato de árvore */
void print_tree(struct tree *r, int l) {
    int i;
    if (!r) return;

    print_tree(r->right, l+1);
    for (i = 0; i < l; ++i) printf("    ");
    printf("%c\n", r->info);
    print_tree(r->left, l+1);
}

/* Encontra um nó na árvore */
struct tree *search_tree(struct tree *root, char key) {
    if (!root) return root;
    while (root->info != key) {
        root = (key < root->info) ? root->left : root->right;
        if (root == NULL) break;
    }
    return root;
}
