
#include "DefaultHuman.h"
#include "TypicalHuman.h"
#include "HealerHuman.h"
#include "GroupCharacters.h"
#include "Battle.h"
#include <memory>

#include <iostream>
#include <vector>
#include <conio.h>
#include "Serializable.h"
#include "Utility.h"

using namespace std;

//�������� ��������� ����� �����������
bool attacks(DefaultHuman &player1, DefaultHuman &player2)
{
	//��������� �����
	player1.attack(&player2);
	player1.attack(&player2);
	player1.attack(&player2);

	if (player2.getHealth() == 5)
	{
		player2.attack(&player1);
		player2.attack(&player1);
		player2.attack(&player1);

		if (player1.getHealth() == 5)
			return true;
		else
			return false;
	}
	else
		return false;
}

//�����������
bool regeneration(DefaultHuman &player1, DefaultHuman &player2)
{
	if (player2.getHealth() == 8)
	{
		player2.regen();
		player1.regen();
		if (player2.getHealth() == 9 && player1.getHealth() == 6)
			return true;
		else
			return false;
	}
	else
		return false;
}

//��������� ���������
bool receivingTreatment(DefaultHuman &player1, HealerHuman &player2)
{
	player2.treatOthers(&player1);
	player2.treatOthers(&player2);
	if (player2.getHealth() == 14 && player1.getHealth() == 9)
	{
		player2.treatOthers(&player2);
		player2.treatOthers(&player2);
		player2.treatOthers(&player2);
		if (player2.getHealth() == 20)
			return true;
		else
			return false;
	}
	else
		return false;
}

//��� ����
bool isAlive(DefaultHuman& player1, HealerHuman& player2)
{
	player1.attack(&player2);
	player1.attack(&player2);
	player1.attack(&player2);

	if (player2.getAlive())
	{
		player1.attack(&player2);
		if (!player2.getAlive())
			return true;
		else
			return false;
	}
	else
		return false;
}

//���������� ������ � �������
bool addCharacter(GroupCharacters &group)
{
	DefaultHuman Anna;
	TypicalHuman Maria;
	HealerHuman Kirill;

	group.addCharacter(&Anna);
	group.addCharacter(&Kirill);
	group.addCharacter(&Maria);
	group.addCharacter(&Kirill);

	if (group.getGroup().size() == 5)
		return true;
	else
		return false;
}

void firstTest()
{
	TypicalHuman Leonid;
	HealerHuman Andrey;

	//��� �������� ������
	struct Test
	{
		bool value;
		string name;
	};

	vector <Test> test(5);

	test[0].name = "����� - ";
	test[1].name = "����������� - ";
	test[2].name = "��������� - ";
	test[3].name = "���������� � ������� - ";
	test[4].name = "������ ��������� - ";

	test[0].value = attacks(Leonid, Andrey);
	test[1].value = regeneration(Leonid, Andrey);
	test[2].value = receivingTreatment(Leonid, Andrey);

	//������ �������� ������ ����������
	vector<DefaultHuman*> groupVector(0);
	groupVector.push_back(&Leonid);
	groupVector.push_back(&Andrey);
	GroupCharacters groupPeople(groupVector);

	test[3].value = addCharacter(groupPeople);
	test[4].value = isAlive(Leonid, Andrey);

	//�������� �����������
	for (size_t i = 0; i < test.size(); i++)
		cout << test[i].name << ((test[i].value) ? "�������" : "���������") << endl;



	vector <DefaultHuman*> groupForPrint = groupPeople.getGroup();
	for (size_t i = 0; i < groupForPrint.size(); i++)
		cout << groupForPrint[i] << endl;

	cout << endl << endl;

}

void gameTest()
{
	GroupCharacters Green, Blue(vector <DefaultHuman*> (0));
	const int sizeGroups = 2;

	cout << "-----------------������ �������-----------------" << endl << endl;
	for (size_t i = 0; i < sizeGroups; i++)
	{
		cout << "��������: 1- ��������, 2- ��������" << endl;
		char k = _getch();
		switch (k)
		{
		case '1':
			Green.addCharacter(new TypicalHuman);
			cout << "�������� �������" << endl;
			break;
		case '2':
			Green.addCharacter(new HealerHuman);
			cout << "�������� ��������" << endl;
			break;
		default:
			i--;
			continue;
		}
	}

	cout << "-----------------������ �������-----------------" << endl << endl;
	for (size_t i = 0; i < sizeGroups; i++)
	{
		cout << "��������: 1- ��������, 2- ��������" << endl;
		char k = _getch();
		switch (k)
		{
		case '1':
			Blue.addCharacter(new TypicalHuman);
			cout << "�������� �������" << endl;
			break;
		case '2':
			Blue.addCharacter(new HealerHuman);
			cout << "�������� ��������" << endl;
			break;
		default:
			i--;
			continue;
		}
	}

	cout << endl << "������� ����� �������..." << endl;
	char k = _getch();

	bool gameOver = false;
	Battle Game(Green,Blue);
	do
	{

		system("cls");
		//group 1
		cout << "-----------------������ �������-----------------" << endl;
		for (size_t i = 0; i < Game.getTeam(1).getGroup().size() ; i++)
		{
			if (typeid(*Game.getTeam(1).choiceCharacter(i)) == typeid(HealerHuman))
				cout << i + 1 << " - ��������\t" << Game.getTeam(1).choiceCharacter(i)->getHealth()*5 << "%" << endl;
			else if (typeid(*Game.getTeam(1).choiceCharacter(i)) == typeid(TypicalHuman))
				cout << i + 1 << " - �������\t" << Game.getTeam(1).choiceCharacter(i)->getHealth()*5 << "%" << endl;
		}
		//cout << Game.getTeam(1).getGroup().size() << "\t" << Game.getTeam(2).getGroup().size() << endl;
		//group 1
		cout << endl << "-----------------������ �������-----------------" << endl;
		for (size_t i = 0; i < Game.getTeam(2).getGroup().size() ; i++)
		{
			if (typeid(*Game.getTeam(2).choiceCharacter(i)) == typeid(HealerHuman))
				cout << i + 1 << " - ��������\t" << Game.getTeam(2).choiceCharacter(i)->getHealth()*5 << "%" << endl;
			else if (typeid(*Game.getTeam(2).choiceCharacter(i)) == typeid(TypicalHuman))
				cout << i + 1 << " - �������\t" << Game.getTeam(2).choiceCharacter(i)->getHealth()*5 << "%" << endl;
		}

		if (Game.moveSelection() == Game.getTeam(1))
			cout << "����� ������ �������. �������� ���������" << endl;
		else if (Game.moveSelection() == Game.getTeam(2))
			cout << "����� ������ �������. �������� ���������" << endl;

		//������ ����������
		char k, g;
		do
		{
			cout << "�������� ���������" << endl;
			k = _getch();
			if ((k-'0'-1) >= 0 && (k - '0'-1) < Game.moveSelection().getGroup().size()) break;
			cout << "��� ������ ���������" << endl;
		} while (true);

		char action;
		//����� ����
		if (typeid(*Game.moveSelection().choiceCharacter(k - '0' - 1)) == typeid(TypicalHuman))
			while (true)
			{
				cout << "�������� ��������: ��������� - x, ������ - z" << endl;
				action = _getch();
				if (action == 'x' || action == 'z') break;
				cout << "��� ������ ��������" << endl;
			}

		else if (typeid(*Game.moveSelection().choiceCharacter(k - '0' - 1)) == typeid(HealerHuman))
			while (true)
			{
				cout << "�������� ��������: ��������� - x, ������ - h, ������ - z" << endl;
				action = _getch();
				if (action == 'x' || action == 'h' || action == 'z') break;
				cout << "��� ������ ��������" << endl;
			}

		bool occurred = false;
		//����� �����
		do
		{
			if (action == 'z')
			{
				DefaultHuman secretMan;
				occurred = Game.nextMove(action, *Game.moveSelection().choiceCharacter(k - '0' - 1), secretMan);
				if (occurred) break;
			}
			
			if (action == 'h')
				cout << "�������� �������� �� �������" << endl;
			else
				cout << "�������� ����������" << endl;
			g = _getch();
			

			if (action == 'h')
			{
				if ((g - '0' - 1) >= 0 && (g - '0' - 1) < Game.moveSelection().getGroup().size())
					occurred = Game.nextMove(action, *Game.moveSelection().choiceCharacter(k - '0' - 1), *Game.moveSelection().choiceCharacter(g - '0' - 1));
			}
			else
				if ((g - '0' - 1) >= 0 && (g - '0' - 1) < Game.moveSelectionEnemy().getGroup().size())
					occurred = Game.nextMove(action, *Game.moveSelection().choiceCharacter(k - '0' - 1), *Game.moveSelectionEnemy().choiceCharacter(g - '0' - 1));
			
			if (occurred) break;

			cout << "��� ������ ���������" << endl;
		} while (true);

		

		gameOver = Game.checkEndGame();
	} while (!gameOver);

	cout << "-------------------------���� ��������----------------------------" << endl;
	cout << "\t\t";

	if (Game.getTeam(1).getGroup().size() == 0)
		cout << "�������� ������ �������" << endl;

	else if (Game.getTeam(2).getGroup().size() == 0)
		cout << "�������� ������ �������" << endl;

}

void printJSON(const Document& d)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	cout << buffer.GetString() << endl;
}

void testJSON()
{

	cout << "\n\t���������\n" << endl;

	DefaultHuman Andrey;
	HealerHuman Artem;
	TypicalHuman Kirill;
	TypicalHuman Leonid;

	Andrey.attack(&Kirill);

	Document docAndrey = Andrey.toJSON();
	Document docArtem = Artem.toJSON();
	Document docKirill = Kirill.toJSON();
	bool copyFromAndrey = Leonid.fromJSON(docAndrey);
	bool copyFromArtem = Leonid.fromJSON(docArtem);
	bool copyFromKirill = Leonid.fromJSON(docKirill);
	Document docLeonid = Leonid.toJSON();

	cout << endl << "------------------Andrey D" << endl;
	printJSON(docAndrey);
	cout << endl << "------------------Artem H" << endl;
	printJSON(docArtem);
	cout << endl << "------------------Kirill T" << endl;
	printJSON(docKirill);
	cout << endl << "------------------Leonid T" << endl;
	printJSON(docAndrey);


	if (copyFromAndrey)
		std::cout << "������� ����������� � Default � Typical " << endl;
	else
		std::cout << "�� ������� ����������� � Default � Typical " << endl;

	if (copyFromArtem)
		std::cout << "������� ����������� � Healer � Typical " << endl;
	else
		std::cout << "�� ������� ����������� � Healer � Typical " << endl;

	if (copyFromKirill)
		std::cout << "������� ����������� � Typical � Typical " << endl;
	else
		std::cout << "�� ������� ����������� � Typical � Typical " << endl;

	cout << endl << "------------------Edit Leonid T" << endl;
	printJSON(docLeonid);

	cout << "\n\t������ ����������\n" << endl;

	GroupCharacters green, blue;
	
	green.addCharacter(&Kirill);
	green.addCharacter(&Andrey);
	//std::shared_ptr<DefaultHuman> Vasiliy = std::make_shared<HealerHuman>(HealerHuman());
	//DefaultHuman* Vasiliy = new HealerHuman;

	Document docGreen = green.toJSON();
	cout << endl << "------------------Green" << endl;
	printJSON(docGreen);
	//const Value& gr = docGreen["party"];

	blue.addCharacter(&Artem);
	blue.addCharacter(&Leonid);

	Document docBlue = blue.toJSON();
	cout << endl << "------------------Blue" << endl;
	printJSON(docBlue);

	bool copyFromGreen = blue.fromJSON(docGreen);
	docBlue = blue.toJSON();
	if (copyFromGreen)
		std::cout << "������� ����������� � Group � Group " << endl;
	else
		std::cout << "�� ������� ����������� � Group � Group " << endl;
	cout << endl << "------------------Edit Blue" << endl;
	printJSON(docBlue);

	cout << "\n\t���\n" << endl;
	Battle first(green, blue), second(blue, green);

	
	cout << endl << "------------------First Game" << endl;
	first.nextMove('x', *first.moveSelection().choiceCharacter(0), *first.moveSelectionEnemy().choiceCharacter(0));
	first.nextMove('x', *first.moveSelection().choiceCharacter(0), *first.moveSelectionEnemy().choiceCharacter(0));
	first.nextMove('x', *first.moveSelection().choiceCharacter(0), *first.moveSelectionEnemy().choiceCharacter(0));
	Document docFirst = first.toJSON();
	printJSON(docFirst);


	Document docSecond = second.toJSON();
	cout << endl << "------------------Second Game" << endl;
	printJSON(docSecond);

	bool copyFromFirst = second.fromJSON(docFirst);
	if (copyFromFirst)
		std::cout << "������� ����������� � Battle � Battle " << endl;
	else
		std::cout << "�� ������� ����������� � Battle � Battle " << endl;
	cout << endl << "------------------Edit Second" << endl;
	docSecond = second.toJSON();
	printJSON(docSecond);

}


void main()
{
	setlocale(LC_ALL, "Ru");
	//firstTest();
	//gameTest();
	testJSON();

	return;
}