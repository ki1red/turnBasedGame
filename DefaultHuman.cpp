#include "DefaultHuman.h"

//Установить новое здоровье
void DefaultHuman::setHealth(int newHealth)
{
	this->health = newHealth;
	checkHealth();
}

//Конструктор с параметрами для целителя
DefaultHuman::DefaultHuman(unsigned _hitPower):FULL_HEALTH(DEFAULT_MAX_HEALTH), health(DEFAULT_MAX_HEALTH), regeneration(true), hitPower(_hitPower), regenPower(1), isAlive(true) {}

//Конструктор
DefaultHuman::DefaultHuman() : FULL_HEALTH(DEFAULT_MAX_HEALTH), health(DEFAULT_MAX_HEALTH), regeneration(true), hitPower(5), regenPower(1), isAlive(true) {}


//Регенерация здоровья
void DefaultHuman::regen()
{
	//Если мёртв
	if (!isAlive) return;

	if (this->regeneration)
		this->setHealth(this->health + this->regenPower);
}

//Нанесение урона
void DefaultHuman::attack(DefaultHuman* enemy)
{
	//Если мёртв
	if (!isAlive) return;

	//Нулевой указатель
	if (enemy == nullptr) return;

	this->regen();
	(*enemy).health -= this->hitPower;
}

//Проверка здоровья
void DefaultHuman::checkHealth()
{
	//Если мёртв
	if (!isAlive) return;

	if (this->health > FULL_HEALTH)
		this->health = FULL_HEALTH;
	else if (this->health <= 0)
		isAlive = false;
}

//Узнать здоровье
const int DefaultHuman::getHealth()
{
	//Если мёртв
	if (!isAlive) return 0;

	return this->health;
}

//Проверка наличия жизни
const bool DefaultHuman::getAlive()
{
	this->checkHealth();
	return isAlive;
}

//Сериализация
Document DefaultHuman::toJSON()
{
	Document document;
	Document::AllocatorType allocator = document.GetAllocator();

	document.SetObject();

	Value documentType;
	documentType.SetString("DefaultHuman", 12, allocator);
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
bool DefaultHuman::fromJSON(const Value& value)
{
	if (!value.IsObject()) return false;
	if (!value.HasMember("type")) return false;

	if (std::string(value["type"].GetString()) != std::string("DefaultHuman")) return false;

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
