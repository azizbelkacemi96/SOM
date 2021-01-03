
#include "Structs.h"

double *moyenne_v,*min,*max;
#define SQR(x) ((x)*(x))

void alloc_array_struct(int n)
{
    vecteur_tab=malloc(n*sizeof(struct vecteur));
    int i;
    for(i=0;i<n;i++)
    {
        vecteur_tab[i].argument=malloc(N_conf.n_in*sizeof(double));
        vecteur_tab[i].nom=malloc(20*sizeof(char));
    }
}

/*
Normalisation 
*/

void normalisation(int i,int size )
{
    double somme=0.;
    int j;
    for(j=0;j<size;j++)
        somme+=SQR(vecteur_tab[i].argument[j]);
    vecteur_tab[i].norme=sqrt(somme);

}

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
            printf("%d",vecteur_tab[i].argument);
 }

 fclose(in);
    free(str);
}

void max_v(double k)
{
    max=malloc(N_conf.n_in*sizeof(double));
    int i;
    for(i=0;i<N_conf.n_in;i++)
        max[i]=moyenne_v[i]+k;
}

void min_v(double k)
{
    min=malloc(N_conf.n_in*sizeof(double));
    int i;
    for(i=0;i<N_conf.n_in;i++)
        min[i]=moyenne_v[i]-k;
}

void vecteur_moyen (int n)
{
    moyenne_v=malloc(N_conf.n_in*sizeof(double));
    memset(moyenne_v,0,N_conf.n_in*sizeof(double));

    int i,j;

    for(i=0;i<N_conf.n_in;i++)
    {
        for(j=0;j<n;j++)
            moyenne_v[i]+=vecteur_tab[j].argument[i];
        moyenne_v[i]/=n;
    }
}
int main () {
    alloc_array_struct(150);

    read_data();
    return 0;
}
