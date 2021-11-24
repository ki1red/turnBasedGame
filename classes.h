#pragma once

class Default_Human
{
protected:
	int health;
	bool regeneration;
	int powerHit;

	const int FULL_HEALTH;

public:
	//Значения по умолчанию
	Default_Human();

	~Default_Human();

	//Узнать здоровье
	int getHealth();

	//Регенерация здоровья
	void regen();

	//Нанесение урона
	void attack(Default_Human enemy);

	//Проверка здоровья
	bool checkHealth();

};

class typicalHuman : public Default_Human{};

class healerHuman : public Default_Human
{
public:
	void treatOthers(Default_Human other);
};
