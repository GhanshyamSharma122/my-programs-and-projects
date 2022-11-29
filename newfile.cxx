#include <stdio.h>
#include <conio.h>
int streql(char first[40], char second[40])
{
	int i = 0, diff;
	do
	{
		diff = first[i] - second[i];
		if (diff != 0)
			break;
		i++;
	} while (first[i] != '\0' || second[i] != '\0');
	return diff == 0 ? 1 : 0;
}
struct t
{
	int age, Class;
	char name[30], section[20];
	float per;
} temp;
struct students
{
	int age, Class, rollNo;
	char name[30], section[20];
	float per;
} s;
void showData();
void searchData();
void storeData();
void deleteData();
void editData();
void main()
{
	int ch;
start:
	clrscr();
	printf("STUDENT DATABASE\nSELECT ANY OF THE SERVICES\n1.data entry\n2.show all data \n3.search data\n4.delete data \n5.edit data \n6.exit\n");
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		storeData();
		break;
	case 2:
		showData();
		break;
	case 3:
		searchData();
		break;
	case 4:
		deleteData();
		break;
	case 5:
		editData();
		break;
	case 6:
		goto exit;
	default:
		printf("invalid choice");
		break;
	}
	printf("press any key to continue\n");
	getch();
	getch();
	goto start;
exit:
	getch();
}
void showData()
{
	FILE *fptr;
	fptr = fopen("stddata.html", "r");
	while (fscanf(fptr, "%s	%d %d %s %d %f ", s.name, &s.Class, &s.age, s.section, &s.rollNo, &s.per) != EOF)
	{
		printf("---------------------------------------------\nname : %s\nClass:%d \nAge : %d\nSection : %s\nRoll no : %d\nPercentage : %0.2f \n---------------------------------------------\n", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
	}
	fclose(fptr);
}
void searchData()
{
	FILE *fptr;
	fptr = fopen("stddata.html", "r");
	int check = 1, r, ch, found = 0;
	char nam[30], section[20];
	printf("enter your choice=\n1.search by name\n2.search by roll number and section\n");
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		printf("enter the name to search\n");
		scanf("%s", nam);
		break;
	case 2:
		printf("enter the roll no and section to search\n");
		scanf("%d %s", &r, section);
		break;
	default:
		printf("invalid choice\n");
		check = 0;
		break;
	}
	if (check)
	{
		while (fscanf(fptr, "%s	%d %d %s %d %f ", s.name, &s.Class, &s.age, s.section, &s.rollNo, &s.per) != EOF)
		{
			if (streql(s.name, nam) || (s.rollNo == r && (streql(s.section, section))))
			{
				printf("---------------------------------------------\nname : %s\nClass:%d \nAge : %d\nSection : %s\nRoll no : %d\nPercentage : %0.2f \n---------------------------------------------\n", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
				found = 1;
			}
		}
		if (found == 0)
			printf("\nrecord not found");
	}
	fclose(fptr);
}
void storeData()
{
	FILE *fptr;
	fptr = fopen("stddata.html", "a");
	int n;
	printf("please enter the number of records you want to store?");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("enter the name[separate the first name and last name by dash(_)], class, age ,section,roll no, percentage\n");
		scanf("%s", s.name);
		printf("\n");
		scanf("%d %d %s %d %f", &s.Class, &s.age, s.section, &s.rollNo, &s.per);
		fprintf(fptr, "%s	%d %d %s %d %0.2f ", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
	}
	printf("records added successfully \n");
	fclose(fptr);
}
void deleteData()
{
	FILE *fptr, *temp;
	fptr = fopen("stddata.html", "r");
	temp = fopen("temp", "w");
	char nam[40];
	int roll, success = 0;
	showData();
	printf("Enter the name and rollNo of the record to delete \n");
	scanf("%s %d", nam, &roll);
	while (fscanf(fptr, "%s	%d %d %s %d %f ", s.name, &s.Class, &s.age, s.section, &s.rollNo, &s.per) != EOF)
	{
		if (streql(nam, s.name) && roll == s.rollNo)
		{
			printf("The record Name: %s RollNo:%d was deleted successfully\n", nam, roll);
			success = 1;
		}
		else
		{
			fprintf(temp, "%s	%d %d %s %d %0.2f ", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
		}
	}
	if (success == 0)
	{
		printf("the record was not found\n");
	}
	fclose(fptr);
	fclose(temp);
	remove("stddata.html");
	rename("temp", "stddata.html");
}
void editData()
{
	FILE *fptr, *temp;
	fptr = fopen("stddata.html", "r");
	temp = fopen("temp", "a");
	char nam[40];
	int roll, success = 0;
	showData();
	printf("Enter the name and rollNo of the record to edit \n");
	scanf("%s %d", nam, &roll);
	while (fscanf(fptr, "%s	%d %d %s %d %f ", s.name, &s.Class, &s.age, s.section, &s.rollNo, &s.per) != EOF)
	{
		if (streql(nam, s.name) && roll == s.rollNo)
		{
			printf("The record Name: %s RollNo:%d is found.\nNow give new data to this record(you have to enter all details again of that record)\n", nam, roll);
			printf("enter the name, class, age ,section,roll no, percentage\n");
			scanf("%s", s.name);
			printf("\n");
			scanf("%d %d %s %d %f", &s.Class, &s.age, s.section, &s.rollNo, &s.per);
			fprintf(temp, "%s	%d %d %s %d %0.2f ", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
			success = 1;
		}
		else
		{
			fprintf(temp, "%s	%d %d %s %d %0.2f ", s.name, s.Class, s.age, s.section, s.rollNo, s.per);
		}
	}
	if (success == 0)
	{
		printf("the record was not found\n");
	}
	fclose(fptr);
	fclose(temp);
	remove("stddata.html");
	rename("temp", "stddata.html");
	getch();
}