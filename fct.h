#include <stdio.h>

typedef struct Lan{
       char* firstName;
       char* secondName;
       int points;
}PLAYER;

typedef struct lista_echipe{
    char nume_echipa[50];
    int nr_playeri;
    float punctaj;
    PLAYER *info;
    
    struct lista_echipe *urm;
}LISTA;

typedef struct stack{
    LISTA team;
    struct stack *urm;
}STIVA;

typedef struct queue{
    LISTA team;
    struct queue *urm;
    struct queue *front,*rear;
}COADA;

typedef struct clasament{
    LISTA team;
    struct clasament *urm;
}Clasament_list;

typedef struct arbore{
    LISTA team;
    struct arbore *left,*right;
}Node;

void AddAtBeggining(LISTA **cap, PLAYER x[], int nr_playeri,char nume_echipa[]);
void afisare_lista(FILE *f,LISTA *cap);
float puncte_echipa (LISTA p);
int cate_echipe_trebuie_eliminate(int nr_echipe);
float scor_minim(LISTA *cap);
void sters_din_lista(LISTA **cap, float key);
void enQueue(COADA **c,LISTA p);
void deQueue(COADA **c);
void push(STIVA **s,LISTA p,int *top);
void pop (STIVA **s,int *top);
void stack_display(FILE *f,STIVA *s);
void stergere_recursiva(STIVA **cap);
LISTA top(STIVA *s);
void eliberare_lista(LISTA **cap);
void AddAtBeggining2( Clasament_list **top8,LISTA echipa);
void afisare_DRS(Node *r,FILE *f);
Node *insert(Node *root,LISTA echipa);
void cerinte(int c[],FILE *f);
void spatii(LISTA team,LISTA team2,FILE *r);
void afisare_pe_nivel(Node *r,int lvl,FILE *f);
void make_AVL(Node **r,Clasament_list *sortat8);
void make_sortat_top8(Clasament_list **sortat8,Node *r);
LISTA * cerinta_1(int nr_echipe,FILE *d);
Clasament_list* cerinta_3(LISTA *p,FILE *r,int nr_echipe,int cr[]);
void free_tree(Node* root) ;