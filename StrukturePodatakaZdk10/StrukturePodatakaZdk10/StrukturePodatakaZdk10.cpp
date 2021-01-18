#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ZNAK (11)

struct _listaCvor;
struct _stabloCvor;
typedef struct _listaCvor* lPok;
typedef struct _stabloCvor* stPok;
typedef struct _stabloCvor {
	char znak[MAX_ZNAK];
	stPok livo;
	stPok desno;
}stCvor;
typedef struct _listaCvor {
	stPok stCvor;
	lPok next;
}lCvor;

stPok novi_stPok(char*);
void pushFront(lPok, stPok);
void pushBack(lPok, stPok);
stPok popFront(lPok);
stPok izDatoteke(char*);
int provjeraBroj(char*);
void infiksIspis(lPok, stPok);
//void infiksIspis(stPok);

int main() {
	stPok postfiks = NULL;
	lCvor head;
	head.next = NULL;
	lPok infiks = NULL;
	FILE *fp = NULL;
	char datoteka[50];
	printf("\nUnesi ime datoteke(.txt): ");
	scanf(" %s", datoteka);
	postfiks = izDatoteke(datoteka);
	//infiksIspis(postfiks);
														//ako zelimo ispis sa zagradama nije potreban ostatak "main funkcije" vec promjena "infiksIspis" funkcije
	infiksIspis(&head, postfiks);						//na dnu je dan primjer kao ce izgledati sa zagradama (potrebno je zamijeniti koju verziju "infiksIspis" koristimo)													
	fp = fopen("infiks.txt", "w");
	for (infiks = head.next; infiks != NULL; infiks = infiks->next) {
		fprintf(fp , "%s ", infiks->stCvor->znak);		//rjesenje je tocno ispisano (provjereno sa vise primjera), ali moze izgledati krivo zbog nedostatka zagrada
	}													
	fclose(fp);
	return 0;
}

stPok novi_stPok(char* znak) {
	stPok p = NULL;
	p = (stPok)malloc(sizeof(stCvor));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		free(p);
		return NULL;
	}
	strcpy(p->znak, znak);
	p->livo = NULL;
	p->desno = NULL;
	return p;
}
void pushFront(lPok head, stPok cvor) {
	lPok p = NULL;
	p = (lPok)malloc(sizeof(lCvor));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		free(p);
		return;
	}
	p->stCvor = cvor;
	p->next = head->next;
	head->next = p;
}
void pushBack(lPok head, stPok cvor) {
	lPok p = head;
	while (NULL != p->next)
		p = p->next;
	return pushFront(p, cvor);
}
stPok popFront(lPok head) {
	lPok p = head->next;
	stPok q = NULL;
	if (NULL == p)
		return NULL;
	head->next = p->next;
	q = p->stCvor;
	free(p);
	return q;
}
stPok izDatoteke(char* datoteka) {
	FILE *fp = NULL;
	lCvor head;
	head.next = NULL;
	fp = fopen(datoteka, "r");
	if (NULL == fp) {
		printf("\nGreska pri otvaranju datoteke\n");
		return NULL;
	}
	while (!feof(fp)) {
		stPok p = NULL;
		char data[MAX_ZNAK];
		fscanf(fp, " %s", data);
		p = novi_stPok(data);
		if (NULL == p) {
			fclose(fp);
			return NULL;
		}
		if (provjeraBroj(data)) {
			pushFront(&head, p);
		}
		else {
			p->desno = popFront(&head);
			p->livo = popFront(&head);
			pushFront(&head, p);
		}
	}
	fclose(fp);
	return popFront(&head);
}
int provjeraBroj(char* data) {
	int broj = 0;
	if (sscanf(data, " %d", &broj) == 1)return 1;
	return 0;
}
void infiksIspis(lPok head, stPok current) {
	if (NULL == current)
		return;
	infiksIspis(head, current->livo);
	pushBack(head, current);
	infiksIspis(head, current->desno);
}/*
void infiksIspis( stPok current) {	//ispis sa zagradama ako ne upisujemo u datoteku nego samo na terminal
	if (NULL == current)
		return;
	if (NULL != current->livo && strcmp(current->znak, "*") && strcmp(current->znak, "/"))
		printf("(");				//provjera za ispis zagrada, ako je broj nece ispisati jer ce zagrada biti redundantna, primjer -> ((4)+(3))
	infiksIspis(current->livo);		//takoder ako je mnozenje ili dijeljenje jer oni vec imaju prednost pri redoslijedu racunskih operacija
	printf("%s ", current->znak);	//brojevi nece imati djece tako da je dovoljna provjera samo jednog djeteta
	infiksIspis(current->desno);	//postoje jos neki slucajevi gdje se zagrade mogu izostaviti ali to su neki specificni slucajevi koji zahtijevaju drukciji pristup
	if (NULL != current->livo && strcmp(current->znak, "*") && strcmp(current->znak, "/"))
		printf(")");
}*/