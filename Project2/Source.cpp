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
	int xod;
public:
	Game()
	{
		xod = 0;
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
		xod = 0;
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
				else if (mas[i][u] == 'O')
					kolO++;
				else
				break;
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
				else if (mas[u][i] == 'O')
					kolO++;
				else
					break;
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
	int ProverkaDIA()
	{
		int kolX = 0, kolO = 0;
		for (int i = 0; i < str; i++)
		{
			for (int u = 0; u < sto; u++)
			{
				if (u == i)
				{
					if (mas[i][u] == 'X')
						kolX++;
					else if (mas[i][u] == 'O')
						kolO++;
					else
						break;
				}
			}
			if (kolX == str)
				return 1;
			if (kolO == str)
				return 2;
		}
		return 0;
	}
	int ProverkaDIA2()
	{
		int kolX = 0, kolO = 0;
		for (int i = 0; i < str; i++)
		{
			for (int u = 0; u < sto; u++)
			{
				if (u+i==sto-1)
				{
					if (mas[i][u] == 'X')
						kolX++;
					else if (mas[i][u] == 'O')
						kolO++;
					else
						break;
				}
			}
			if (kolX == str)
				return 1;
			if (kolO == str)
				return 2;
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
		xod = 0;
	}
	bool VvodX()
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
		xod++;
		system("cls");
		PrintMas();
		if (ProverkaSTO() == 1 || ProverkaSTR() == 1 || ProverkaDIA() == 1 || ProverkaDIA2() == 1)
		{
			cout << "\t\t~~~~~~~ 'X' won! ~~~~~~~\n\n";
			return 1;
		}
		if (ProverkaSTO() == 2 || ProverkaSTR() == 2 || ProverkaDIA() == 2 || ProverkaDIA2() == 2)
		{
			cout << "\t\t~~~~~~~ 'O' won! ~~~~~~~\n\n";
			return 1;
		}
		if (xod >= str * sto)
		{
			cout << "\tNobody won.\n";
			return 0;
		}
		return 0;
	}
	bool VvodO()
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
		xod++;
		system("cls");
		PrintMas();
		if (ProverkaSTO() == 1 || ProverkaSTR() == 1 || ProverkaDIA() == 1 || ProverkaDIA2() == 1)
		{
			cout << "\t\t~~~~~~~ 'X' won! ~~~~~~~\n\n";
			return 1;
		}
		if (ProverkaSTO() == 2 || ProverkaSTR() == 2 || ProverkaDIA() == 2 || ProverkaDIA2() == 2)
		{
			cout << "\t\t~~~~~~~ 'O' won! ~~~~~~~\n\n";
			return 1;
		}
		if (xod >= str * sto)
		{
			cout << "\tNobody won.\n";
			return 0;
		}
		return 0;
	}
	bool BotO()
	{
		bool f = true;
		int s = rand() % str, g = rand() % sto;
		while (f)
		{			
			if (mas[s][g] == 'X' || mas[s][g] == 'O')
			{
				s = rand() % str;
				g = rand() % sto;			
			}
			else
			{
				mas[s][g] = 'O';
				xod++;
				f = false;
			}
		}
		cout << "Bot is thinking...\n";
		this_thread::sleep_for(chrono::milliseconds(rand()%1000+500));
		system("cls");
		PrintMas();
		if (ProverkaSTO() == 1 || ProverkaSTR() == 1 || ProverkaDIA() == 1 || ProverkaDIA2() == 1)
		{
			cout << "\t\t~~~~~~~ 'X' won! ~~~~~~~\n\n";
			return 1;
		}
		if (ProverkaSTO() == 2 || ProverkaSTR() == 2 || ProverkaDIA() == 2 || ProverkaDIA2() == 2)
		{
			cout << "\t\t~~~~~~~ 'O' won! ~~~~~~~\n\n";
			return 1;
		}
		if (xod >= str * sto)
		{
			cout << "\tNobody won.\n";
			return 0;
		}
		return 0;
	}
	void Menu()
	{
		char vvod;
		do
		{
			system("cls");
			cout << "\t1. Game VS Bot.\n\t2. Solo game.\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				while (xod < str * sto)
				{
					if (VvodX()|| xod >= str * sto)
						break;

					if (BotO()|| xod >= str * sto)
						break;
				}
				system("pause");
				RandMas();
				break;
			}
			case'2':
			{
				while (xod < str * sto)
				{					
					if (VvodX()|| xod >= str * sto)
						break;
					
					if (VvodO()|| xod >= str * sto)
						break;
				}
				system("pause");
				RandMas();
				break;
			}
			}

		} while (vvod != 27);
	}

};

void main()
{
	srand(time(0));
	Game A;

	A.Menu();
}