
#include <stdio.h>
#include "fct.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

int main(int argc, char *argv[]){
       FILE *c=fopen(argv[1], "r+"); 
        FILE *d=fopen(argv[2], "r+");
        FILE *r=fopen(argv[3], "w+");
        int nr_echipe,i;
        int *cr=(int*)malloc(5*sizeof(int));
        cerinte(cr,c);
        fseek(d,0,0);
        fscanf(d,"%d",&nr_echipe);

    LISTA *p=cerinta_1(nr_echipe,d);
    LISTA *cap=p;
   if(cr[1]==1){
   int k=cate_echipe_trebuie_eliminate(nr_echipe);
    nr_echipe=nr_echipe-k;
    for(i=0; i<k; i++){
        float scor_de_eliminat=scor_minim(cap);
        sters_din_lista(&cap,scor_de_eliminat);
    }
   }
   afisare_lista(r,cap);
   
    if(cr[2]==1 || cr[3]==1 || cr[4]==1){
    Clasament_list *top8=cerinta_3(cap,r,nr_echipe,cr);
    Clasament_list *cap8=top8;
    Node *root=(Node*)malloc(sizeof(Node)); root=NULL;
    top8=cap8;
    while(top8){
        root=insert(root,top8->team);
        top8=top8->urm;
    }
    if(cr[3]==1){
    fprintf(r,"TOP 8 TEAMS:\n");
    afisare_DRS(root,r);
}
   // eliberare_lista(top8);
    if(cr[4]==1){
    Clasament_list *sortat8=(Clasament_list*)malloc(sizeof(Clasament_list));
    Node *AvlRoot=NULL;
    make_sortat_top8(&sortat8,root);
    make_AVL(&AvlRoot,sortat8);
    fprintf(r,"\nTHE LEVEL 2 TEAMS ARE:\n");
    afisare_pe_nivel(AvlRoot,2,r);
    }
    }
    fclose(r);
    fclose(d); 
    return 0;
}