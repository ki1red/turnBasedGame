#pragma once
#include "DefaultHuman.h"
class TypicalHuman : public DefaultHuman
{
public:

	TypicalHuman();

	//Сериализация
	Document toJSON() override;

	//Десериализация
	bool fromJSON(const Value& value) override;
};