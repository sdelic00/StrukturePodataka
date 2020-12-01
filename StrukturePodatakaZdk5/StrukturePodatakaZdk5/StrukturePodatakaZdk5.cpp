#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>

struct _skup;
typedef struct _skup* Pok;
typedef struct _skup {
	int broj;
	Pok next;
}Skup;

Pok noviPok(int);
void unosRucni(Pok);
void unosDatoteka(Pok, const char*);
void ispisSkupa(Pok);
void dodajPok(Pok, Pok);
void unija(Pok, Pok, Pok);
void presjek(Pok, Pok, Pok);

int main() {
	Skup head1, head2, head3, head4;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;
	int izbor = 0, x = 0;
	while (0 == x) {
		printf("\nOdaberite nacin unosa skupova:\n1 - Rucni unos\n2 - Iz datoteke\n");
		scanf("%d", &izbor);
		if (1 == izbor) {
			printf("\nPrvi skup:\n");
			unosRucni(&head1);
			printf("\nPrvi skup:\n");
			ispisSkupa(&head1);
			printf("\nDrugi skup:\n");
			unosRucni(&head2);
			printf("\nDrugi skup:\n");
			ispisSkupa(&head2);
			x = 1;
		}
		else if(2 == izbor) {
			printf("\nPrvi skup:\n");
			unosDatoteka(&head1,"skup1.txt");
			ispisSkupa(&head1);
			printf("\nDrugi skup:\n");
			unosDatoteka(&head2,"skup2.txt");
			ispisSkupa(&head2);
			x = 1;
		}
		else {
			printf("\nGreska pri odabiru. Ponovite odabir\n");
		}
	}
	unija(&head1, &head2, &head3);
	printf("\nUnija skupova:\n");
	ispisSkupa(&head3);
	presjek(&head1, &head2, &head4);
	printf("\nPresjek skupova:\n");
	ispisSkupa(&head4);
}
Pok noviPok(int broj) {
	Pok p = NULL;
	p = (Pok)malloc(sizeof(Skup));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->broj = broj;
	p->next = NULL;
	return p;
}
void dodajPok(Pok gdje, Pok novi) {
	novi->next = gdje->next;
	gdje->next = novi;
}
void unosRucni(Pok head) {
	Pok p = NULL;
	Pok q = NULL;
	int broj, izbor = 0, x = 0;
	printf("\nUnesite broj: ");
	scanf("%d", &broj);
	p = noviPok(broj);
	dodajPok(head, p);
	while (0 == x) {
		printf("\nZelite li dodati jos jedan clan?\n1 - Da\n2 - Ne\n");
		scanf("%d", &izbor);
		if (1 == izbor) {
			printf("\nUnesite broj: ");
			scanf("%d", &broj);
			p = noviPok(broj);
			for (q = head; q != NULL; q = q->next) {
				if (broj == q->broj) {
					printf("\nBroj vec postoji u skupu\n");
					free(p);
					break;
				}
				else if (q->broj > p->broj) {
					p->broj = q->broj;
					q->broj = broj;
					dodajPok(q, p);
					break;
				}
				else if (NULL == q->next) {
					dodajPok(q, p);
					break;
				}
			}
		}
		else if (2 == izbor) {
			printf("\nGotov unos\n");
			x = 1;
		}
		else {
			printf("\nGreska pri odabiru. Ponovite odabir\n");
		}
	}
}
void ispisSkupa(Pok head) {
	Pok p = NULL;
	printf("\nSkup: ");
	for (p = head->next; p != NULL; p = p->next) {
		printf("%d ", p->broj);
	}
	printf("\n");
}
void unija(Pok head1, Pok head2, Pok head3) {
	Pok p = head1->next;
	Pok q = head2->next;
	Pok k = head3;
	while (NULL != p || NULL != q) {
		if (NULL == p) {
			k->next = noviPok(q->broj);
			q = q->next;
			k = k->next;
		}
		else if (NULL == q) {
			k->next = noviPok(p->broj);
			p = p->next;
			k = k->next;
		}
		else if (p->broj > q->broj) {
			k->next = noviPok(q->broj);
			q = q->next;
			k = k->next;
		}
		else if (p->broj < q->broj) {
			k->next = noviPok(p->broj);
			p = p->next;
			k = k->next;
		}
		else if (p->broj == q->broj) {
			k->next = noviPok(p->broj);
			p = p->next;
			q = q->next;
			k = k->next;
		}
	}
	k->next = NULL;
}
void presjek(Pok head1, Pok head2, Pok head4) {
	Pok p = head1->next;
	Pok q = head2->next;
	Pok k = head4;
	while (NULL != p && NULL != q) {
		if (p->broj > q->broj) {
			q = q->next;
		}
		else if (p->broj < q->broj) {
			p = p->next;
		}
		else if (p->broj == q->broj) {
			k->next = noviPok(p->broj);
			p = p->next;
			q = q->next;
			k = k->next;
		}
	}
	k->next = NULL;
}
void unosDatoteka(Pok head, const char *fileName) {
	Pok p = NULL;
	Pok q = NULL;
	FILE *fp;
	int broj;
	fp = fopen(fileName, "r");
	while (fscanf(fp, "%d", &broj) != EOF) {
		p = noviPok(broj);
		for (q = head; q != NULL; q = q->next) {
			if (broj == q->broj) {
				printf("\nBroj vec postoji u skupu\n");
				free(p);
				break;
			}
			else if (q->broj > p->broj) {
				p->broj = q->broj;
				q->broj = broj;
				dodajPok(q, p);
				break;
			}
			else if (NULL == q->next) {
				dodajPok(q, p);
				break;
			}
		}
	}
	fclose(fp);
}