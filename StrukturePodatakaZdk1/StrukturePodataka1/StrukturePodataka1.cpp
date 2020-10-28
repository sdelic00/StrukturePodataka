#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<malloc.h>

typedef struct
{
	char ime[50];
	char prezime[50];
	int bodovi;
	float relBodovi;
}student;

int brojSt();
int upis(student *, int);
int ispis(student *, int);

int main()
{
	int brSt = 0;
	int er;
	student *stud;
	brSt = brojSt();
	stud = (student *)malloc(brSt * sizeof(student));
	er = upis(stud, brSt);
	er = ispis(stud, brSt);
}
int brojSt()
{
	FILE *pf;
	int brSt = 0;
	pf = fopen("student.txt", "r");
	char x='A';
	while (x!=EOF)
	{
		x = getc(pf);
		if (x == '\n')
			brSt++;
	}
	fclose(pf);
	return brSt;
}
int upis(student *stud, int brSt)
{
	FILE *pf;
	int i;
	int maxBodovi = 30;
	pf = fopen("student.txt", "r");
	for (i = 0; i < brSt; i++)
	{
		fscanf(pf, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
		stud[i].relBodovi = (float)stud[i].bodovi / maxBodovi * 100;
	}
	fclose(pf);
	return 0;
}
int ispis(student *stud, int brSt)
{
	int i;
	int maxBodovi = 30;
	for (i = 0; i < brSt; i++)
	{
		printf("\n%d. student: %s %s\nBodovi: %d/%d\nPostotak: %.2f\n", i + 1, stud[i].ime, stud[i].prezime, stud[i].bodovi, maxBodovi, stud[i].relBodovi);
	}
	return 0;
}