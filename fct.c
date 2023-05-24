#include "fct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
   // fprintf(f,"\n");
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
    if (echipa.punctaj < root->team.punctaj) root->left = insert(root->left, echipa);
    else if (echipa.punctaj > root->team.punctaj) root->right = insert(root->right, echipa);
     else if (echipa.punctaj == root->team.punctaj) {
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

void spatii(LISTA team,LISTA team2,FILE *r){
    for(int i=strlen(team.nume_echipa);i<67-strlen(team2.nume_echipa);i++){
       if(i==33)fprintf(r,"-");
       else fprintf(r," ");
    }
   
}

void afisare_pe_nivel(Node *r,int lvl,FILE *f){
    if(r==NULL) return;
    if(lvl==0)fprintf(f,"%s \n",r->team.nume_echipa);
    if(lvl>0){
        afisare_pe_nivel(r->right, lvl-1,f);
        afisare_pe_nivel(r->left, lvl-1,f);
    }
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

void make_sortat_top8(Clasament_list **sortat8,Node *r){
      if(r!=NULL){
        make_sortat_top8(sortat8,r->left);

        Clasament_list *new=(Clasament_list*)malloc(sizeof(Clasament_list));
        new->team=r->team;
        new->urm=(*sortat8);
        (*sortat8)=new;

        make_sortat_top8(sortat8,r->right);
    }
}
void make_AVL(Node **r,Clasament_list *sortat) {
        Clasament_list *cap=(Clasament_list*)malloc(sizeof(Clasament_list));
        cap=sortat;
        sortat=sortat->urm->urm->urm;
        *r=(Node*)malloc(sizeof(Node));
        (*r)->team=sortat->team;
        (*r)->left=(*r)->right=NULL;

    (*r)->right = (Node*)malloc(sizeof(Node));
    (*r)->right->team = cap->urm->team;
    (*r)->right->left = (Node*)malloc(sizeof(Node));
    (*r)->right->left->team = cap->urm->urm->team;
    (*r)->right->right = (Node*)malloc(sizeof(Node));
    (*r)->right->right->team = cap->team;
  
    (*r)->right->left->left = NULL;
    (*r)->right->left->right = NULL;
    (*r)->right->right->left = NULL;
    (*r)->right->right->right = NULL;

    (*r)->left = (Node*)malloc(sizeof(Node));
    (*r)->left->team = sortat->urm->urm->team;
    (*r)->left->left = (Node*)malloc(sizeof(Node));
    (*r)->left->left->team = sortat->urm->urm->urm->team;
    (*r)->left->right = (Node*)malloc(sizeof(Node));
    (*r)->left->right->team = sortat->urm->team;
    (*r)->left->left->left = (Node*)malloc(sizeof(Node));
    (*r)->left->left->left->team = sortat->urm->urm->urm->urm->team;

        (*r)->left->left->left=NULL;
        (*r)->left->right->left=NULL;
        (*r)->left->right->right=NULL;
}
