
#ifndef ABCBANKCONTACT_DBCONTROLLER_H
#define ABCBANKCONTACT_DBCONTROLLER_H

#include "DBConnection.h"
#include "Contact.h"


typedef struct ContactAddress
{
	std::string id;
	std::string contact_id;
	std::string address_id;
}ContactAddressPivot;

typedef struct FirstNameAddresLike
{
	std::string contact_id;
	std::string firstName;
	std::string secondName;
	std::string birthday;
	std::string photo;
	std::string address_id;
	std::string address_description;

}AddresLike;


class DBController {

private:
	DBConnection* conn;

protected:
	std::vector<Contact*>* RetrieveContacts(std::string sql);
	std::vector<Phone*>* RetrievePhones(int contact_id);
	std::vector<Address*>* RetrieveAddress(int contact_id);
	std::vector<ContactAddressPivot*>* RetrieveContactAddresPivot(int contact_id);
	int DeleteFromContactAddressPivot(int contact_id);
	int DeleteFromContactAddressPivotWithAddressId(int contact_id, int address_id);
	DBConnection* GetConnection();
	int DeleteFromContact(int contact_id);
	int DeleteFromAddress(int address_id);



public:
	DBController(std::string db_filename);
	~DBController();


	//CRUD CONTACTS
	//SELECT CONTACTS

	Contact* GetContactWithId(int id);
	std::vector<Contact*>* GetContacts();
	std::vector<Phone*>* GetContactPhones(int contact_id);
	std::vector<Address*>* GetContactAddress(int contact_id);
	std::vector<Contact*>* GetContactWithName(std::string firstName);
	std::vector<Contact*>* GetContactWithFullName(std::string firstName, std::string secondName);
	std::vector<Contact*>* GetContactWithAgeInRange(int from, int to);
	std::vector<AddresLike*>* GetContactWithAddressLike(std::string firstname, std::string addresslike);
	std::vector<Contact*>* GetContactsWhoLiveIn(int address_id);
	Phone* GetPhoneWithId(int id);
	Phone* GetPhone(std::string phone);
	Address* GetAddressWithId(int id);

	//DELETE CONTACTS
	int DeleteContactById(int id);
	int DeleteAddressFromContact(int contact_id, int contact_addres_id);
	int DeletePhoneFromContact(int contact_id, int phone_id);

	//INSERT
	int InsertAddress(std::string description);
	int InsertContact(std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL);
	int AddPhoneToContact(int contact_id, std::string phone);
	int AddAddressToContact(int contact_id, int address_id);



	//UPDATE CONTACTS
	int UpdateContact(int contact_id, std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL);



	//Utils
	int IsIntegerBiggerThanCero(std::string positiveNumber);



};


#endif //ABCBANKCONTACT_DBCONTROLLER_H
