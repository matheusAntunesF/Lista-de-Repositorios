#include <stdio.h>
#include <stdlib.h>
#include "polinomio.h"

void inicializa_polinomio(Polinomio * ap_pol){
	No * no_cab = (No *) malloc(sizeof(No));
	no_cab -> valor.grau = no_cab -> valor.coef = -1;
	no_cab -> prox = no_cab -> antec = no_cab;
	(*ap_pol) = no_cab;
}

void define_coeficiente(Polinomio pol, int grau, int coef){
	if(coef == 0)
		return;

	No * no_atual = pol -> prox;
	while(no_atual -> valor.grau < grau && no_atual != pol){
		no_atual = no_atual -> prox;
	}
	
	if(no_atual -> valor.grau == grau){
		no_atual -> valor.coef = coef;
	} else {
		No * no_ant = no_atual -> antec;
		No * novo_no = (No *) malloc(sizeof(No));
		novo_no -> valor.grau = grau;
		novo_no -> valor.coef = coef;
		no_ant -> prox = novo_no;
		novo_no -> antec = no_ant;
		novo_no -> prox = no_atual;
		no_atual -> antec = novo_no;
	}
}

void zera(Polinomio pol){
	No * no_atual = pol -> prox;
	while(no_atual != pol){
		no_atual = no_atual -> prox;
		free(no_atual -> antec);
	}
	pol -> prox = pol -> antec = pol;
}

void insere_novo_res(Polinomio * ap_atual_res, int grau, int coef){
	No * novo_no = (No *) malloc(sizeof(No));
	novo_no -> valor.grau = grau;
	novo_no -> valor.coef = coef;
	(*ap_atual_res) -> prox = novo_no;
	novo_no -> antec = (*ap_atual_res);
	(*ap_atual_res) = (*ap_atual_res) -> prox;
}

void soma(Polinomio res, Polinomio a, Polinomio b){
	zera(res);
	
	No * no_atual_a = a -> prox;
	No * no_atual_b = b -> prox;
	No * no_atual_res = res;	
	int coef, grau;
	while(no_atual_a != a || no_atual_b != b){
		if(no_atual_a == a){
			grau = no_atual_b -> valor.grau;
			coef = no_atual_b -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_b = no_atual_b -> prox;
		} else if(no_atual_b == b){
			grau = no_atual_a -> valor.grau;
			coef = no_atual_a -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_a = no_atual_a -> prox;
		} else if(no_atual_a -> valor.grau == no_atual_b -> valor.grau){
			coef = (no_atual_a -> valor.coef) + (no_atual_b -> valor.coef);
			if(coef == 0){
				no_atual_a = no_atual_a -> prox;
				no_atual_b = no_atual_b -> prox;
			}else {
				grau = no_atual_a -> valor.grau;
				insere_novo_res(&no_atual_res, grau, coef);
				no_atual_a = no_atual_a -> prox;
				no_atual_b = no_atual_b -> prox;
			}
		} else if(no_atual_a -> valor.grau > no_atual_b -> valor.grau){
			grau = no_atual_b -> valor.grau;
			coef = no_atual_b -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_b = no_atual_b -> prox;
		} else{ 
			grau = no_atual_a -> valor.grau;
			coef = no_atual_a -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_a = no_atual_a -> prox;
		}
	}
	no_atual_res -> prox = res;
	res -> antec = no_atual_res;
}

void subtrai(Polinomio res, Polinomio a, Polinomio b){
	zera(res);
	
	No * no_atual_a = a -> prox;
	No * no_atual_b = b -> prox;
	No * no_atual_res = res;	
	int coef, grau;
	while(no_atual_a != a || no_atual_b != b){
		if(no_atual_a == a){
			grau = no_atual_b -> valor.grau;
			coef = -(no_atual_b -> valor.coef);
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_b = no_atual_b -> prox;
		} else if(no_atual_b == b){
			grau = no_atual_a -> valor.grau;
			coef = no_atual_a -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_a = no_atual_a -> prox;
		} else if(no_atual_a -> valor.grau == no_atual_b -> valor.grau){
			coef = (no_atual_a -> valor.coef) - (no_atual_b -> valor.coef);
			if(coef == 0){
				no_atual_a = no_atual_a -> prox;
				no_atual_b = no_atual_b -> prox;
			} else {
				grau = no_atual_a -> valor.grau;
				insere_novo_res(&no_atual_res, grau, coef);
				no_atual_a = no_atual_a -> prox;
				no_atual_b = no_atual_b -> prox;
			}
		} else if(no_atual_a -> valor.grau > no_atual_b -> valor.grau){
			grau = no_atual_b -> valor.grau;
			coef = -(no_atual_b -> valor.coef);
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_b = no_atual_b -> prox;
		} else{ 
			grau = no_atual_a -> valor.grau;
			coef = no_atual_a -> valor.coef;
			insere_novo_res(&no_atual_res, grau, coef);
			no_atual_a = no_atual_a -> prox;
		}
	}
	no_atual_res -> prox = res;
	res -> antec = no_atual_res;
}

void imprime(Polinomio pol){
	No * no_atual = pol -> prox;
	printf("[");
	while(no_atual -> prox != pol){
		printf("(%d,%d),", no_atual -> valor.grau, no_atual -> valor.coef);
		no_atual = no_atual -> prox;
	}
	printf("(%d,%d)]\n", no_atual -> valor.grau, no_atual -> valor.coef);
}

void desaloca_polinomio(Polinomio *ap_pol){
	No * no_atual = (*ap_pol);
	no_atual = no_atual -> prox;
	while(no_atual != (*ap_pol)){
		no_atual = no_atual -> prox;
		free(no_atual -> antec);
	}
	free(no_atual);
	(*ap_pol)=NULL;
}
