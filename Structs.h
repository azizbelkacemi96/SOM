#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>


typedef Data Data;
struct Data
{
    double* vecteur;
    char* etiquette;
    double* norme;
};

struct N_config
 {
   int n_in; //variable pour la taille du vecteur
   int n_l_out; // nombre de neuron map sur ligne
   int n_c_out; // npmbre de neuron sur colone
   int n_out; //total neuron (n_l_out * n_c_out)
   int nb_it; // Nombre d'iterations qu'on calcule avec la methode donnée
   double minAlpha;//starting value
   int train; //training layer operation num
   int ftrain; //first layer operation num
 }N_conf;

typedef struct neurone neurone;

 struct neurone
 {
    double*w;
    int etiquette;
    double* distance_eql;
 };
 
 struct reseau
 {
   int voisinage;  
  neurone **map;//??????
  double *vecteur_courant; 
  double alpha; 
  char *etiquette;   
 };
 
 struct vecteur
	{
        char *nom;
        double *argument;
        double norme;
	};

struct vecteur * vecteur_tab;