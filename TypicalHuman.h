#pragma once
#include "DefaultHuman.h"
class TypicalHuman : public DefaultHuman
{
public:

	TypicalHuman();

	//������������
	Document toJSON() override;

	//��������������
	bool fromJSON(const Value& value) override;
};