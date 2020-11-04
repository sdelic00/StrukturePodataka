#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (256)

struct _person;
typedef struct _person *Position;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;
}Person;

Position createStudent(char *firstName, char *lastName, int birthYear);
void insert(Position where, Position what);
void insertAfter(Position head, Position what, char *lastName);
void insertBefore(Position head, Position what, char *lastName);
void insertLast(Position head, Position what);
void sortList(Position head);
void sort(Position x, Position y);
void printList(Position head);
void findStudent(Position head, char *lastName);
void deleteStudent(Position head, char *lastName);
void saveList(Position head);
void loadList(Position head);

int main(void)
{
	Person head;
	Position p = NULL;
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear = 0;
	int choice = 0;
	int studentChoice = 0;
	int x = 0;
	head.next = NULL;
	while (x == 0)
	{
		choice = 0;
		studentChoice = 0;
		printf("\r\nWhat would you like to do");
		printf("\r\n1 - Add a new student\n2 - Find a specific student\n3 - Delete a student from the list\n4 - Print the list\n5 - Sort the list\n6 - Save the list in a file\n7 - Load a list from a file\n8 - Close the program\n\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("\r\nFirst name: ");
			scanf(" %s", firstName);
			printf("\r\nLast name: ");
			scanf(" %s", lastName);
			printf("\r\nBirth year: ");
			scanf(" %d", &birthYear);
			p = createStudent(firstName, lastName, birthYear);
			printf("\r\nWhere would you like to add the new student");
			printf("\r\n1 - At the start of the list\n2 - At the end of the list\n3 - After a specific student\n4 - Before a specific student\n\n");
			scanf("%d", &studentChoice);
			switch (studentChoice)
			{
			case 1:
				insert(&head, p);
				printf("\r\nStudent added to the list\n");
				break;
			case 2:
				insertLast(&head, p);
				printf("\r\nStudent added to the list\n");
				break;
			case 3:
				printf("\r\nAfter which student would you like to add\n");
				scanf(" %s", lastName);
				insertAfter(&head, p, lastName);
				break;
			case 4:
				printf("\r\nBefore which student would you like to add\n");
				scanf(" %s", lastName);
				insertBefore(&head, p, lastName);
				break;
			default:
				printf("\r\nError - Added at the end of the list\n");
				insertLast(&head, p);
			}
			break;
		case 2:
			printf("\r\nWhich student are you looking for\n");
			scanf(" %s", lastName);
			findStudent(&head, lastName);
			break;
		case 3:
			printf("\r\nWhich student would you like to delete\n");
			printList(&head);
			scanf(" %s", lastName);
			deleteStudent(&head, lastName);
			break;
		case 4:
			printList(&head);
			break;
		case 5:
			sortList(&head);
			break;
		case 6:
			saveList(&head);
			break;
		case 7:
			loadList(&head);
			break;
		case 8:
			x = 1;
			printf("\r\nGoodbye\n");
			break;
		default:
			printf("\r\nError\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}
Position createStudent(char *firstName, char *lastName, int birthYear)
{
	Position p = NULL;
	p = (Position)malloc(sizeof(Person));
	if (NULL == p)
	{
		printf("Memory allocation failed\r\n");
		return NULL;
	}
	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->birthYear = birthYear;

	return p;
}
void insert(Position where, Position what)
{
	what->next = where->next;
	where->next = what;
}
void insertLast(Position head, Position what)
{
	Position p = NULL;
	for (p = head; p->next != NULL; p = p->next);
	insert(p, what);
}
void findStudent(Position head, char *lastName)
{
	Position p = NULL;
	int result = 0;
	for (p = head->next; p != NULL; p = p->next)
	{
		result = strcmp(p->lastName, lastName);
		if (result == 0)
			break;
	}
	if (NULL == p)
		printf("\r\nStudent not found\n");
	else
		printf("\r\nStudent found:\n%s %s %d\n", p->firstName, p->lastName, p->birthYear);
}
void printList(Position head)
{
	Position p = NULL;
	printf("List of content :\r\n");
	for (p = head->next; p != NULL; p = p->next)
	{
		printf("%s %s %d\r\n", p->firstName, p->lastName, p->birthYear);
	}
}
void deleteStudent(Position head, char *lastName)
{
	Position p = NULL;
	Position q = NULL;
	int result = 0;
	int delResult = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		result = strcmp(p->next->lastName, lastName);
		if (result == 0)
		{
			q = p->next;
			p->next = p->next->next;
			free(q);
			delResult = 1;
			break;
		}
	}
	if (delResult == 0)
		printf("\r\nStudent not found\n");
	else
		printf("\r\nStudent removed from the list\n");
}
void insertAfter(Position head, Position what, char *lastName)
{
	Position p = NULL;
	int result = 0;
	int addResult = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		result = strcmp(p->next->lastName, lastName);
		if (result == 0)
		{	
			p = p->next;
			insert(p, what);
			addResult = 1;
			break;
		}
	}
	if (addResult == 0)
	{
		printf("\r\nError - Added at the end of the list\n");
		insertLast(head, p);
	}
	else
		printf("\r\nStudent added to the list\n");
}
void insertBefore(Position head, Position what, char *lastName)
{
	Position p = NULL;
	int result = 0;
	int addResult = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		result = strcmp(p->next->lastName, lastName);
		if (result == 0)
		{
			insert(p, what);
			addResult = 1;
			break;
		}
	}
	if (addResult == 0)
	{
		printf("\r\nError - Added at the end of the list\n");
		insertLast(head, p);
	}
	else
		printf("\r\nStudent added to the list\n");
}
void sortList(Position head)
{
	Position p = NULL;
	Position q = NULL;
	int result = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		for (q = head; q->next->next != NULL; q = q->next)
		{
			result = strcmp(q->next->lastName, q->next->next->lastName);
			if (result > 0)
			{
				sort(q, q->next);
			}
		}
	}
	printf("\r\nList sorted\n");
}
void sort(Position x, Position y)
{
	x->next = y->next;
	y->next = x->next->next;
	x->next->next = y;
}
void saveList(Position head)
{
	FILE *fp;
	Position p = NULL;
	fp = fopen("lista.txt", "w");
	for (p = head->next; p != NULL; p = p->next)
	{
		fprintf(fp, "%s %s %d\n", p->firstName, p->lastName, p->birthYear);
	}
	printf("\r\nList saved\n");
	fclose(fp);
}
void loadList(Position head)
{
	Position p = NULL;
	Position q = NULL;
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear = 0;
	int br = 0, result = 1;
	FILE *fp;
	fp = fopen("lista.txt", "r");
	while (fscanf(fp, " %s %s %d", firstName, lastName, &birthYear) != EOF)
	{
		p = createStudent(firstName, lastName, birthYear);
		for (q = head->next; q != NULL; q = q->next)
		{
			result = strcmp(q->lastName, lastName);
			if(result==0)
				break;
		}
		if (result == 0)
		{
			br++;
			free(p);
		}
		else
			insertLast(head, p);
	}
	if(br==0)
		printf("\r\nList loaded\n");
	else
		printf("\r\nList loaded (some students already exist)\n");
	sortList(head);
	fclose(fp);
}