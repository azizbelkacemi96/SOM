
#include "Structs.h"

double *moyenne_v,*min,*max;

void init_n_conf()
{
    conf.nbNeuronneLigne=6;
    conf.nbNeuronneColone=10;
    conf.tailleNeuronne=conf.nbNeuronneLigne*conf.nbNeuronneColone;
    conf.tailleVecteur=4;
    conf.nbIteration=30000;
    conf.alpha=0.7;
    conf.ftrain=conf.nbIteration/5;
    conf.train=2;
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

        for(j=0;j<conf.tailleVecteur;j++)
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

        normalisation(i,conf.tailleVecteur);
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
            print("%f",data[i].vecteur[i]);
        }
        print("%s",data[i].etiquette);

    }
}
void max_v(double k)
{
    max=malloc(conf.tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<conf.tailleVecteur;i++)
        max[i]=moyenne_v[i]+k;
}

void min_v(double k)
{
    min=malloc(conf.tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<conf.tailleVecteur;i++)
        min[i]=moyenne_v[i]-k;
}
/*
Normalisation 
*/

void Normalisation(int i,int size )
{
    double somme=0.;
    int j;
    for(j=0;j<size;j++)
        somme+=SQR(vecteur_tab[i].argument[j]);
    vecteur_tab[i].norme=sqrt(somme);
}

void vecteur_moyen (int n)
{
    moyenne_v=malloc(conf.tailleVecteur*sizeof(double));
    memset(moyenne_v,0,conf.tailleVecteur*sizeof(double));

    int i,j;

    for(i=0;i<conf.tailleVecteur;i++)
    {
        for(j=0;j<n;j++)
            moyenne_v[i]+=vecteur_tab[j].argument[i];
        moyenne_v[i]/=n;
    }
}
int main () {
    void AficheData();
    return 0;
}