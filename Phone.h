#pragma once

#include <iostream>


class Phone
{
private:
	int id;

protected:
	std::string phone;

public:
	Phone();
	~Phone();
	int GetId();
	std::string GetPhone();
	void SetId(int id);
	void SetPhone(std::string phone);

};


