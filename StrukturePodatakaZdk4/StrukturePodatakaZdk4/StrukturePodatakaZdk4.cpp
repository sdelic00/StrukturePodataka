#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>

struct _polinom;
typedef struct _polinom *Clan;
typedef struct _polinom {
	int koef;
	int exp;
	Clan next;
}Polinom;

Clan noviClan(int koef, int exp);
void unosPol(Clan head, const char *fileName);
void dodajClan(Clan head, Clan novi);
void zbrojiPol(Clan head1, Clan head2, Clan head3);
void pomnoziPol(Clan head1, Clan head2, Clan head4);
void ispisPol(Clan head);

int main() {
	Polinom head1, head2, head3, head4;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;
	unosPol(&head1, "polinom1.txt");
	ispisPol(&head1);
	unosPol(&head2, "polinom2.txt");
	ispisPol(&head2);
	zbrojiPol(&head1, &head2, &head3);
	printf("\nZbroj polinoma\n");
	ispisPol(&head3);
	pomnoziPol(&head1, &head2, &head4);
	printf("\nUmnozak polinoma\n");
	ispisPol(&head4);
	return 0;
}
Clan noviClan(int koef, int exp) {
	Clan p = NULL;
	p = (Clan)malloc(sizeof(Polinom));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->koef = koef;
	p->exp = exp;
	p->next = NULL;
	return p;
}
void unosPol(Clan head, const char *fileName) {
	Clan p = NULL;
	Clan q = NULL;
	FILE *fp;
	int koef, exp;
	fp = fopen(fileName, "r");
	while (fscanf(fp, "%d %d", &koef, &exp) != EOF) {
		p = noviClan(koef, exp);
		for (q = head; q != NULL; q = q->next) {
			if (koef == 0) {
				free(p);
				break;
			}
			else if (q->exp == exp) {
				q->koef = q->koef + p->koef;
				free(p);
				break;
			}
			else if (q->exp > p->exp) {
				p->koef = q->koef;
				p->exp = q->exp;
				q->koef = koef;
				q->exp = exp;
				dodajClan(q, p);
				break;
			}
			else if(q->next==NULL){
				dodajClan(q, p);
				break;
			}
		}
	}
	fclose(fp);
}
void dodajClan(Clan gdje, Clan novi) {
	novi->next = gdje->next;
	gdje->next = novi;
}
void zbrojiPol(Clan head1, Clan head2, Clan head3) {
	Clan p = NULL;
	Clan q = NULL;
	Clan k = NULL;
	int tempKoef = 0;
	p = head1->next;
	q = head2->next;
	k = head3;
	while (p != NULL || q != NULL) {
		if (p == NULL) {
			for (q; q != NULL; q = q->next) {
				k->next = noviClan(q->koef, q->exp);
				k = k->next;
			}
		}
		else if (q == NULL) {
			for (p; p != NULL; p = p->next) {
				k->next = noviClan(p->koef, p->exp);
				k = k->next;
			}
		}
		else if (p->exp == q->exp) {
			tempKoef = p->koef + q->koef;
			if (tempKoef != 0) {
				k->next = noviClan(tempKoef, p->exp);
				k = k->next;
				p = p->next;
				q = q->next;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
		else if (p->exp < q->exp) {
			k->next = noviClan(p->koef, p->exp);
			k = k->next;
			p = p->next;
		}
		else if (p->exp > q->exp) {
			k->next = noviClan(q->koef, q->exp);
			k = k->next;
			q = q->next;
		}
	}
	k->next = NULL;
}
void ispisPol(Clan head) {
	Clan p = head->next;
	printf("\nKoef\tExp\n");
	for (p; p != NULL; p = p->next) {
		printf("%d\t%d\n", p->koef, p->exp);
	}
}
void pomnoziPol(Clan head1, Clan head2, Clan head4) {
	Clan p = NULL;
	Clan q = NULL;
	Clan k = NULL;
	Clan z = NULL;
	int koef, exp;
	for (p = head1->next; p != NULL; p = p->next) {
		for (q = head2->next; q != NULL; q = q->next) {
			koef = q->koef*p->koef;
			exp = q->exp + p->exp;
			z = noviClan(koef, exp);
			for (k=head4; k != NULL; k = k->next) {
				if (k->exp == z->exp) {
					k->koef = k->koef + z->koef;
					free(z);
					break;
				}
				else if (k->exp > z->exp) {
					z->koef = k->koef;
					z->exp = k->exp;
					k->koef = koef;
					k->exp = exp;
					dodajClan(k, z);
					break;
				}
				else if (k->next == NULL) {
					dodajClan(k, z);
					break;
				}
			}
		}
	}
}