#pragma once

#include "DefaultHuman.h"
#include "TypicalHuman.h"
#include "HealerHuman.h"
#include "GroupCharacters.h"
#include "Serializable.h"

#include <vector>
#include <iostream>

class Battle : public Serializable
{
private:
	//Ход игроков
	int walk;

	GroupCharacters group1;
	GroupCharacters group2;

	//Действия персонажей
	enum action
	{
		Attack = 'x',
		Health = 'h',
		Nothing = 'z'
	};

	//Избавляемся от мертвых тел
	void recountOfSeats(GroupCharacters& group);
public:

	//Выбор команды для хода
	GroupCharacters moveSelection();

	//Выбор команды противника
	GroupCharacters moveSelectionEnemy();

	//Конструктор с параметрами
	Battle(GroupCharacters& _group1, GroupCharacters& _group2);

	//Сделать ход
	bool nextMove(char act, DefaultHuman& you, DefaultHuman& he);

	//Узнать команду
	GroupCharacters getTeam(int num);

	//Конец игры
	bool const checkEndGame();

	//Сериализация
	Document toJSON() override;

	//Десериализация
	bool fromJSON(const Value& value) override;

};