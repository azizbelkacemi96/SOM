
#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#define carre(x) ((x)*(x))

double *moyenne_v,*min,*max;
int * index_array;

    int nbNeuronneLigne=6;
    int nbNeuronneColone=10;
    int tailleVecteur=4;
    int nbIteration=30000;
    double alpha=0.7;
    

void allocation_tab(int n)
{
    vecteur_tab=malloc(n*sizeof(struct vecteur));
    int i;
    for(i=0;i<n;i++)
    {
        vecteur_tab[i].argument=malloc(tailleVecteur*sizeof(double));
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
        somme+=carre(vecteur_tab[i].argument[j]);
    vecteur_tab[i].norme=sqrt(somme);

}

void data()
{
    FILE * in;

    char *str=malloc(sizeof(char)*500);
    in=fopen("iris.data","r");

    int i,j;
 for(i=0;i<150;i++)
 {
        fscanf(in,"%s",str);
        char *tok=strtok(str,",");

        for(j=0;j<tailleVecteur;j++)
            {
                vecteur_tab[i].argument[j]=atof(tok);
                tok=strtok(NULL,",");
            }

        if (strcmp(tok, "Iris-setosa") == 0)
     strcpy(vecteur_tab[i].nom,"S");
        else if(strcmp(tok,"Iris-versicolor")==0)
            strcpy(vecteur_tab[i].nom,"V");
        else
            strcpy(vecteur_tab[i].nom,"G");

        normalisation(i,tailleVecteur);
            printf("%f",vecteur_tab[i].argument);
 }

 fclose(in);
    free(str);
}
void vecteur_moyen (int n)
{
    moyenne_v=malloc(tailleVecteur*sizeof(double));
    memset(moyenne_v,0,tailleVecteur*sizeof(double));

    int i,j;

    for(i=0;i<tailleVecteur;i++)
    {
        for(j=0;j<n;j++)
            moyenne_v[i]+=vecteur_tab[j].argument[i];
        moyenne_v[i]/=n;
    }
}
void max_v(double a)
{
    max=malloc(tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<tailleVecteur;i++)
        max[i]=moyenne_v[i]+a;
}

void min_v(double a)
{
    min=malloc(tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<tailleVecteur;i++)
        min[i]=moyenne_v[i]-a;
}


 shuffle(int n)
{
    int min;
    int max;
     int tmp =0;
     int random = 0;
     int *tabMelange = NULL;
     tabMelange=malloc(n *sizeof(int));
     for (int i = 0; i < n; i++)
     {
         tabMelange[i]=i;
     }
     for (int i = 0; i < n; i++)
     {
         random = rand()%n;
         tmp=tabMelange[i];
         tabMelange[i]=tabMelange[random];
         tabMelange[random]=tmp;
        return tabMelange;
     } 
     
     
}
double distance_eql(double *x, double *y, int n)
{
	double d=0.0;
	int i;
	for(i=0;i<n;i++)
	{
		d+=(carre(x[i] - y[i]));
	}
	return sqrt(d);
}

void map()
{
    int i,j;
    reseau.map=malloc(nbNeuronneColone*sizeof(Neurone *));
	for(i=0;i<nbNeuronneLigne;i++)
	{
		reseau.map[i]=malloc(nbNeuronneLigne*sizeof(Neurone));
	}
	for(i=0;i<nbNeuronneLigne;i++)
	{
		for (j=0;j<nbNeuronneColone;j++)
		{
            reseau.map[i][j].w=(double*)malloc(sizeof(double)*tailleVecteur);
			reseau.map[i][j].etiquette=malloc(20*sizeof(char));
			strcpy(reseau.map[i][j].etiquette, ".");
		}
	}
}
void affiche_map()
{
    int i,j;
    for(i=0;i<nbNeuronneLigne;i++)
    {
        for(j=0;j<nbNeuronneColone;j++)
            {
                printf("%s ",reseau.map[i][j].etiquette);
            }
        printf("\n");
    }
}

int main () {
    allocation_tab(150);
    data();
    vecteur_moyen(150);
    min_v (0.005);
    max_v (0.005);
    printf("\n");
    map();
    affiche_map();
    return 0;
}
