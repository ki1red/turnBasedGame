#include "GroupCharacters.h"


//Конструктор с параметрамаи
GroupCharacters::GroupCharacters(std::vector <DefaultHuman*> _party) : party(_party) {}

//Конструктор по умолчанию
GroupCharacters::GroupCharacters() : party(std::vector <DefaultHuman*> (0)) {}

//Добавление нового персонажа в команду
void GroupCharacters::addCharacter(DefaultHuman* character)
{
	for (auto i = this->party.begin(); i != this->party.end(); i++)
		if (*i == character)
			return;

	this->party.push_back(character);
}

//Удаление персонажа из команды
void GroupCharacters::kickCharacter(DefaultHuman* character)
{
	for (auto i = this->party.begin(); i != this->party.end(); i++)
	{
		if ((*i) == character)
			this->party.erase(i);
			break;
	}
}

//Выбрать персонажа
DefaultHuman* GroupCharacters::choiceCharacter(int index)
{
	return getGroup()[index];
}

//Получить список команды
std::vector <DefaultHuman*> GroupCharacters::getGroup()
{
	return this->party;
}

//Сериализация
Document GroupCharacters::toJSON()
{
	Document document;
	Document::AllocatorType allocator = document.GetAllocator();

	document.SetObject();

	Value documentType;
	documentType.SetString("GroupCharacters", 15, allocator);
	document.AddMember("type", documentType, allocator);

	Value documentParty;
	documentParty.SetArray();
	for (size_t i=0; i < this->party.size();i++)
	{
		Value character;
		character.CopyFrom(party[i]->toJSON(), allocator);
		documentParty.PushBack(character, allocator);
	}

	document.AddMember("party", documentParty, allocator);

	return document;
}

//Десериализация
bool GroupCharacters::fromJSON(const Value& value)
{
	if (!value.IsObject()) return false;
	if (!value.HasMember("type")) return false;	

	if (std::string(value["type"].GetString()) != std::string("GroupCharacters")) return false;

	const Value& partyJSON = value["party"].GetArray();

	std::vector <DefaultHuman*> _party(0);


	for (SizeType i = 0; i < partyJSON.Size(); i++)
	{
		const Value& character = partyJSON[i];
		if (!character.IsObject()) return false;
		if (!character.HasMember("type")) return false;

		if (std::string(character["type"].GetString()) == std::string("DefaultHuman"))
		{
			DefaultHuman* human = new DefaultHuman;
			(*human).fromJSON(character);
		
			_party.push_back(human);
		}

		else if (std::string(character["type"].GetString()) == std::string("HealerHuman"))
		{
			DefaultHuman* human = new HealerHuman;
			(*human).fromJSON(character);

			_party.push_back(human);
		}

		else if (std::string(character["type"].GetString()) == std::string("TypicalHuman"))
		{
			DefaultHuman* human = new TypicalHuman;
			(*human).fromJSON(character);

			_party.push_back(human);
		}
	}

	this->party = _party;

	return true;
}

//Оператор сравнения
bool GroupCharacters::operator== (const GroupCharacters& otherGroup)
{
	GroupCharacters group = otherGroup;
	if (group.getGroup().size() != this->party.size()) return false;

	for (size_t i = 0; i < this->party.size(); i++)
		if (this->party[i] != group.choiceCharacter(i))
			return false;

	return true;
}

//Оператор присваивания
GroupCharacters & GroupCharacters::operator= (const GroupCharacters & otherGroup)
{
	std::vector<DefaultHuman*> othergroup = otherGroup.party;
	this->party = othergroup;
	return *this;
}