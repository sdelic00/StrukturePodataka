#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>

struct _lista;
typedef struct _lista* Pok;
typedef struct _lista {
	int broj;
	Pok next;
}Lista;

Pok noviPok(int);
void pushStog(Pok);
void pushRed(Pok);
void pop(Pok);
void ispis(Pok);

int main() {
	Lista head;
	head.next = NULL;
	Pok last = &head;
	int izbor = 0, x = 0, izbStog = 0, izbRed = 0;
	while (0 == x) {
		printf("\nZelite li raditi:\n1 - Sa stogom\n2 - S redom\n");
		scanf("%d", &izbor);
		if (1 == izbor) {
			while (0 == x) {
				printf("\n1 - Dodaj broj na stog\n2 - Skini broj sa stoga\n3 - Zavrsi sa radom i ispisi stog\n");
				scanf("%d", &izbStog);
				if (1 == izbStog) {
					pushStog(&head);
					printf("\nStog: ");
					ispis(&head);
				}
				else if (2 == izbStog) {
					if (NULL == head.next) {
						printf("\nPrazon stog\n");
					}
					else {
						pop(&head);
						printf("\nStog: ");
						ispis(&head);
					}
				}
				else if (3 == izbStog) {
					printf("\nStog: ");
					ispis(&head);
					x = 1;
				}
				else {
					printf("\nGreska pri odabiru\n");
				}
			}
		}
		else if (2 == izbor) {
			while (0 == x) {
				printf("\n1 - Dodaj broj u red\n2 - Skini broj iz reda\n3 - Zavrsi s radom i ispisi red\n");
				scanf("%d", &izbRed);
				if (1 == izbRed) {
					pushRed(last);
					last = last->next;
					printf("\nRed: ");
					ispis(&head);
				}
				else if (2 == izbRed) {
					if (NULL == head.next) {
						printf("\nPrazan red\n");
					}
					else {
						if (head.next == last) {
							last = &head;
						}
						pop(&head);
						printf("\nRed: ");
						ispis(&head);
					}
				}
				else if (3 == izbRed) {
					printf("\nRed: ");
					ispis(&head);
					x = 1;
				}
				else {
					printf("\nGreska pri odabiru\n");
				}
			}
		}
		else {
			printf("\nGreska pri odabiru\n");
		}
	}
}
Pok noviPok(int broj) {
	Pok p = NULL;
	p = (Pok)malloc(sizeof(Lista));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->broj = broj;
	p->next = NULL;
	return p;
}
void pushStog(Pok head){
	Pok p = NULL;
	int broj;
	broj = ((double)rand() / RAND_MAX)*(100 - 10 + 1) + 10;
	p = noviPok(broj);
	p->next = head->next;
	head->next = p;
}
void pushRed(Pok last) {
	Pok p = NULL;
	int broj;
	broj = ((double)rand() / RAND_MAX)*(100 - 10 + 1) + 10;
	p = noviPok(broj);
	last->next = p;
	last = last->next;
}
void pop(Pok head) {
	Pok p = NULL;
	p = head->next;
	head->next = p->next;
	printf("\nIzbacen je broj: %d\n", p->broj);
	free(p);
}
void ispis(Pok head) {
	Pok p = NULL;
	for (p = head->next; NULL != p; p = p->next) {
		printf("%d ", p->broj);
	}
	printf("\n");
}