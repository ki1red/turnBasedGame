#include "HealerHuman.h"
#include "DefaultHuman.h"

//Конструкор
HealerHuman::HealerHuman() : DefaultHuman(), healerPower(3) {};

//Полечить
void HealerHuman::treatOthers(DefaultHuman* other)
{
	//Если мёртв
	if (!isAlive) return;

	//Нулевой указатель
	if (other == nullptr) return;

	this->regen();
	(*other).receiveHealing(healerPower);
	(*other).checkHealth();
}

//Восстановить здоровье
void HealerHuman::receiveHealing(int health)
{
	//Если мёртв
	if (!isAlive) return;

	this->setHealth(this->health + health);
}

//Сериализация
Document HealerHuman::toJSON()
{
	Document document;
	Document::AllocatorType allocator = document.GetAllocator();

	document.SetObject();

	Value documentType;
	documentType.SetString("HealerHuman", 11, allocator);
	document.AddMember("type", documentType, allocator);

	Value documentHealth;
	documentHealth.SetInt(this->health);
	document.AddMember("health", documentHealth, allocator);

	Value documentRegeneration;
	documentRegeneration.SetBool(this->regeneration);
	document.AddMember("regeneration", documentRegeneration, allocator);

	Value documentHitPower;
	documentHitPower.SetInt(this->hitPower);
	document.AddMember("hitPower", documentHitPower, allocator);

	Value documentRegenPower;
	documentRegenPower.SetInt(this->regenPower);
	document.AddMember("regenPower", documentRegenPower, allocator);

	Value documentIsAlive;
	documentIsAlive.SetBool(this->isAlive);
	document.AddMember("isAlive", documentIsAlive, allocator);

	Value documentHealerPower;
	documentHealerPower.SetInt(this->healerPower);
	document.AddMember("healerPower", documentHealerPower, allocator);

	return document;
}

//Десериализация
bool HealerHuman::fromJSON(const Value& value)
{
	if (!value.IsObject()) return false;
	if (!value.HasMember("type")) return false;

	if (std::string(value["type"].GetString()) != std::string("HealerHuman")) return false;

	int _health;
	bool _regeneration;
	unsigned _hitPower;
	int _regenPower;
	bool _isAlive;
	int _healerPower;

	if (!value.HasMember("health")) return false;
	else _health = value["health"].GetInt();

	if (!value.HasMember("regeneration")) return false;
	else _regeneration = value["regeneration"].GetBool();

	if (!value.HasMember("hitPower")) return false;
	else _hitPower = value["hitPower"].GetInt();

	if (!value.HasMember("regenPower")) return false;
	else _regenPower = value["regenPower"].GetInt();

	if (!value.HasMember("isAlive")) return false;
	else _isAlive = value["isAlive"].GetBool();

	if (!value.HasMember("healerPower")) return false;
	else _healerPower = value["healerPower"].GetBool();

	this->health = _health;
	this->regeneration = _regeneration;
	this->hitPower = _hitPower;
	this->regenPower = _regenPower;
	this->isAlive = _isAlive;
	this->healerPower = _healerPower;

	return true;
}