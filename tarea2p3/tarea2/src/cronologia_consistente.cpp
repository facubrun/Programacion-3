/* 52651752
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>
#include "../include/grafo.h"
#include "../include/cronologia_consistente.h"
#include "../include/lista.h"
#include "../include/lista_datos.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  bool existe_cr_consistente = false; 

  Cronologia cr = new evento[2*n]; 
  Grafo grafo = crear_grafo(2*n,true);
  for(nat i=1;i<=2*n;i++){
	  agregar_vertice(i,grafo);
   }
  while(!es_vacia_lista_datos(tipo1)){
	  agregar_arista(n+id1(primer_dato(tipo1)),id2(primer_dato(tipo1)),grafo);
	  
	  tipo1 = resto_datos(tipo1);
   }
   
   
   while(!es_vacia_lista_datos(tipo2)){
	  agregar_arista(id1(primer_dato(tipo2)),n+id2(primer_dato(tipo2)),grafo);
	  agregar_arista(id2(primer_dato(tipo2)),n+id1(primer_dato(tipo2)),grafo);
	  
	  tipo2 = resto_datos(tipo2);
	}  
  
  Lista V1 = vertices(grafo);
  Lista S=crear_lista();
  while(existe_actual(V1)){
	  if(in_grado(actual(V1),grafo)==0){
	    insertar_al_inicio(actual(V1),S);
	   } 
      siguiente(V1); 
   }
   
   nat *incid = new nat[2*n+1];
   for(nat j = 1;j<=2*n;j++){
	   incid[j]=in_grado(j,grafo);
	}     
	
   nat i=0;
   while(existe_actual(S)){
	  if(actual(S) <= n){//nacimiento
		  evento ev = {actual(S),nace};
	      cr[i]=ev;
	      i++;
	   }
	   else if(actual(S)>n){//muerte
		   evento ev2 = {actual(S)-n,muere};
		   cr[i]=ev2;
		   i++;
	   }
	  
	  Lista adyac = adyacentes(actual(S),grafo);
	  while(existe_actual(adyac)){
		  incid[actual(adyac)]--;
		  if(incid[actual(adyac)]==0)
		    insertar_al_inicio(actual(adyac),S);
		  siguiente(adyac);
       }
       siguiente(S);
    }
    destruir_grafo(grafo);
    destruir_lista(V1);
    destruir_lista(S);
    
    
  nat k=1;
  bool incid_0 = true;  
  while(incid_0 && k<=2*n){
	  if(incid[k]==0){
	     incid_0 = true;
	   }
	   else {incid_0 = false;}
	   k++;
	}
  delete []incid;
  if(incid_0) existe_cr_consistente = false;
  else { existe_cr_consistente = true;} 
  // Determinar si existe o no una cronología consistente con los datos, 
  // en caso de existir, construirla en cr 

  if(existe_cr_consistente) { // si existe, retornarla en cr
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
    delete[] cr;
    return NULL;
  }
} 
