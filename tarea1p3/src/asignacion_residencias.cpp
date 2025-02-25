/* 5265175 */

/* 
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include <cstddef>
#include <cstdlib>
#include "../include/cola.h"
#include "../include/asignacion.h"

Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs){
	//inicializaciones 
	Asignacion emparejamiento = crear_asignacion();
	Cola h_libres = crear_cola();
	for(nat i = 0;i<m;i++)
		encolar(i,h_libres);
		
	nat *Siguiente = new nat[m];
	for(nat i = 0;i<m;i++)
		Siguiente[i]=0;
		
	int *Actual = new int[n];
	for(nat i = 0;i<n;i++)
		Actual[i]=-1;
    
    nat **Ranking = new nat*[n];
    for(nat i = 0;i<n;i++)
       Ranking[i] = new nat[m];
       
    for(nat i = 0;i<n;i++){
		for(nat j = 0;j<m;j++){
			Ranking[i][ePrefs[i][j]]=j;  
		}
	}
    
    while(!es_vacia_cola(h_libres)){
		nat h = frente(h_libres); 
		nat e = hPrefs[h][Siguiente[h]];
		par p = {e,h};
		
		if(Actual[e] == -1){ //e esta libre
		insertar_par(p,emparejamiento); //e acepta
		Actual[e] = h;
		C[h]--;
	     }
		else{ //e no esta libre
		  if(Ranking[e][h] < Ranking[e][Actual[e]]){//e prefiere a h antes que al actual
			 nat actual_e = abs(Actual[e]); 
			 par actual = {e,actual_e};
			 remover_par(actual,emparejamiento);
		     C[Actual[e]]++;
		     if(C[Actual[e]]==1)
		       encolar(Actual[e],h_libres);
		       
		     C[h]--;
		     insertar_par(p,emparejamiento);
		     Actual[e] = h;
		   }
		}
		
		Siguiente[h]++;
		
		if(C[h]==0)
		 desencolar(h_libres);
     }
     
    delete []Siguiente;
    delete []Actual;
    for(nat i = 0;i<n;i++)
       delete []Ranking[i];
       
    delete []Ranking;
    destruir_cola(h_libres);
    return emparejamiento;
}
