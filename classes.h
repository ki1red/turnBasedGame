#pragma once

class Default_Human
{
protected:
	int health;
	bool regeneration;
	int powerHit;

	const int FULL_HEALTH;

public:
	//�������� �� ���������
	Default_Human();

	~Default_Human();

	//������ ��������
	int getHealth();

	//����������� ��������
	void regen();

	//��������� �����
	void attack(Default_Human enemy);

	//�������� ��������
	bool checkHealth();

};

class typicalHuman : public Default_Human{};

class healerHuman : public Default_Human
{
public:
	void treatOthers(Default_Human other);
};
