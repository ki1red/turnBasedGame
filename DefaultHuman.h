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

	//�������� ��������
	void setHealth(int hp);

	//����������� � ����������� ��� ��������
	DefaultHuman(unsigned _hitPower);
public:
	static const unsigned int DEFAULT_MAX_HEALTH = 20U;
	//�������� �� ���������
	DefaultHuman();

	//��������
	virtual void treatOthers(DefaultHuman* other) {};
	
	//������������ ��������
	virtual void receiveHealing(int health) {};

	//����������� ��������
	void regen();

	//��������� �����
	void attack(DefaultHuman *enemy);

	//�������� ��������
	void checkHealth();

	//������ ��������
	const int getHealth();

	//�������� ������� �����
	const bool getAlive();

	//������������
	Document toJSON() override;

	//��������������
	bool fromJSON(const Value& value) override;
};