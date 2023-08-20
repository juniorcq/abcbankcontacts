#pragma once

#include <iostream>

class Address
{
private:
	int id;

protected:
	std::string address;

public:

	Address(std::string address = "");
	~Address();

	int GetId();
	std::string GetAddress();

	void SetId(int id);
	void SetAddress(std::string address);

};

