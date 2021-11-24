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
	//����������� � �����������
	GroupCharacters(std::vector <DefaultHuman*> _party);

	//����������� �� ���������
	GroupCharacters();
	
	//���������� ������ ��������� � �������
	void addCharacter(DefaultHuman* character);

	//�������� ��������� �� �������
	void kickCharacter(DefaultHuman* character);

	//������� ���������
	DefaultHuman* choiceCharacter(int index);

	//�������� ������ �������
	std::vector <DefaultHuman*> getGroup();

	//������������
	Document toJSON() override;

	//��������������
	bool fromJSON(const Value& value) override;

	bool operator== (const GroupCharacters& otherGroup);

	GroupCharacters & operator= (const GroupCharacters& otherGroup);
};