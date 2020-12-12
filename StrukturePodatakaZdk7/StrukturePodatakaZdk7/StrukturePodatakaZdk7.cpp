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
void unosDat(char*);
void push(Pok, int);
int pop(Pok);
void racun(Pok, char);

int main() {
	Lista head;
	head.next = NULL;
	Pok p = NULL;
	char *postfiks=(char*)malloc(50*sizeof(char));
	char oper = 'a';
	int broj, n = 0, x = 0;
	unosDat(postfiks);
	printf("\nPostfiks izraz: ");
	puts(postfiks);
	while ('\0' != oper) {
		x = sscanf(postfiks, "%d %n", &broj, &n);
		if (1 == x) {
			push(&head, broj);
			postfiks += n;
		}
		else if(0 == x){
			sscanf(postfiks, "%c %n", &oper, &n);
			if ('\0' == oper) {
				break;
			}
			racun(&head, oper);
			postfiks += n;
		}
		else if (-1 == x) {
			break;
		}
	}
	p = head.next;
	printf("\nRjesenje izraza je: %d\n", p->broj);
	return 0;
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
void unosDat(char *postfiks) {
	FILE *fp;
	fp = fopen("postfiks.txt", "r");
	if (NULL == fp) {
		printf("\nGreska pri otvaranju datoteke\n");
	}
	fgets(postfiks, 50, fp);
	fclose(fp);
}
void push(Pok head, int broj) {
	Pok p = NULL;
	p = noviPok(broj);
	p->next = head->next;
	head->next = p;
}
int pop(Pok head) {
	Pok p = NULL;
	int broj;
	p = head->next;
	head->next = p->next;
	broj = p->broj;
	free(p);
	return broj;
}
void racun(Pok head, char oper) {
	int br1, br2, rez=0, y=0;
	br2 = pop(head);
	br1 = pop(head);
	switch (oper) {
	case'+':
		rez = br1 + br2;
		break;
	case'-':
		rez = br1 - br2;
		break;
	case'*':
		rez = br1 * br2;
		break;
	case'/':
		rez = br1 / br2;
		break;
	default:
		printf("\nGreska\n");
		push(head, br1);
		push(head, br2);
		y++;
		break;
	}
	if (0 == y) {
		push(head, rez);
	}
}