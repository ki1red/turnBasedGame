#pragma once
#include "DefaultHuman.h"
class HealerHuman : public DefaultHuman
{
private:
	//���� ����������� ��������������
	int healerPower;

public:
	HealerHuman();

	//��������
	void treatOthers(DefaultHuman* other) override;

	//������������ ��������
	void receiveHealing(int health) override;

	//������������
	Document toJSON() override;

	//��������������
	bool fromJSON(const Value& value) override;
};
