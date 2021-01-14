
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
int * tab_index;
bmu *bestU = NULL;
    int best_size=1;
    int nbNeuronneLigne=6;
    int nbNeuronneColone=10;
    int tailleVecteur=4;
    int nbIteration=30000;
    double alpha=0.7;
    int train=2;
    int ftrain= 30000/5;



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
            printf("%d",vecteur_tab[i].argument);
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


void init_shuffle(int n)
{
    tab_index=malloc(sizeof(int)*n);
    int i;
    for(i=0;i<n;i++)
        tab_index[i]=i;
}
/**
On le met de façon alétoire
**/
void shuffle(int n)
{
    int i,r_and,k;
    srand(time(NULL));
    for(i=0;i<n;i++)
        {
            r_and=rand()%n;
            k=tab_index[i];
            tab_index[i]=tab_index[r_and];
            tab_index[r_and]=k;
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

void update(bmu* b_mu)
{
    int voisin=reseau.voisinage;
    int i,j,x1,x2,y1,y2;

    for(;voisin>=0;voisin--)
    {
        if(b_mu->r-voisin<0)
            x1=0;
        else
            x1=b_mu->r-voisin;
        if(b_mu->c-voisin<0)
            y1=0;
        else
            y1=b_mu->c-voisin;

        if(b_mu->r+voisin>nbNeuronneLigne-1)
            x2=nbNeuronneLigne-1;
        else
            x2=b_mu->r+voisin;
        if(b_mu->c+voisin>nbNeuronneColone-1)
            y2=nbNeuronneColone-1;
        else
            y2=b_mu->c+voisin;

        for(i=x1;i<=x2;i++)
            for(j=y1;j<=y2;j++)
            {

                int k;

                for(k=0;k<tailleVecteur;k++)
                    {

                        reseau.map[i][j].w[k]+=reseau.alpha*(reseau.vecteur_courant[k]-reseau.map[i][j].w[k]);
                    }
            }
    }
}
double* init_rand_w()
{
    int i;
    double k=(double)rand()/RAND_MAX;
    double *tmp_w=malloc(tailleVecteur*sizeof(double));

    for(i=0;i<tailleVecteur;i++)
        {
            tmp_w[i]=k*(max[i]-min[i])+min[i];
        }

    double norm=0.;

    for(i=0;i<tailleVecteur;i++)
    {
        norm+=carre(tmp_w[i]);
    }

    for(i=0;i<tailleVecteur;i++)
    {
            tmp_w[i]/=norm;
    }
    return tmp_w;
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
            reseau.map[i][j].w=init_rand_w();
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


/**
Fonction pour calculer le α a chaque fois
(pas sur que ca soit exdistance_eqlement ca a revoir )
**/

void calc_alpha(int it_n, int tot_it)
{
    reseau.alpha = alpha * (1 - ((double)it_n/(double)tot_it));
}
void training()
{
    int i,j,p,u,it;
    double min_d,dist;

    bestU=malloc(sizeof(bmu));

    for(p=0;p<train;p++)
    {
        int cur_n_it;
        if(!p)
        {
            cur_n_it=ftrain;
        }
        else
        {
            cur_n_it=nbIteration-ftrain;
            alpha=0.07;
            reseau.voisinage=1;
        }

        for(it=0;it<cur_n_it;it++)
        {
            calc_alpha(it,cur_n_it);

            if(it%(ftrain/2)==0&&it!=0&&p==0)
            {
                reseau.voisinage-=1;
            }


            shuffle(150);

            for(u=0;u<150;u++)
            {

                reseau.vecteur_courant=vecteur_tab[tab_index[u]].argument;
                min_d=1000.;
                for(i=0;i<nbNeuronneLigne;i++)
                {
                    for(j=0;j<nbNeuronneColone;j++)
                    {
                        dist=distance_eql(reseau.vecteur_courant,reseau.map[i][j].w,tailleVecteur);
                        reseau.map[i][j].distance_eql=dist;
                        if(dist<min_d)
                        {
                            min_d=dist;
                            if(best_size>1)
                            {
                                best_size=1;
                                bestU=realloc(bestU,best_size*sizeof(bmu));
                            }
                            bestU[0].distance_eql=dist;
                            bestU[0].r=i;
                            bestU[0].c=j;
                        }
                        else if(dist==min_d)
                        {

                            best_size++;
                            bestU=realloc(bestU,best_size*sizeof(bmu));
                            bestU[best_size-1].distance_eql=dist;
                            bestU[best_size-1].r=i;
                            bestU[best_size-1].c=j;

                        }
                    }
                }

                if(best_size>1)
                {
                    int t=rand()%(best_size);
                    bestU[0]=bestU[t];
                }

                strcpy(reseau.map[bestU[0].r][bestU[0].c].etiquette, vecteur_tab[tab_index[u]].nom);
                update(bestU);
            }
        }
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
    reseau.voisinage=6;
    reseau.alpha=0;
    training();
    printf("apres l algorithm SOM:\n");
    affiche_map();
    free(moyenne_v);
    free(min);
    free(max);
    return 0;
}
