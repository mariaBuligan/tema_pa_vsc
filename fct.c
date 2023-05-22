#include "fct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void afisare_fisier(FILE *f){
    fseek(f,0,SEEK_SET);
    char c;
    while((c=getc(f))!=EOF){
        printf("%c",c);
    }
    printf("\n");
}
void AddAtBeggining(LISTA **cap, PLAYER x[], int nr_playeri,char nume_echipa[]){
    float m=0;
    LISTA *new=(LISTA*)malloc(sizeof(LISTA));
    new->info=(PLAYER*)malloc(sizeof(PLAYER));
    
    new->nr_playeri=nr_playeri;
    strcpy(new->nume_echipa,nume_echipa);

    for(int i=0;i< new->nr_playeri;i++){
        new->info[i].firstName=(char*)malloc(20* sizeof(char));
        new->info[i].secondName=(char*)malloc(20*sizeof(char));
        
        strcpy(new->info[i].firstName, x[i].firstName);
        strcpy(new->info[i].secondName, x[i].secondName);
        new->info[i].points=x[i].points;
        m=m+new->info[i].points;
    }
    new->punctaj=m/(new->nr_playeri);
    new->urm=*cap;
    *cap=new;
    
}

void AddAtBeggining2( Clasament_list **top8,LISTA echipa){
    Clasament_list *new=(Clasament_list*)malloc(sizeof(Clasament_list));
    new->team=echipa;
    new->urm=*top8;
    *top8=new;
}

void afisare_lista(FILE *f,LISTA *cap){
    while (cap) {
        fprintf(f,"%s\n",cap->nume_echipa);
        cap=cap->urm;
    }
    fprintf(f,"\n");
}

int cate_echipe_trebuie_eliminate(int nr_echipe){
    int k=1;  
    while((k*2)<nr_echipe)
        k=k*2;
    
    return (nr_echipe-k);
}

float puncte_echipa (LISTA p){
    
    int s=0;
    float media;
    for(int i=0;i<p.nr_playeri;i++){
            s=s+p.info[i].points;
    }
    media=(float)s/p.nr_playeri;
    return media;
}
float scor_minim(LISTA *cap){
    
    float min=INT_MAX;
    while(cap){
        float scor=puncte_echipa(*cap);
        if(scor<min)  min=scor;
        cap=cap->urm;
    }
    return min;
}

void sters_din_lista(LISTA **p, float key) {
  
    LISTA *current = *p;
    LISTA *prev = NULL;
    
    while (current != NULL) {
        if (puncte_echipa(*current) == key) {
            if (prev == NULL){
                *p = current->urm;
            } else {
                prev->urm = current->urm;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->urm;
    }
}

void enQueue(COADA **c, LISTA p){
    COADA *new=(COADA*)malloc(sizeof(COADA));
    new->team=p;
    new->rear=NULL;
    new->front=NULL;
    new->urm=NULL;
    
    if((*c)->front==NULL)(*c)->front=(*c)->rear=new;
    else {
        ((*c)->rear)->urm=new;
        (*c)->rear=new;
    }
   
}
void deQueue(COADA **c){
   
    if((*c)->front==NULL || (*c)->rear==NULL)return;

    if((*c)->front==(*c)->rear){
        free((*c)->front);
        (*c)->front=(*c)->rear=NULL;
        return;
    }
    else{
         COADA *aux;
        aux=(*c)->front;
        (*c)->front=((*c)->front)->urm;
        free(aux);
    }
} 

void queue_display(COADA *c){
    printf("Coada actuala este:\n");
    while(c){
        printf("%s ",c->team.nume_echipa);
        c=c->urm;
    }
    printf("\n");
}

void push(STIVA **s,LISTA echipa,int *top){
    STIVA *new=(STIVA*)malloc(sizeof(STIVA));
        *top= *top+1;
        new->team=echipa;
        new->urm=*s;
        *s=new;
}

void pop (STIVA **s,int *top){
   
    if(*top<0){
        printf("Lista e goala\n");
        return;
    }
    else{
        STIVA *temp=(*s);
        *top=*top -1;
        *s=(*s)->urm;
        free(temp);
    }
    
}
void stack_display(FILE *f,STIVA *s){
    while(s!=NULL){
        fprintf(f,"%s",s->team.nume_echipa);
        for(int i=strlen(s->team.nume_echipa);i<=33;i++){
            fprintf(f," ");
        }
        fprintf(f,"-  ");
        fprintf(f,"%3.2f\n",s->team.punctaj);
        s=s->urm;
    }
    fprintf(f,"\n");
}
void stergere_recursiva(STIVA **cap){
    if(*cap==NULL)return;
    else {
        stergere_recursiva(&((*cap)->urm));
        free(*cap);
        *cap=NULL;
    }
}
LISTA top(STIVA *s){
    return s->team;
}

void eliberare_lista(LISTA *cap){
    LISTA *aux=cap;
    while(aux!=NULL){
        LISTA *next=aux->urm;
        free(aux->nume_echipa);
        for(int i=0;i<aux->nr_playeri;i++){
            free(aux->info[i].firstName);
            free(aux->info[i].secondName);
        }
        free(aux->info);
        free(aux);
        aux=next;
    }
}

Node* newNode(LISTA echipa){
    Node *node= (Node*)malloc(sizeof(Node));
    node->team=echipa;
    node->left = node->right = NULL; 
    return node;
}
Node* insert(Node* root, LISTA echipa){
    if (root == NULL) return newNode(echipa);
    //printf("PUN:%s %f %f\n",echipa.nume_echipa,echipa.punctaj,root->team.punctaj);
    if (echipa.punctaj < root->team.punctaj) root->left = insert(root->left, echipa);
    else if (echipa.punctaj > root->team.punctaj) root->right = insert(root->right, echipa);
     else if (echipa.punctaj == root->team.punctaj) {
       // printf("%d",strcmp(echipa.nume_echipa,root->team.nume_echipa));
        if(strcmp(root->team.nume_echipa,echipa.nume_echipa)>0)  root->left = insert(root->left,echipa);
        if(strcmp(root->team.nume_echipa,echipa.nume_echipa)<0)  root->right = insert(root->right,echipa);
    }
    return root;
}

void afisare_DRS(Node *r,FILE *f){
    if(r!=NULL){
        afisare_DRS(r->right,f);
        fprintf(f,"%s",r->team.nume_echipa);
        for(int i=strlen(r->team.nume_echipa);i<=33;i++){
            fprintf(f," ");
        }
        fprintf(f,"-  ");
        fprintf(f,"%3.2f\n",r->team.punctaj);
        afisare_DRS(r->left,f);    
    }
}

void cerinte(int c[],FILE *f){
   fscanf(f,"%d %d %d %d %d",&c[0],&c[1],&c[2],&c[3],&c[4]);
}

Node *rightRotation(Node *z) {
    Node *y = z->left;
    Node *x = y->right;
    y->right = z;
    z->left = x;
    return y;
}

Node *leftRotation(Node *z) {
    Node *y = z->right;
    Node *x = y->left;
    y->left = z;
    z->right = x;
    return y;
}

Node* LRRotation(Node*Z) {
    Z->left = leftRotation(Z->left);
    return rightRotation(Z);
}

Node* RLRotation(Node*Z) {
    Z->right = rightRotation(Z->right);
    return leftRotation(Z);
}

Node *copie_arbore(Node *root){
    if(root==NULL) return NULL;
    
    Node *cpy=newNode(root->team);
    cpy->left=copie_arbore(root->left);
    cpy->right=copie_arbore(root->right);

    return cpy;
}
void spatii(LISTA team,LISTA team2,FILE *r){
    for(int i=strlen(team.nume_echipa);i<67-strlen(team2.nume_echipa);i++){
       if(i==34)fprintf(r,"-");
       else fprintf(r," ");
    }
   
}
void afisare_pe_nivel(Node *r,int lvl,FILE *f){
   // printf("new lvl:");
    if(r==NULL) return;
    if(lvl==0)fprintf(f,"%s \n",r->team.nume_echipa);
    if(lvl>0){
        afisare_pe_nivel(r->left, lvl-1,f);
        afisare_pe_nivel(r->right, lvl-1,f);
    }
   // printf("\n");
}
int height(Node *r){
    int hs,hd;
    if(r==NULL)return -1;
    hs=height(r->left);
    hd=height(r->right); 

    if (hs > hd) 
        return (1 + hs);
    else     return (1 + hd);
}
int isAVL(Node *r){
    if(abs(height(r->left) - height(r->right))<=1)
            return 1;
        else return 0;
}
/* void make_AVL(Node **r){

    if(height((*r)->left)>height((*r)->right)){
        Node *aux=(*r)->left;
        if(aux->left!=NULL && aux->left->left!=NULL)(*r)->left=rightRotation(aux);
        else if(aux->left!=NULL && aux->left->right!=NULL)(*r)->left=LRRotation(aux);
        free(aux);
    }
     else{
        Node *aux=(*r)->right;
        if(aux->right!=NULL && aux->right->right!=NULL)(*r)->right=leftRotation(aux);
        else if(aux->right!=NULL && aux->right->left!=NULL)(*r)->right=RLRotation(aux);
        free(aux);
    }   
     
    if(isAVL(*r)==0)make_AVL(r);
} */
void make_AVL(Node **r) {
    int balanceFactor = height((*r)->left) - height((*r)->right);

    if (balanceFactor > 1) {
        if (height((*r)->left->left) >= height((*r)->left->right))
            (*r) = rightRotation(*r);
        else
            (*r) = LRRotation(*r);
    } else if (balanceFactor < -1) {
        if (height((*r)->right->right) >= height((*r)->right->left))
            (*r) = leftRotation(*r);
        else
            (*r) = RLRotation(*r);
    }

    if (isAVL(*r) == 0)
        make_AVL(r);
}
