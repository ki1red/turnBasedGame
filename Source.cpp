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

using namespace std;

void gameTest()
{
	GroupCharacters Green, Blue(vector <DefaultHuman*> (0));
	const int sizeGroups = 2;

	cout << "-----------------ПЕРВАЯ КОМАНДА-----------------" << endl << endl;
	for (size_t i = 0; i < sizeGroups; i++)
	{
		cout << "Добавить: 1- Обычного, 2- Целителя" << endl;
		char k = _getch();
		switch (k)
		{
		case '1':
			Green.addCharacter(new TypicalHuman);
			cout << "Добавлен Обычный" << endl;
			break;
		case '2':
			Green.addCharacter(new HealerHuman);
			cout << "Добавлен Целитель" << endl;
			break;
		default:
			i--;
			continue;
		}
	}

	cout << "-----------------ВТОРАЯ КОМАНДА-----------------" << endl << endl;
	for (size_t i = 0; i < sizeGroups; i++)
	{
		cout << "Добавить: 1- Обычного, 2- Целителя" << endl;
		char k = _getch();
		switch (k)
		{
		case '1':
			Blue.addCharacter(new TypicalHuman);
			cout << "Добавлен Обычный" << endl;
			break;
		case '2':
			Blue.addCharacter(new HealerHuman);
			cout << "Добавлен Целитель" << endl;
			break;
		default:
			i--;
			continue;
		}
	}

	cout << endl << "Нажмите любую клавишу..." << endl;
	char k = _getch();

	bool gameOver = false;
	Battle Game(Green,Blue);
	do
	{

		system("cls");
		//group 1
		cout << "-----------------ПЕРВАЯ КОМАНДА-----------------" << endl;
		for (size_t i = 0; i < Game.getTeam(1).getGroup().size() ; i++)
		{
			if (typeid(*Game.getTeam(1).choiceCharacter(i)) == typeid(HealerHuman))
				cout << i + 1 << " - Целитель\t" << Game.getTeam(1).choiceCharacter(i)->getHealth()*5 << "%" << endl;
			else if (typeid(*Game.getTeam(1).choiceCharacter(i)) == typeid(TypicalHuman))
				cout << i + 1 << " - Обычный\t" << Game.getTeam(1).choiceCharacter(i)->getHealth()*5 << "%" << endl;
		}
		//cout << Game.getTeam(1).getGroup().size() << "\t" << Game.getTeam(2).getGroup().size() << endl;
		//group 1
		cout << endl << "-----------------ВТОРАЯ КОМАНДА-----------------" << endl;
		for (size_t i = 0; i < Game.getTeam(2).getGroup().size() ; i++)
		{
			if (typeid(*Game.getTeam(2).choiceCharacter(i)) == typeid(HealerHuman))
				cout << i + 1 << " - Целитель\t" << Game.getTeam(2).choiceCharacter(i)->getHealth()*5 << "%" << endl;
			else if (typeid(*Game.getTeam(2).choiceCharacter(i)) == typeid(TypicalHuman))
				cout << i + 1 << " - Обычный\t" << Game.getTeam(2).choiceCharacter(i)->getHealth()*5 << "%" << endl;
		}

		if (Game.moveSelection() == Game.getTeam(1))
			cout << "Ходит первая команда. Выберите персонажа" << endl;
		else if (Game.moveSelection() == Game.getTeam(2))
			cout << "Ходит вторая команда. Выберите персонажа" << endl;

		//Выборы персонажей
		char k, g;
		do
		{
			cout << "Выберите персонажа" << endl;
			k = _getch();
			if ((k-'0'-1) >= 0 && (k - '0'-1) < Game.moveSelection().getGroup().size()) break;
			cout << "Нет такого персонажа" << endl;
		} while (true);

		char action;
		//Выбор хода
		if (typeid(*Game.moveSelection().choiceCharacter(k - '0' - 1)) == typeid(TypicalHuman))
			while (true)
			{
				cout << "Выберите действие: Атаковать - x, Ничего - z" << endl;
				action = _getch();
				if (action == 'x' || action == 'z') break;
				cout << "Нет такого действия" << endl;
			}

		else if (typeid(*Game.moveSelection().choiceCharacter(k - '0' - 1)) == typeid(HealerHuman))
			while (true)
			{
				cout << "Выберите действие: Атаковать - x, Лечить - h, Ничего - z" << endl;
				action = _getch();
				if (action == 'x' || action == 'h' || action == 'z') break;
				cout << "Нет такого действия" << endl;
			}

		bool occurred = false;
		//Выбор врага
		do
		{
			if (action == 'z')
			{
				DefaultHuman secretMan;
				occurred = Game.nextMove(action, *Game.moveSelection().choiceCharacter(k - '0' - 1), secretMan);
				if (occurred) break;
			}
			
			if (action == 'h')
				cout << "Выберите товарища по команде" << endl;
			else
				cout << "Выберите противника" << endl;
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

			cout << "Нет такого персонажа" << endl;
		} while (true);

		

		gameOver = Game.checkEndGame();
	} while (!gameOver);

	cout << "-------------------------ИГРА ОКОНЧЕНА----------------------------" << endl;
	cout << "\t\t";

	if (Game.getTeam(1).getGroup().size() == 0)
		cout << "Победила вторая команда" << endl;

	else if (Game.getTeam(2).getGroup().size() == 0)
		cout << "Победила первая команда" << endl;

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

	cout << "\n\tПерсонажи\n" << endl;

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
		std::cout << "Успешно скопировано с Default в Typical " << endl;
	else
		std::cout << "Не удалось скопировать с Default в Typical " << endl;

	if (copyFromArtem)
		std::cout << "Успешно скопировано с Healer в Typical " << endl;
	else
		std::cout << "Не удалось скопировать с Healer в Typical " << endl;

	if (copyFromKirill)
		std::cout << "Успешно скопировано с Typical в Typical " << endl;
	else
		std::cout << "Не удалось скопировать с Typical в Typical " << endl;

	cout << endl << "------------------Edit Leonid T" << endl;
	printJSON(docLeonid);

	cout << "\n\tГруппы персонажей\n" << endl;

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
		std::cout << "Успешно скопировано с Group в Group " << endl;
	else
		std::cout << "Не удалось скопировать с Group в Group " << endl;
	cout << endl << "------------------Edit Blue" << endl;
	printJSON(docBlue);

	cout << "\n\tБои\n" << endl;
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
		std::cout << "Успешно скопировано с Battle в Battle " << endl;
	else
		std::cout << "Не удалось скопировать с Battle в Battle " << endl;
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
