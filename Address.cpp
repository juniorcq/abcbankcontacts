#include "Address.h"

Address::Address(std::string address)
{
	this->address = address;
}
Address::~Address()
{
	this->address = "";
}

int Address::GetId()
{
	return this->id;
}
std::string Address::GetAddress()
{
	return this->address;
}

void Address::SetId(int id)
{
	this->id = id;
}
void Address::SetAddress(std::string address)
{
	this->address = address;
}


