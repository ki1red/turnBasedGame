#include "Battle.h"
void printJSN(const Document& d)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	std::cout << buffer.GetString() << std::endl;
}
//Выбор команды для хода
GroupCharacters Battle::moveSelection()
{
	if (walk % 2 == 1)
		return group1;
	else
		return group2;
}

//Выбор команды противника
GroupCharacters Battle::moveSelectionEnemy()
{
	if (walk % 2 != 1)
		return group1;
	else
		return group2;
}		

//Избавляемся от мертвых тел
void Battle::recountOfSeats(GroupCharacters& group)
{
	for (size_t i = 0; i < group.getGroup().size(); i++)
		if (!(*group.choiceCharacter(i)).getAlive())
			group.kickCharacter(group.choiceCharacter(i));
}

//Конструктор с параметрами
Battle::Battle(GroupCharacters& _group1, GroupCharacters& _group2) : group1(_group1), group2(_group2), walk(1) {}

//Сделать ход
bool Battle::nextMove(char a, DefaultHuman& you, DefaultHuman& he)
{
	action act = (action)a;
	if (typeid(you) == typeid(TypicalHuman))
	{
		switch (act)
		{
		case Attack:
			you.attack(&he);
			recountOfSeats(group1);
			recountOfSeats(this->group2);
			this->walk++;
			return true;

		case Nothing:
			you.regen();
			recountOfSeats(this->group1);
			recountOfSeats(this->group2);
			this->walk++;
			return true;

		default:
			return false;
		}
	}
	else if (typeid(you) == typeid(HealerHuman))
	{
		switch (act)
		{
		case Attack:
			you.attack(&he);
			recountOfSeats(this->group1);
			recountOfSeats(this->group2);
			this->walk++;
			return true;

		case Health:
			you.treatOthers(&he);
			recountOfSeats(this->group1);
			recountOfSeats(this->group2);
			this->walk++;
			return true;

		case Nothing:
			you.regen();
			recountOfSeats(this->group1);
			recountOfSeats(this->group2);
			this->walk++;
			return true;

		default:
			return false;
		}
	}
	return false;
}

//Узнать команду
GroupCharacters Battle::getTeam(int num)
{
	switch (num)
	{
	case 1:
		return this->group1;
	case 2:
		return this->group2;
	}
}

//Конец игры
bool const Battle::checkEndGame()
{
	bool g1 = false, g2 = false;
	for (size_t i = 0; i < group1.getGroup().size(); i++)
		if (group1.choiceCharacter(i)->getAlive())
			g1 = true;
	for (size_t i = 0; i < group2.getGroup().size(); i++)
		if (group2.choiceCharacter(i)->getAlive())
			g2 = true;
	return (g1 && g2 ? false : true);
}


//Сериализация
Document Battle::toJSON()
{
	Document document;
	Document::AllocatorType allocator = document.GetAllocator();

	document.SetObject();

	Value documentType;
	documentType.SetString("Battle", 6, allocator);
	document.AddMember("type", documentType, allocator);

	Value documentWalk;
	documentWalk.SetInt(this->walk);
	document.AddMember("walk", documentWalk, allocator);

	Value documentGroup1;
	documentGroup1.CopyFrom((this->group1).toJSON(), allocator);
	document.AddMember("group1", documentGroup1, allocator);

	Value documentGroup2;
	documentGroup2.CopyFrom((this->group2).toJSON(), allocator);
	document.AddMember("group2", documentGroup2, allocator);

	return document;
}

//Десериализация
bool Battle::fromJSON(const Value& value)
{
	if (!value.IsObject()) return false;
	if (!value.HasMember("type")) return false;

	if (std::string(value["type"].GetString()) != std::string("Battle")) return false;

	int _walk;
	GroupCharacters _group1;
	GroupCharacters _group2;

	if (!value.HasMember("walk")) return false;
	else _walk = value["walk"].GetInt();

	if (!value.HasMember("group1")) return false;
	else _group1.fromJSON(value["group1"]);

	if (!value.HasMember("group2")) return false;
	else _group2.fromJSON(value["group2"]);

	this->walk = _walk;
	this->group1 = _group1;
	this->group2 = _group2;

	return true;
}