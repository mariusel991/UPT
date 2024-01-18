#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct palet{

	unsigned int cod;
	struct palet* urm;

}palet;

typedef struct depozit {

	char nume[16];
	palet* prim;
	struct depozit* urm;

}depozit;

depozit* add_depozit(depozit *prim, char* nume) {

	depozit* elem = malloc(sizeof(depozit));
	if (!elem) {
		fprintf(stderr, "Aloc err\n");
		return prim;
	}

	strcpy(elem->nume, nume);
	elem->urm = NULL;
	elem->prim = NULL;

	if (prim == NULL) {
		prim = elem;
		return prim;
	}

	depozit* it = prim;
	while (it->urm != NULL) {
		it = it->urm;
	}
	
	it->urm = elem;
	return prim;

}

palet* insert_palet(palet* prim, unsigned int cod) {
	
	palet* elem = malloc(sizeof(palet));
	if (!elem) {
		return prim;
	}

	elem->cod = cod;
	elem->urm = NULL;

	if (prim == NULL) {
		prim = elem;
		return prim;
	}

	if (elem->cod < prim->cod) {
		elem->urm = prim;
		prim = elem;
		return prim;
	}

	palet* curr = prim->urm;
	palet* ant = prim;

	while (curr != NULL) {
		
		if (elem->cod < curr->cod) {
			ant->urm = elem;
			elem->urm = curr;
			return prim;
		}

		ant = curr;
		curr = curr->urm;
	}

	ant->urm = elem;
	return prim;
}

depozit* add_palet(depozit *ld, char* nume_depozit, unsigned int cod_palet) {
	
	depozit* it_ld = ld;

	while (it_ld != NULL) {
		if (strcmp(it_ld->nume, nume_depozit) == 0) {
			break;
		}
		it_ld = it_ld->urm;
	}

	if (it_ld == NULL) {
		fprintf(stderr, "Depozitul nu exista\n");
		return ld;
	}

	it_ld->prim = insert_palet(it_ld->prim,cod_palet);
	return ld;

}

depozit* sterge_palet(depozit* d, unsigned int cod) {
	
	depozit* itd = d;

	while (itd != NULL) {
		palet* curr = NULL;
		palet* ant = NULL;

		curr = itd->prim;
		ant = NULL;

		while (curr != NULL) {

			if (curr->cod == cod) {
				if (ant == NULL) {
					ant = curr;
					itd->prim = itd->prim->urm;
					free(ant);
					break;
				}
				else {
					ant->urm = curr->urm;
					free(curr);
					break;
				}
			}
			ant = curr;
			curr = curr->urm;
		}

		itd = itd->urm;
	}

	return d;
}

void afisare_depozite(depozit* d) {
	depozit* it1 = d;

	while (it1 != NULL) {
		printf("%s\n", it1->nume);
		palet* it2 = it1->prim;
		while (it2 != NULL) {
			printf("%d ", it2->cod);
			it2 = it2->urm;
		}
		printf("\n");
		it1 = it1->urm;
	}
	printf("\n");
}

void nume_deps(depozit* d) {
	depozit* it = d;

	while (it != NULL) {
		printf("%s\n", it->nume);
		it = it->urm;
	}
}

depozit* delete_all(depozit* d) {
		
	depozit* curr = d;
	depozit* ant = NULL;

	while (curr != NULL) {

		palet* curr1 = curr->prim;
		palet* ant1 = NULL;

		while (curr1 != NULL) {
			ant1 = curr1;
			curr1 = curr1->urm;
			free(ant1);
		}

		ant = curr;
		curr = curr->urm;
		free(ant);
	}

	return NULL;
}


int main() {
	
	depozit* d = NULL;

	d = add_depozit(d, "Timisoara");
	d = add_depozit(d, "Alba");

	d = add_palet(d, "Alba", 32);

	d = add_palet(d, "Timisoara", 45);
	d = add_palet(d, "Timisoara", 32);
	d = add_palet(d, "Timisoara", 37);

	d = sterge_palet(d,32);

	afisare_depozite(d);
	d = delete_all(d);
	//nume_deps(d);

	return 0;
}
