#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <conio.h>
#include <mutex>
#include <string>
using namespace std;

bool Proverka(string A)
{
	if (A[0] < '1')
		return 0;
	for (int i = 0; i < A.size(); i++)
		if (isdigit(A[i]) == 0)
			return 0;
		return 1;
}


class Game
{
	char** mas;
	int str;
	int sto;
public:
	Game()
	{
		str = 3;
		sto = 3;
		mas = new char*[str];
		for (int i = 0; i < str; i++)
		{
			mas[i] = new char[sto];
		}
		RandMas();
	}
	Game(const int&s,const int&o)
	{
		str = s;
		sto = o;
		mas = new char* [str];
		for (int i = 0; i < str; i++)
		{
			mas[i] = new char[sto];
		}
		RandMas();
	}

	int ProverkaSTO()
	{
		int kolX = 0, kolO = 0;
		for (int i = 0; i < str; i++)
		{
			for (int u = 0; u < sto; u++)
			{
				if (mas[i][u] == 'X')
					kolX++;
				if (mas[i][u] == 'O')
					kolO++;
				//else
				//break;
			}
			if (kolX == sto)
				return 1;
			if (kolO == sto)
				return 2;
			kolO = 0;
			kolX = 0;
		}
		return 0;
	}
	int ProverkaSTR()
	{
		int kolX = 0, kolO = 0;
		for (int i = 0; i < str; i++)
		{
			for (int u = 0; u < sto; u++)
			{
				if (mas[u][i] == 'X')
					kolX++;
				if (mas[u][i] == 'O')
					kolO++;
				/*if (mas[u][i] != 'O' && mas[u][i] != 'X')
					break;*/
			}
			if (kolX == str)
				return 1;
			if (kolO == str)
				return 2;
			kolO = 0;
			kolX = 0;
		}
		return 0;
	}
	void PrintMas()
	{
		for (int i = 0; i < str; i++)
		{
			if (i == 0)
			{
				for (int u = 0; u < sto; u++)
				{
					cout << "\t  -----";
				}
				cout << endl;
			}
			for (int u = 0; u < sto; u++)
			{
				cout << "\t|   " << mas[i][u];
				if (u == sto - 1)
					cout << "\t|";
			}
			cout << "\n";			
			for (int u = 0; u < sto; u++)
			{				
				cout << "\t  -----";
			}
			cout << "\n";
		}
	}
	void RandMas()
	{
		for (int i = 0; i < str; i++)
		{
			for (int u = 0; u < sto; u++)
			{
				mas[i][u] = ' ';
			}
		}
	}
	void VvodX()
	{
		int st, o;
		system("cls");
		PrintMas();
		string pr;
re1:	cout << "Enter coordinates for 'X'.\n";
		while (Proverka(pr) == 0 || stoi(pr) > str)
		{
			cout << "str: ";
			cin >> pr;
			if (Proverka(pr) == 0 || stoi(pr) > str)
				cout << "Wrong input.\n";
		}
		st = stoi(pr) - 1;
		pr.clear();
		while (Proverka(pr) == 0 || stoi(pr) > sto)
		{
			cout << "sto: ";
			cin >> pr;
			if (Proverka(pr) == 0 || stoi(pr) > sto)
				cout << "Wrong input.\n";
		}
		o = stoi(pr) - 1;
		if (mas[st][o] == 'X' || mas[st][o] == 'O')
		{
			pr.clear();
			goto re1;
		}
		mas[st][o] = 'X';
		system("cls");		
		if (ProverkaSTO() == 1 || ProverkaSTR() == 1)
		{
			cout << "\t\t~~~~~~~ 'X' won! ~~~~~~~\n\n";
		}
		if (ProverkaSTO() == 2 || ProverkaSTR() == 2)
		{
			cout << "\t\t~~~~~~~ 'O' won! ~~~~~~~\n\n";
		}
	}
	void VvodO()
	{
		int st, o;
		system("cls");
		PrintMas();
		string pr;
re2:	cout << "Enter coordinates for 'O'.\n";
		while (Proverka(pr) == 0 || stoi(pr) > str)
		{
			cout << "str: ";
			cin >> pr;
			if (Proverka(pr) == 0 || stoi(pr) > str)
				cout << "Wrong input.\n";
		}
		st = stoi(pr) - 1;
		pr.clear();
		while (Proverka(pr) == 0 || stoi(pr) > sto)
		{
			cout << "sto: ";
			cin >> pr;
			if (Proverka(pr) == 0 || stoi(pr) > sto)
				cout << "Wrong input.\n";
		}
		o = stoi(pr) - 1;
		if (mas[st][o] == 'X' || mas[st][o] == 'O')
		{
			pr.clear();
			goto re2;
		}
		mas[st][o] = 'O';
		system("cls");
		PrintMas();
		if (ProverkaSTO() == 1 || ProverkaSTR() == 1)
		{
			cout << "\t\t~~~~~~~ 'X' won! ~~~~~~~\n\n";
		}
		if (ProverkaSTO() == 2 || ProverkaSTR() == 2)
		{
			cout << "\t\t~~~~~~~ 'O' won! ~~~~~~~\n\n";
		}
	}
	void Menu()
	{
		char vvod;
		do
		{
			system("cls");
			cout << "1. Game VS bot.\n2. Solo game.\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				while (true)
				{
					VvodX();
					VvodO();
				}
				system("pause");
				break;
			}
			case'2':
			{
				while (ProverkaSTO() == 0 || ProverkaSTR() == 0)
				{
					VvodX();
					if (ProverkaSTO() != 0 || ProverkaSTR() != 0)
						break;
					VvodO();
				}
				system("pause");
				break;
			}
			default:
			{
				system("cls");
				cout << "\tWrong input.\n";
				system("pause");
				break;
			}
			}

		} while (vvod != 27);
	}

	/*int getStr() { return str; }
	int getSto() { return sto; }
	void setStr(const int& s) { str = s; }
	void setSto(const int& o) { sto = o; }
	char** getMas() { return mas; }*/
};

void main()
{
	Game A;

	A.Menu();
}