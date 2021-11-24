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
	//��� �������
	int walk;

	GroupCharacters group1;
	GroupCharacters group2;

	//�������� ����������
	enum action
	{
		Attack = 'x',
		Health = 'h',
		Nothing = 'z'
	};

	//����������� �� ������� ���
	void recountOfSeats(GroupCharacters& group);
public:

	//����� ������� ��� ����
	GroupCharacters moveSelection();

	//����� ������� ����������
	GroupCharacters moveSelectionEnemy();

	//����������� � �����������
	Battle(GroupCharacters& _group1, GroupCharacters& _group2);

	//������� ���
	bool nextMove(char act, DefaultHuman& you, DefaultHuman& he);

	//������ �������
	GroupCharacters getTeam(int num);

	//����� ����
	bool const checkEndGame();

	//������������
	Document toJSON() override;

	//��������������
	bool fromJSON(const Value& value) override;

};