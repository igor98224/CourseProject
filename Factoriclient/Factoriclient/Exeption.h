#pragma once
#include"Libraries.h"
#pragma once
class Exeption :public exception
{
public:
	string errorMessage;
	Exeption(string error) :errorMessage(error) {}
	const char* what() const noexcept { return errorMessage.c_str(); }
	~Exeption() {};
};

