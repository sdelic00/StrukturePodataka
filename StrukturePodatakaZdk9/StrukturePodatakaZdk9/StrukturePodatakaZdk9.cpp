#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>

struct _cvor;
typedef struct _cvor* Pok;
typedef struct _cvor {
	int broj;
	Pok livo;
	Pok desno;
}Cvor;

Pok noviPok(int);
Pok noviCvor(Pok, Pok);
int trazi(Pok, int);
void printRed(Pok);
Pok delCvor(Pok, int);
Pok findMax(Pok);
Pok findMin(Pok);

int main() {
	Pok root = NULL;
	Pok p = NULL;
	int x = 0, izbor = 0, broj, rez=0 ,izbTrazi=0;
	while (0 == x) {
		printf("\nMenu:\n1 - Dodaj broj\n2 - Izbrisi broj\n3 - Pronadi broj\n4 - Ispisi elemente stabla\n5 - Izlaz\n\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("\nKoji broj zelite dodati: ");
			scanf("%d", &broj);
			p = noviPok(broj);
			root = noviCvor(root, p);
			break;
		case 2:
			printf("\nKoji broj zelite izbrisati: ");
			scanf("%d", &broj);
			root = delCvor(root, broj);
			break;
		case 3:
			printf("\nKoji broj zelite pronaci: ");
			scanf("%d", &broj);
			rez = trazi(root, broj);
			switch (rez) {
			case 0:
				printf("\nDodati broj? 1- Da / 2- Ne\n");
				scanf("%d", &izbTrazi);
				switch (izbTrazi) {
				case 1:
					p = noviPok(broj);
					root = noviCvor(root, p);
					break;
				case 2:
					break;
				default:
					printf("\nGreska pri odabiru - broj nije dodan\n");
					break;
				}
				break;
			case 1:
				printf("\nIzbrisati broj? 1 - Da / 2 - Ne\n");
				scanf("%d", &izbTrazi);
				switch (izbTrazi) {
				case 1:
					root = delCvor(root, broj);
					break;
				case 2:
					break;
				default:
					printf("\nGreska pri odabiru - broj nije izbrisan\n");
					break;
				}
				break;
			default:
				printf("\nGreska pri trazenju\n");
				break;
			}
			break;
		case 4:
			printf("\nElementi stabla: ");
			printRed(root);
			printf("\n");
			break;
		case 5:
			printf("\nDovidenja\n");
			x = 1;
			break;
		default:
			printf("\nGreska pri odabiru\n");
			break;
		}
	}
}
Pok noviPok(int broj) {
	Pok p = NULL;
	p = (Pok)malloc(sizeof(_cvor));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->broj = broj;
	p->livo = NULL;
	p->desno = NULL;
	return p;
}
Pok noviCvor(Pok current, Pok novi) {
	if (NULL == current) {
		printf("\nBroj uspjesno dodan\n");
		return novi;
	}
	if (current->broj > novi->broj) {
		current->livo = noviCvor(current->livo, novi);
	}
	else if (current->broj < novi->broj) {
		current->desno = noviCvor(current->desno, novi);
	}
	else {
		printf("\nBroj vec ostoji\n");
		free(novi);
	}
	return current;
}
int trazi(Pok current, int broj) {
	int x = 0;
	if (NULL == current) {
		printf("\nBroj nije pronaden\n");
		return x;
	}
	if (current->broj > broj) {
		x = trazi(current->livo, broj);
	}
	else if (current->broj < broj) {
		x = trazi(current->desno, broj);
	}
	else {
		printf("\nBroj pronaden\n");
		x = 1;
	}
	return x;
}
void printRed(Pok current) {
	if (NULL == current)
		return;
	printRed(current->livo);
	printf("%d ", current->broj);
	printRed(current->desno);
}
Pok delCvor(Pok current, int broj) {
	if (NULL == current) {
		printf("\nBroj nije pronaden\n");
		return NULL;
	}
	if (current->broj == broj) {
		if (NULL == current->livo && NULL == current->desno) {
			free(current);
			return NULL;
		}
		if (NULL == current->desno) {
			Pok temp = findMax(current->livo);
			current->broj = temp->broj;
			current->livo = delCvor(current->livo, temp->broj);
		}
		else if (NULL == current->livo) {
			Pok temp = findMin(current->desno);
			current->broj = temp->broj;
			current->desno = delCvor(current->desno, temp->broj);
		}
		else {
			Pok temp = findMax(current->livo);
			current->broj = temp->broj;
			current->livo = delCvor(current->livo, temp->broj);
		}
	}
	else if (current->broj > broj) {
		current->livo = delCvor(current->livo, broj);
	}
	else {
		current->desno = delCvor(current->desno, broj);
	}
	return current;
}
Pok findMax(Pok current) {
	if (NULL == current)
		return NULL;
	while (NULL != current->desno)
		current = current->desno;
	return current;
}
Pok findMin(Pok current) {
	if (NULL == current)
		return NULL;
	while (NULL != current->livo)
		current = current->livo;
	return current;
}