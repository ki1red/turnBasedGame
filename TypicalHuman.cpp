#include "TypicalHuman.h"
#include "DefaultHuman.h"

TypicalHuman::TypicalHuman() : DefaultHuman(6) {}

//Сериализация
Document TypicalHuman::toJSON()
{
	Document document;
	Document::AllocatorType allocator = document.GetAllocator();

	document.SetObject();

	Value documentType;
	documentType.SetString("TypicalHuman", 12, allocator);
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


	return document;
}

//Десериализация
bool TypicalHuman::fromJSON(const Value& value)
{
	if (!value.IsObject()) return false;
	if (!value.HasMember("type")) return false;

	if (std::string(value["type"].GetString()) != std::string("TypicalHuman")) return false;

	int _health;
	bool _regeneration;
	unsigned _hitPower;
	int _regenPower;
	bool _isAlive;

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

	this->health = _health;
	this->regeneration = _regeneration;
	this->hitPower = _hitPower;
	this->regenPower = _regenPower;
	this->isAlive = _isAlive;

	return true;
}