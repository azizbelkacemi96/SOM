#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>



struct Data
{
    double* vecteur;
    char* etiquette;
    double* norme;
};
typedef struct Data Data;

 struct neurone
 {
    double *w;
    char *etiquette;
    double distance_eql;
 };
typedef struct neurone Neurone;

 struct reseau
 {
   int voisinage;  
  Neurone **map;
  double *vecteur_courant; 
  double alpha; 
  char *etiquette;   
 }reseau;

 struct vecteur
	{
        char *nom;
        double *argument;
        double norme;
	};

struct vecteur * vecteur_tab;
