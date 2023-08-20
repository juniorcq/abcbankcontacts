#include "Phone.h"


Phone::Phone()
{
	this->phone = "";
}
Phone::~Phone()
{
	this->phone = "";
}
int Phone::GetId()
{
	return this->id;
}
std::string Phone::GetPhone()
{
	return this->phone;
}
void Phone::SetId(int id)
{
	this->id = id;
}
void Phone::SetPhone(std::string phone)
{
	this->phone = phone;
}
