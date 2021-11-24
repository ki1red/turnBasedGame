#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;
class Serializable {
public:
	Serializable() {};

	//Сериализация по умолчанию
	virtual Document toJSON() = 0;

	//Десериализация по умолчанию
	virtual bool fromJSON(const Value& value) = 0;
};