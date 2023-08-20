
#include "Contact.h"

Contact::Contact()
{
	this->firstName = "";
	this->secondName = "";
	this->birthday = "";
	this->personalPhotoUrl = "";

}
Contact::Contact(std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL)
{
	this->firstName = firstName;
	this->secondName = secondName;
	this->birthday = birthday;
	this->personalPhotoUrl = personalPhotoURL;

}
Contact::~Contact()
{
	this->firstName = "";
	this->secondName = "";
	this->birthday = "";
	this->personalPhotoUrl = "";

}

int Contact::GetId()
{
	return this->id;
}
std::string Contact::GetFirstName()
{
	return this->firstName;
}
std::string Contact::GetSecondName()
{
	return this->secondName;
}
std::string Contact::GetBirthday()
{
	return this->birthday;
}
std::string Contact::GetPersonalPhotoUrl()
{
	return this->personalPhotoUrl;
}

void Contact::SetId(int id)
{
	this->id = id;
}
void Contact::SetFirstName(std::string firstName)
{
	this->firstName = firstName;
}
void Contact::SetSecondName(std::string secondName)
{
	this->secondName = secondName;
}
void Contact::SetBirthday(std::string birthday)
{
	this->birthday = birthday;
}
void Contact::SetPersonalPhotoUrl(std::string personalPhotoUrl)
{
	this->personalPhotoUrl = personalPhotoUrl;
}


