Ы#pragma once
#include "DefaultHuman.h"
class HealerHuman : public DefaultHuman
{
private:
	//Сила магического восстановления
	int healerPower;

public:
	HealerHuman();

	//Полечить
	void treatOthers(DefaultHuman* other) override;

	//Восстановить здоровье
	void receiveHealing(int health) override;

	//Сериализация
	Document toJSON() override;

	//Десериализация
	bool fromJSON(const Value& value) override;
};
