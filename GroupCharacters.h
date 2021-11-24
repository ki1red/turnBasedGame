#pragma once
#include "DefaultHuman.h"
#include "TypicalHuman.h"
#include "HealerHuman.h"
#include "Serializable.h"

#include <vector>
#include <iostream>

class GroupCharacters : public Serializable
{
private:
	
	std::vector <DefaultHuman*> party;
public:
	//Конструктор с параметрами
	GroupCharacters(std::vector <DefaultHuman*> _party);

	//Конструктор по умолчанию
	GroupCharacters();
	
	//Добавление нового персонажа в команду
	void addCharacter(DefaultHuman* character);

	//Удаление персонажа из команды
	void kickCharacter(DefaultHuman* character);

	//Выбрать персонажа
	DefaultHuman* choiceCharacter(int index);

	//Получить список команды
	std::vector <DefaultHuman*> getGroup();

	//Сериализация
	Document toJSON() override;

	//Десериализация
	bool fromJSON(const Value& value) override;

	bool operator== (const GroupCharacters& otherGroup);

	GroupCharacters & operator= (const GroupCharacters& otherGroup);
};