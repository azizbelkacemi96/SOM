
#include "Structs.h"
void init_n_conf()
{
    N_conf.n_l_out=6;
    N_conf.n_c_out=10;
    N_conf.n_out=N_conf.n_l_out*N_conf.n_c_out;
    N_conf.n_in=4;
    N_conf.nb_it=30000;
    N_conf.minAlpha=0.7;
    N_conf.ftrain=N_conf.nb_it/5;
    N_conf.train=2;
}
void read_data()
{
    FILE * in;

    char *str=malloc(sizeof(char)*500);
    in=fopen("iris.data","r");

    int i,j;
 for(i=0;i<150;i++)
 {
        fscanf(in,"%s",str);
        char *tok=strtok(str,",");

        for(j=0;j<N_conf.n_in;j++)
            {
                vecteur_tab[i].argument[j]=atof(tok);
                tok=strtok(NULL,",");
            }

        if (strcmp(tok, "Iris-setosa") == 0)
     strcpy(vecteur_tab[i].nom,"A");
        else if(strcmp(tok,"Iris-versicolor")==0)
            strcpy(vecteur_tab[i].nom,"B");
        else
            strcpy(vecteur_tab[i].nom,"C");

        normalisation(i,N_conf.n_in);
 }

 fclose(in);
    free(str);
}

/*
Afficher mes data 
*/
void AficheData(Data* data,int Ligne,int collone){
    for(int i=0; i< Ligne;i++){
        print("%d",i+1);
        for (int j=0; j< collone;j++) {
            print("%f",data[i].vect[i]);
        }
        print("%s",data[i].etiquette);

    }
}