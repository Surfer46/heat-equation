#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grRDF.h"

#define K 0.13
#define C 0.11
#define RHO 7.8

/*
 * Per compilar:
        gcc -o crancknic -g -Wall crancknic.c grRDF.c -lm
 */
        

/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double F (double t, double x, double y) {
    if(sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5))<0.2){
        return 100/K;
    }
    else return 0;
}

/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double G (double t, double x, double y) {
  return 0;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double H (double x, double y) {
  return 0;
}

/*!\brief Implementa l'algorisme 1.1 per al punt 2 del gui\'o. */
int main (int argc, char *argv[]) {
  //Declaracions
  int k,nx,ny,nt,maxit;
  double dx,dy,tol;
  grRDF gr;

  FILE *f=fopen("placacn.txt","w");
  if (f == NULL){
        printf("Error a l'obrir l'arxiu!\n");
        exit(1);
    }

  //Control parametres linia de comandes
  if (argc!=8
         || sscanf(argv[1],"%lf",&dx)!=1
         || sscanf(argv[2],"%lf",&dy)!=1
         || sscanf(argv[3],"%d",&nx)!=1
         || sscanf(argv[4],"%d",&ny)!=1
         || sscanf(argv[5],"%d",&nt)!=1
         || sscanf(argv[6],"%lf",&tol)!=1
         || sscanf(argv[7],"%d",&maxit)!=1
      ) {
      fprintf(stderr, "./crancknic dx dy nx ny nt tol maxit\n");
      return -1;
   }

   //Configuracio parametres
   double dt=K/(C*RHO*nt);
   //double mux=dt/(dx*dx);
   //double muy=dt/(dy*dy);  

   //Ara no cal comprovar la condició:
   //if(1-2*mux-2*muy<0) printf("No es compleix la condició de convergència\n");
   if(dx>=1 || dy>=1) printf("Els passos en espai són més grans que 1\n");
   
   //Inicialitzem graella (parametres i llesca t=0)
   grRDF_init(&gr,dx,dy,dt,nx,ny,H);

   //Escrivim graella inicial 
   grRDF_escriure(&gr,f);

   //Fem passos d'integracio. Bucle en el temps
   for(k=0;k<=nt;k++){
     grRDF_pasCalCN(&gr,1.7,tol,maxit,F,G);
     grRDF_escriure(&gr,f);
   }
   fclose(f);
   return 0;
}
#undef K
#undef RHO
#undef C
