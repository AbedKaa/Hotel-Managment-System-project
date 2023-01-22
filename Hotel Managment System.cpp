#include <iostream>
#include <conio.h>
#include <string.h>
#include <Windows.h>

using namespace std;

FILE* Login;
char findBook;
char password[10];

struct BOOK
{
	int id;
	char name[15];
	char Author[20];
	int quatntity;
	float Price;
	int rackno;
	char* cat;
};
struct BOOK book;

COORD coord = { 0,0 };

//prototype!!!
char categories[][15] = { "Computer","Electronics","Electrical","Civil","Mechanical","Architecture" };
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int getdata(int);
int checkid(int);
void Password();
void get_password(char*);
void issuerecord();
void creditNclose();
void adminsignup();
void gotoxy(int x, int y) {
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void add_window() {
	gotoxy(20, 5);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGORIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20, 7);
	cout << "\xDB\xDB\xDB\xDB\xB2 01 . Computer";
	gotoxy(20, 9);
	cout << "\xDB\xDB\xDB\xDB\xB2 02 . Electronics";
	gotoxy(20, 11);
	cout << "\xDB\xDB\xDB\xDB\xB2 03 . Electrical";
	gotoxy(20, 13);
	cout << "\xDB\xDB\xDB\xDB\xB2 04 . Civil";
	gotoxy(20, 15);
	cout << "\xDB\xDB\xDB\xDB\xB2 05 . Mechanical";
	gotoxy(20, 17);
	cout << "\xDB\xDB\xDB\xDB\xB2 06 . architecture";
	gotoxy(20, 19);
	cout << "\xDB\xDB\xDB\xDB\xB2 07 . Back to main menu";
	gotoxy(20, 21);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
}
void addbooks(void) {
	system("cls");
	FILE* fp;
	int i, choice;
	add_window();
	gotoxy(20, 22);
	cout << "Enter your choice:";
	scanf("%d", &choice);
	if (choice == 7)
		mainmenu();
	system("cls");
	fp = fopen("Records.dat", "ab+");
	if (getdata(choice) == 1)
	{
		book.cat = categories[choice - 1];
		fseek(fp, 0, SEEK_END);
		fwrite(&book, sizeof(book), 1, fp);
		fclose(fp);
		gotoxy(21, 14);
		cout << "The record is sucessfully saved";
		gotoxy(21, 15);
		cout << "Save any more?(Y / N):";
		if (getch() == 'n' || getch() == 'N')
			mainmenu();
		else
		{
			system("cls");
			addbooks();
		}
	}
	fclose(fp);
}

void deletebooks()
{
	FILE* ft;
	FILE* fp;
	system("cls");
	int d, findBooks = 1;
	char another = 'y';
	while (another == 'y')
	{
		system("cls");
		gotoxy(10, 5);
		cout << "Enter the Book ID to  delete:";
		scanf("%d", &d);
		fp = fopen("Record.dat", "rb+");
		while (fread(&book, sizeof(book), 1, fp) == 1)
		{
			if (book.id == d)
			{
				gotoxy(10, 7);
				cout << "The book record is available";
				gotoxy(10, 8);
				cout << "Book name is %s", book.name;
				gotoxy(10, 9);
				cout << "Rack No. is %d", book.rackno;
				findBook = 1;
				gotoxy(10, 10);
				cout << "Do you want to delete it?(Y/N):";
				if (getch() == 'y' || getch() == 'Y')
				{
					ft = fopen("test.dat", "wb");
					rewind(fp);
					while (fread(&book, sizeof(book), 1, fp) == 1)
					{
						if (book.id != d)
						{
							fwrite(&book, sizeof(book), 1, ft);
						}
					}
					fclose(fp);
					fclose(ft);
					remove("Record.dat");
					rename("test.dat", "Record.dat");

					gotoxy(10, 11);
					cout << "The record is sucessfully deleted";
				}
			}
		}
		if (findBook == 0)
		{
			gotoxy(10, 10);
			cout << "No record is found";
			getch();
		}
		gotoxy(10, 12);
		cout << "Delete another record?(Y/N)";
		fflush(stdin);
		another = getch();
	}
}



void viewbooks(void)
{
	int j;
	FILE* fp;
	system("cls");
	gotoxy(1, 1);
	cout << "*********************************Book List*****************************";
	gotoxy(2, 2);
	cout << " CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ";
	j = 4;
	fp = fopen("Record.dat", "rb");
	while (fread(&book, sizeof(book), 1, fp) == 1)
	{
		gotoxy(3, j);
		cout << "%s", book.cat;
		gotoxy(16, j);
		cout << "%d", book.id;
		gotoxy(22, j);
		cout << "%s", book.name;
		gotoxy(36, j);
		cout << "%s", book.Author;
		gotoxy(50, j);
		cout << "%d", book.quatntity;
		gotoxy(57, j);
		cout << "%.2f", book.Price;
		gotoxy(69, j);
		cout << "%d", book.rackno;
		cout << "\n\n";
		j++;
	}
	fclose(fp);
	gotoxy(35, 25);
	returnfunc();
}

void editbooks(void)
{
	system("cls");
	FILE* fp;
	int  c = 0, d;
	gotoxy(20, 4);
	cout << "****Edit Books Section****";
	char another = 'y';
	while (another == 'y')
	{
		system("cls");
		gotoxy(15, 6);
		cout << "Enter Book Id to be edited:";
		scanf("%d", &d);
		fp = fopen("Record.dat", "rb+");
		while (fread(&book, sizeof(book), 1, fp) == 1)
		{
			if (checkid(d) == 0)
			{
				gotoxy(15, 7);
				cout << "The book is availble";
				gotoxy(15, 8);
				cout << "The Book ID:%d", book.id;
				gotoxy(15, 9);
				cout << "Enter new name:";
				scanf("%s", book.name);
				gotoxy(15, 10);
				cout << "Enter new Author:";
				scanf("%s", book.Author);
				gotoxy(15, 11);
				cout << "Enter new quantity:";
				scanf("%d", &book.quatntity);
				gotoxy(15, 12);
				cout << "Enter new price:";
				scanf("%f", &book.Price);
				gotoxy(15, 13);
				cout << "Enter new rackno:";
				scanf("%d", &book.rackno);
				gotoxy(15, 14);
				cout << "The record is modified";
				fseek(fp, ftell(fp) - sizeof(book), 0);
				fwrite(&book, sizeof(book), 1, fp);
				fclose(fp);
				c = 1;
			}
			if (c == 0)
			{
				gotoxy(15, 9);
				cout << "No record found";
			}
		}
		gotoxy(15, 16);
		cout << "Modify another Record?(Y/N)";
		fflush(stdin);
		another = getch();
	}
	returnfunc();
}
//functions!!!


void returnfunc() {
	cout << "\nPress Enter to return to main menu";
a:
	if (getch() == 13)
		mainmenu();
	else
		goto a;
}

void get_password(char* pass) {
	char temp_passP[25];
	int i = 0;
	while (1)
	{
		temp_passP[i] = getch();
		if (temp_passP[i] == 13)
			break;
		else if (temp_passP[i] == 8)
		{
			if (i != 0)
			{
				cout << "\b\b";
				i--;
			}
			else
			{
				cout << "\a";
			}
		}
		else
		{
			cout << "*";
			*(pass + i) = temp_passP[i];
			i++;
		}
		*(pass + i) = '\0';
	}
}

void creditNclose() {
	system("cls");
	gotoxy(16, 3);
	cout << "programmers.....";
	gotoxy(16, 6);
	cout << "Abed karakira & Rami Mahdi";
	gotoxy(16, 8);
	cout << "Department of computer science";
	gotoxy(16, 10);
	cout << "Antonine University,Babdaa";
	gotoxy(16, 11);
	cout << "Exiting int 3 seconds..............>";
	Sleep(3000);
	exit(0);
}



void adminsignup()
{
	char temp[10];
	Login = fopen("password.dat", "wb");
	gotoxy(10, 10);
	cout << "Enter passoed: ";
	get_password(password);
	gotoxy(10, 11);
	cout << "Re Enter Password: ";
	get_password(temp);
	while (strcmp(password, temp) != 0)
	{
		gotoxy(10, 10);
		cout << "Password did not matched! Enter again";
		gotoxy(10, 11);
		cout << "Enter password: ";
		get_password(password);
		gotoxy(11, 12);
		cout << "Re Enter Password: ";
		get_password(temp);
		system("cls");
	}
	fwrite(&password, sizeof(password), 1, Login);
	fclose(Login);
}

void adminsignin() {
	char temp[10];
	Login = fopen("password.dat", "rb");
	gotoxy(10, 10);
	cout << "Enter password: ";
	get_password(temp);
	while (fread(&password, sizeof(password), 1, Login) == 1)
	{
		while (strcmp(temp, password) != 0)
		{
			system("cls");
			gotoxy(10, 10);
			cout << "Password did not match! ";
			cout << "Enter Again: ";
			get_password(temp);
		}
		gotoxy(10, 11);
		cout << "Passwprd Match";
		break;
	}
	fclose(Login);
	gotoxy(10, 12);
	cout << "Press any Key...";
	getch();
}



int change_password() {
	system("cls");
	FILE* Login;
	char old_pass[10], new_pass[10];
	gotoxy(10, 10);
	cout << "Enter Old Password: ";
	get_password(old_pass);
	gotoxy(10, 11);
	cout << "Enter New Password: ";
	get_password(new_pass);
	Login = fopen("password.dat", "rb+");
	while (fread(&password, sizeof(password), 1, Login) == 1)
	{
		if (strcmp(old_pass, password) == 0)
		{
			strcpy(password, new_pass);
			fseek(Login, -sizeof(password), SEEK_CUR);
			fwrite(&password, sizeof(password), 1, Login);
			fclose(Login);
			gotoxy(10, 12);
			cout << "Password sucessfully changed! ";
			return 1;
		}
		else
		{
			gotoxy(10, 12);
			cout << "Password changing process failed! ";
			return 0;
		}
	}
}

int getdata(int choice)
{
	int bookID;
	gotoxy(20, 3);
	cout << "Enter the Information Below";
	gotoxy(20, 4);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20, 5);
	cout << "\xB2";
	gotoxy(46, 5);
	cout << "\xB2";
	gotoxy(20, 6);
	cout << "\xB2";
	gotoxy(46, 6);
	cout << "\xB2";
	gotoxy(20, 7);
	cout << "\xB2";
	gotoxy(46, 7);
	cout << "\xB2";
	gotoxy(20, 8);
	cout << "\xB2";
	gotoxy(46, 8);
	cout << "\xB2";
	gotoxy(20, 9);
	cout << "\xB2";
	gotoxy(46, 9);
	cout << "\xB2";
	gotoxy(20, 10);
	cout << "\xB2";
	gotoxy(46, 10);
	cout << "\xB2";
	gotoxy(20, 11);
	cout << "\xB2";
	gotoxy(46, 11);
	cout << "\xB2";
	gotoxy(20, 12);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(21, 5);
	cout << "Category";
	gotoxy(31, 5);
	cout <<categories[choice - 1];
	gotoxy(21, 6);
	cout << "Book ID: ";
	gotoxy(30, 6);
	scanf("%d", bookID);
	if (checkid(bookID) == 0)
	{
		gotoxy(21, 13);
		cout << "The book id already exists";
		getch();
		addbooks;
		return 0;
	}
	book.id = bookID;
	gotoxy(21, 7);
	cout << "Book Name:";
	gotoxy(33, 7);
	scanf("%s", book.name);
	gotoxy(21, 8);
	cout << "Author:";
	gotoxy(30, 8);
	scanf("%d", book.Author);
	gotoxy(21, 9);
	cout << "Quantity:";
	gotoxy(31, 9);
	scanf("%d", &book.quatntity);
	gotoxy(21, 10);
	cout << "Price:";
	gotoxy(28, 10);
	scanf("%f", &book.Price);
	gotoxy(21, 11);
	cout << "Rack No:";
	gotoxy(30, 11);
	scanf("%d", book.rackno);
}

int checkid(int t)
{
	FILE* temp;
	temp = fopen("Record.dat", "rb+");
	while (fread(&book, sizeof(book), 1, temp) == 1)
	{
		if (book.id == t)
		{
			fclose(temp);
			return 0;
		}
		fclose(temp);
		return 1;
	}
}

void searchByID()
{
	system("cls");
	int id;
	FILE* fp;
	gotoxy(25, 4);
	cout << "****Search Books By Id****";
	gotoxy(20, 5);
	cout << "Enter the book id:";
	scanf("%d", &id);
	int findBook = 0;
	fp = fopen("Record.dat", "rb");
	while (fread(&book, sizeof(book), 1, fp) == 1)
	{
		if (book.id == id)
		{
			Sleep(2);
			gotoxy(20, 7);
			cout << "The Book is available";
			gotoxy(20, 8);
			cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
			gotoxy(20, 9);
			cout << "\xB2 ID:%d", book.id;
			gotoxy(47, 9);
			cout << "\xB2";
			gotoxy(20, 10);
			cout << "\xB2 Name:%s", book.name;
			gotoxy(47, 10);
			cout << "\xB2";
			gotoxy(20, 11);
			cout << "\xB2 Author:%s", book.Author;
			gotoxy(47, 11);
			cout << "\xB2";
			gotoxy(20, 12);
			cout << "\xB2 Quantity:%d", book.quatntity;
			gotoxy(47, 12);
			cout << "\xB2";
			gotoxy(20, 13);
			cout << "\xB2 Price:Rs.%.2f", book.Price;
			gotoxy(47, 13);
			cout << "\xB2";
			gotoxy(20, 14);
			cout << "\xB2 Rack No:%d", book.rackno;
			gotoxy(47, 14);
			cout << "\xB2";
			gotoxy(20, 15);
			cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
			findBook = 1;
		}
	}
	if (findBook == 0)
	{
		gotoxy(20, 8);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(20, 9);
		cout << "\xB2";
		gotoxy(38, 9);
		cout << "\xB2";
		gotoxy(20, 10);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(22, 9);
		cout << "\aNo Reecord Found";
	}
	fclose(fp);
	gotoxy(20, 17);
	cout << "Try another search?(Y/N)";
	if (getch() == 'y' || getch() == 'Y')
		searchByID();
	else
	{
		mainmenu();
	}
}

void searchByName()
{
	system("cls");
	char s[15];
	int d = 0;
	FILE* fp;
	gotoxy(25, 4);
	cout << "****Search Books By Name****";
	gotoxy(20, 5);
	cout << "Enter Book Name:";
	scanf("%s", s);
	fp = fopen("Record.dat", "rb");
	while (fread(&book, sizeof(book), 1, fp) == 1)
	{
		if (strcmp(book.name, (s)) == 0)
		{
			gotoxy(20, 7);
			cout << "The Book is available";
			gotoxy(20, 8);
			cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
			gotoxy(20, 9);
			cout << "\xB2 ID:%d", book.id;
			gotoxy(47, 9);
			cout << "\xB2";
			gotoxy(20, 10);
			cout << "\xB2 Name:%s", book.name;
			gotoxy(47, 10);
			cout << "\xB2";
			gotoxy(20, 11);
			cout << "\xB2 Author:%s", book.Author;
			gotoxy(47, 11);
			cout << "\xB2";
			gotoxy(20, 12);
			cout << "\xB2 Quantity:%d", book.quatntity;
			gotoxy(47, 12);
			cout << "\xB2";
			gotoxy(20, 13);
			cout << "\xB2 Price:Rs.%.2f", book.Price;
			gotoxy(47, 13);
			cout << "\xB2";
			gotoxy(20, 14);
			cout << "\xB2 Rack No:%d", book.rackno;
			gotoxy(47, 14);
			cout << "\xB2";
			gotoxy(20, 15);
			cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
			d++;
		}
	}
	if (d == 0)
	{
		gotoxy(20, 8);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(20, 9);
		cout << "\xB2";
		gotoxy(38, 9);
		cout << "\xB2";
		gotoxy(20, 10);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(22, 9);
		cout << "\aNo Reecord Found";
	}
	fclose(fp);
	gotoxy(20, 17);
	cout << "Try another search?(Y/N)";
	if (getch() == 'y' || getch() == 'Y')
		searchByID();
	else
	{
		mainmenu();
	}
}
	void searchbooks()
{
	system("cls");
	cout << "*****************************Search Books*********************************";
	gotoxy(20, 10);
	cout << "\xDB\xDB\xDB\xB2 1. Search By ID";
	gotoxy(20, 14);
	cout << "\xDB\xDB\xDB\xB2 2. Search By Name";
	gotoxy(15, 20);
	cout << "Enter Your Choice";
	switch (getch())
	{
	case '1':
		searchByID();
		break;
	case '2':
		searchByName();
		break;
	default:
		getch();
		searchbooks();
	}
}
void mainmenu()
{
	while (1)
	{
		system("cls");
		gotoxy(20, 3);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(20, 5);
		cout << "\xDB\xDB\xDB\xDB\xB2 1. Add Books   ";
		gotoxy(20, 7);
		cout << "\xDB\xDB\xDB\xDB\xB2 2. Delete Book";
		gotoxy(20, 9);
		cout << "\xDB\xDB\xDB\xDB\xB2 3. Search Book";
		gotoxy(20, 11);
		cout << "\xDB\xDB\xDB\xDB\xB2 4. View Book List";
		gotoxy(20, 13);
		cout << "\xDB\xDB\xDB\xDB\xB2 5. Edit Book Record ";
		gotoxy(20, 15);
		cout << "\xDB\xDB\xDB\xDB\xB2 6. Change Password";
		gotoxy(20, 17);
		cout << "\xDB\xDB\xDB\xDB\xB2 7. Close Application";
		gotoxy(20, 19);
		cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
		gotoxy(20, 21);
		cout << "Enter your choice:";
		switch (getch())
		{
		case '1':
			addbooks();
			break;
		case '2':
			deletebooks();
			break;
		case '3':
			searchbooks();
			break;
		case '4':
			viewbooks();
			break;
		case '5':
			editbooks();
			break;
		case '6':
			change_password();
			gotoxy(10, 13);
			cout << "press any key to continue....";
			getch();
			break;
		case '7':
			creditNclose();
		default:
			gotoxy(10, 23);
			cout << "\aWrong Entry!!Please re-entered correct option";
			getch();
		}

	}
}

int main() {
	Login = fopen("password.dat", "rb");
	if (Login == NULL)
	{
		gotoxy(10, 9);
		cout << "Database Do not existe. Be an adminstrator. Sign Up";
		adminsignup();
	}
	else
	{
		adminsignin();
	}
	mainmenu();
	return 0;
}
//main menu functions!!!
