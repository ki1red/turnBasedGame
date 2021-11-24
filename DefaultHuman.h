#pragma once
#include "Serializable.h"
class DefaultHuman : public Serializable
{
protected:
	int health;
	bool regeneration;
	unsigned hitPower;
	int regenPower;
	bool isAlive;

	const int FULL_HEALTH;

	//Добавить здоровье
	void setHealth(int hp);

	//Конструктор с параметрами для целителя
	DefaultHuman(unsigned _hitPower);
public:
	static const unsigned int DEFAULT_MAX_HEALTH = 20U;
	//Значения по умолчанию
	DefaultHuman();

	//Исцелить
	virtual void treatOthers(DefaultHuman* other) {};
	
	//Восстановить здоровье
	virtual void receiveHealing(int health) {};

	//Регенерация здоровья
	void regen();

	//Нанесение урона
	void attack(DefaultHuman *enemy);

	//Проверка здоровья
	void checkHealth();

	//Узнать здоровье
	const int getHealth();

	//Проверка наличия жизни
	const bool getAlive();

	//Сериализация
	Document toJSON() override;

	//Десериализация
	bool fromJSON(const Value& value) override;
};