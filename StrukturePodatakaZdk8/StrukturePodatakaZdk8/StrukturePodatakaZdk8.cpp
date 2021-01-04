#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NAME_LENGHT (256)

struct _dir;
struct _stog;
typedef struct _dir* Pok;
typedef struct _stog* stPok;
typedef struct _dir {
	char name[MAX_NAME_LENGHT];
	Pok sibling;
	Pok child;
}Dir;
typedef struct _stog {
	Pok current;
	stPok next;
}Stog;

Pok noviPok(char*);
stPok noviStog(Pok);
void noviDirektorij(Pok, char*);
void printDir(Pok);
Pok ulazDir(Pok, stPok, char*);
Pok izlazDir(stPok);
void currentDir(stPok, Pok);
void delDir(Pok);

int main() {
	Dir c;
	strcpy(c.name, "C:");
	c.sibling = NULL;
	c.child = NULL;
	Stog head;
	head.next = NULL;
	Pok current = &c;
	int x = 0;
	char oper[16], name[MAX_NAME_LENGHT];
	while (0 == x) {
		currentDir(&head, current);
		printf("\nMenu:\nmd - novi direktorij\ncd - udi u direktorij\ncd.. - napusti direktorij\ndir - ispisi sadrzaj direktorija\nizlaz - Ugasi program\n\n");
		scanf(" %s", oper);
		if (0 == strcmp("md", oper)) {
			printf("\nIzaberite ime direktorija: ");
			scanf(" %s", name);
			noviDirektorij(current, name);
		}
		else if (0 == strcmp("cd", oper)) {
			printf("\nIzaberite direktorij: ");
			scanf(" %s", name);
			current = ulazDir(current, &head, name);
		}
		else if (0 == strcmp("cd..", oper)) {
			current = izlazDir(&head);
		}
		else if (0 == strcmp("dir", oper)) {
			printDir(current);
		}
		else if (0 == strcmp("izlaz", oper)) {
			printf("\nDovidenja\n");
			delDir(c.child);
			x = 1;
		}
		else {
			printf("\nGreska pri odabiru\n");
		}
	}
}
Pok noviPok(char *name) {
	Pok p = NULL;
	p = (Pok)malloc(sizeof(_dir));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	strcpy(p->name, name);
	p->sibling = NULL;
	p->child = NULL;
	return p;
}
stPok noviStog(Pok current) {
	stPok p = NULL;
	p = (stPok)malloc(sizeof(_stog));
	if (NULL == p) {
		printf("\nGreska pri alokaciji memorije\n");
		return NULL;
	}
	p->current = current;
	p->next = NULL;
	return p;
}
void noviDirektorij(Pok current, char *name) {
	Pok p = NULL;
	Pok q = NULL;
	p = noviPok(name);
	if (NULL == current->child) {
		current->child = p;
	}
	else if (NULL != current->child) {
		q = current->child;
		while (q->sibling != NULL) {
			q = q->sibling;
		}
		q->sibling = p;
	}
}
void printDir(Pok current) {
	Pok p = NULL;
	p = current->child;
	while (NULL != p) {
		printf("\n%s", p->name);
		p = p->sibling;
	}
	printf("\n");
}
Pok ulazDir(Pok current, stPok head, char *name) {
	Pok p = current->child;
	stPok stp = NULL;
	if (NULL == p) {
		return current;
	}
	while (NULL != p) {
		if (0 == strcmp(p->name, name)) {
			break;
		}
		else {
			p = p->sibling;
		}
	}
	if (NULL != p) {
		stp = noviStog(current);
		stp->next = head->next;
		head->next = stp;
		printf("\nSuccess\n");
		return p;
	}
	else if (NULL == p) {
		printf("\nDirektorije ne postoji\n");
		return current;
	}
}
Pok izlazDir(stPok head) {
	Pok p = NULL;
	stPok temp = head->next;
	p = temp->current;
	head->next = temp->next;
	free(temp);
	return p;
}
void currentDir(stPok head, Pok current) {
	stPok p = head->next;
	int x = 0, i=0;
	printf("\n");
	if (NULL != p) {
		while (NULL != p) {
			x++;
			p = p->next;
		}
		while (0 != x) {
			p = head;
			for (i = 0; i < x; i++) {
				p = p->next;
			}
			printf("%s/", p->current->name);
			x--;
		}
	}
	printf("%s/\n", current->name);
}
void delDir(Pok current) {
	if (NULL == current) {
		return;
	}
	delDir(current->sibling);
	delDir(current->child);
	free(current);
}