
#include <stdio.h>
#include "fct.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

int main(int argc, char **argv){

        char *cale1 = argv[1];
        char *cale2 = argv[0];
        char *cale3 = argv[2];
        LISTA *p=NULL,*cap=NULL;
        FILE *d=fopen("d.in", "r+");
        FILE *r=fopen("r.out", "w+");
        FILE *c=fopen("c.in","r+");
        int nr_echipe,i;
        char nume_echipa[50];
        int *cr=(int*)malloc(5*sizeof(int));
        cerinte(cr,c);
        fseek(d,0,0);
        fscanf(d,"%d",&nr_echipe);
 
    for(i=0;i<nr_echipe;i++){
        int nr_playeri;
        fscanf(d,"%d ",&nr_playeri);
        fgets(nume_echipa,50,d);
        nume_echipa[strlen(nume_echipa)-1]='\0';
        PLAYER *jucator=(PLAYER*)malloc(nr_playeri*sizeof(PLAYER));
        for(int j=0;j< nr_playeri;j++){
            jucator[j].firstName=(char*)malloc(20*sizeof(char));
            jucator[j].secondName=(char*)malloc(20*sizeof(char));
            
            fscanf(d,"%s %s %d", jucator[j].firstName,jucator[j].secondName,&jucator[j].points);    
        }
        fscanf(d,"\n");
        AddAtBeggining(&p, jucator, nr_playeri, nume_echipa);
    }
   
   cap=p;
   int k=cate_echipe_trebuie_eliminate(nr_echipe);
    nr_echipe=nr_echipe-k;
    for(i=0; i<k; i++){
        float scor_de_eliminat=scor_minim(cap);
        sters_din_lista(&cap,scor_de_eliminat);
    }
    if(cr[1]==1)afisare_lista(r,cap);

    Clasament_list *top8=NULL,*cap8=NULL;
    STIVA *s_invinsi=(STIVA*)malloc(sizeof(STIVA)); s_invinsi=NULL; int top1=-1;
    STIVA *s_castigatori=(STIVA*)malloc(sizeof(STIVA)); s_castigatori=NULL; int top2=-1;
    COADA *q=(COADA*)malloc(sizeof(COADA));
     q->front=q->rear=NULL;
    for(p=cap;p!=NULL;p=p->urm){
        enQueue(&q,*p);
    }
   for(int i=1;i<=log2(nr_echipe);i++){
    if(cr[2]==1)fprintf(r,"--- ROUND NO:%d\n",i);
        while(q->front!=NULL){
        float pct_1=q->front->team.punctaj;
        float pct_2=q->front->urm->team.punctaj;
        if(cr[2]==1){
        fprintf(r,"%s",q->front->team.nume_echipa);
        spatii(q->front->team,q->front->urm->team,r);
        fprintf(r,"%s\n",q->front->urm->team.nume_echipa); 
        }
         if(i==log2(nr_echipe)-2){
             AddAtBeggining2(&top8,q->front->team);
             AddAtBeggining2(&top8,q->front->urm->team);
         }
        if(pct_1>=pct_2){
             q->front->team.punctaj ++;
            push(&s_castigatori,q->front->team,&top1);
            push(&s_invinsi,q->front->urm->team,&top2);
        }
       else if(pct_1<pct_2){
             q->front->urm->team.punctaj ++;
             push(&s_castigatori,q->front->urm->team,&top1);
             push(&s_invinsi,q->front->team,&top2);
       }
        deQueue(&q);
        deQueue(&q);
     }
     if(cr[2]==1){
      fprintf(r,"\nWINNERS OF ROUND NO:%d\n",i);
      stack_display(r,s_castigatori);
     }
                while(top1>=0){  
                     enQueue(&q,(top(s_castigatori)));
                     pop(&s_castigatori,&top1);
                }
    stergere_recursiva(&s_invinsi);
   }

    cap8=top8;
    Node *root=(Node*)malloc(sizeof(Node));
    root=NULL;
    top8=cap8;
    while(top8){
        root=insert(root,top8->team);
        top8=top8->urm;
    }
    if(cr[3]==1){
    fprintf(r,"TOP 8 TEAMS:\n");
    afisare_DRS(root,r);
}
    if(cr[4]==1){
    Node *AvlRoot=(Node*)malloc(sizeof(Node));
    AvlRoot=NULL;
    AvlRoot=copie_arbore(root);
    fprintf(r,"\nTHE LEVEL 2 TEAMS ARE:\n");
    printf("%d %d",height(AvlRoot->left),height(AvlRoot->right));
    if(isAVL(AvlRoot)==1)afisare_pe_nivel(AvlRoot,2,r);
    else {
        make_AVL(&AvlRoot);
        printf("%d %d",height(AvlRoot->left),height(AvlRoot->right));
        afisare_pe_nivel(AvlRoot,2,r);
    }
}
    //eliberare_lista(cap);
    //free(top8);
    fclose(r);
    fclose(d); 
    return 0;
}