
#include <iostream>
#include<string>
#include "DBController.h"
#include "DBConnection.h"




DBController::DBController(std::string db_filename)
{
	conn = new DBConnection(db_filename);
}
DBController::~DBController()
{
	delete conn;
}
DBConnection* DBController::GetConnection()
{
	return conn;
}


///////////////////////////// CRUDS ///////////////////////////////////////////////////////////////

///////////CONTACT///////////////

/////////UTIL FUNCTIONS///////

int DBController::IsIntegerBiggerThanCero(std::string positiveNumber)
{
	for (int i = 0; i < strlen(positiveNumber.c_str()); i++)
	{
		if (!isdigit(positiveNumber[i]))return -1;
	}

	int converted = std::stoi(positiveNumber);

	return converted >0 ? converted : -1;

}
std::vector<Contact*>* DBController::RetrieveContacts(std::string sql)
{

	int connected = this->GetConnection()->Connect();
	sqlite3 *db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	std::vector<Contact*>* contactlist = new std::vector<Contact*>();
	Contact* contact;
	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			contact = new Contact();
			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					int id = std::atoi(valor.c_str());
					contact->SetId(id);
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "firstName") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						contact->SetFirstName(valor);
					}
					else
						if (strcmp(sqlite3_column_name(stmt, i), "secondName") == 0)
						{
							std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
							contact->SetSecondName(valor);
						}
						else
							if (strcmp(sqlite3_column_name(stmt, i), "birthday") == 0)
							{
								std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
								contact->SetBirthday(valor);
							}
							else
								if (strcmp(sqlite3_column_name(stmt, i), "personalPhoto") == 0)
								{

									std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
									contact->SetPersonalPhotoUrl(valor);
								}
			}

			// Getting all records as result of the SQL query excecution
			contactlist->push_back(contact);
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return contactlist;
}
std::vector<Phone*>* DBController::RetrievePhones(int contact_id)
{
	std::string id = std::to_string(contact_id);
	std::string  sql = "SELECT phone, Phone.id FROM 'Phone' INNER JOIN 'Contact' ON Phone.contact_id = Contact.id WHERE Contact.id = Phone.contact_id  AND Contact.id ='" + id + "'";
	int connected = this->GetConnection()->Connect();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	std::vector<Phone*>* list = new std::vector<Phone*>();
	Phone* phone;
	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			phone = new Phone();
			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					int id = std::atoi(valor.c_str());
					phone->SetId(id);
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "phone") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						phone->SetPhone(valor);
					}
			}

			// Getting all records as result of the SQL query excecution
			list->push_back(phone);
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return list;
}
std::vector<Address*>* DBController::RetrieveAddress(int contact_id)
{
	std::string id = std::to_string(contact_id);
	std::string  sql = "SELECT Address.description, Address.id FROM 'Contact' INNER JOIN 'ContactAddress' ON Contact.id = ContactAddress.contact_id INNER JOIN 'Address' ON ContactAddress.address_id = Address.id WHERE Contact.id = ContactAddress.contact_id AND Contact.id ='" + id + "'";
	int connected = this->GetConnection()->Connect();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	std::vector<Address*>* list = new std::vector<Address*>();
	Address* address;
	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			address = new Address();
			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					int id = std::atoi(valor.c_str());
					address->SetId(id);
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "description") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						address->SetAddress(valor);
					}
			}

			// Getting all records as result of the SQL query excecution
			list->push_back(address);
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return list;
}
std::vector<ContactAddressPivot*>* DBController::RetrieveContactAddresPivot(int contact_id)
{
	std::string id = std::to_string(contact_id);
	std::string sqlcontactaddress = "SELECT id, contact_id, address_id FROM 'ContactAddress' INNER JOIN 'Contact' ON ContactAddress.contact_id = Contact.id WHERE ContactAddress.contact_id ='" + std::to_string(contact_id) + "'";
	int connected = this->GetConnection()->Connect();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	std::vector<ContactAddressPivot*>* list = new std::vector<ContactAddressPivot*>(3);
	ContactAddressPivot* contactaddress;
	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sqlcontactaddress.c_str(), -1, &stmt, 0);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			contactaddress = new ContactAddressPivot;
			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					contactaddress->id = id;
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "contact_id") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						contactaddress->contact_id = valor;
					}
					else
						if (strcmp(sqlite3_column_name(stmt, i), "address_id") == 0)
						{
							std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
							contactaddress->address_id = valor;
						}
			}

			// Getting all records as result of the SQL query excecution
			list->push_back(contactaddress);
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return list;
}
int DBController::DeleteFromContactAddressPivot(int contact_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		//DELETE FROM ContactAddress WHERE ContactAddress.contact_id = 20
		std::string sqldelete = "DELETE FROM ContactAddress WHERE ContactAddress.contact_id = '" + std::to_string(contact_id) + "';";
		this->GetConnection()->Connect();
		sqlite3* db = this->GetConnection()->GetDatabase();

		rc = sqlite3_exec(db, sqldelete.c_str(), NULL, NULL, NULL);

		if (rc != SQLITE_OK)
			std::cerr << "Error DELETE" << std::endl;
		else {
			std::cout << "Operation OK!\n\n" << std::endl;

		}
		this->GetConnection()->Disconnect();
	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}
int DBController::DeleteFromContactAddressPivotWithAddressId(int contact_id, int address_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		//DELETE FROM ContactAddress WHERE ContactAddress.contact_id = 20
		std::string sqldelete = "DELETE FROM ContactAddress WHERE ContactAddress.contact_id = '" + std::to_string(contact_id) + "' AND ContactAddress.address_id = '" + std::to_string(address_id) + "';";

		this->GetConnection()->Connect();

		sqlite3* db = this->GetConnection()->GetDatabase();
		rc = sqlite3_exec(db, sqldelete.c_str(), NULL, NULL, NULL);

		if (rc != SQLITE_OK)
			std::cerr << "Error DELETE" << std::endl;
		else {
			std::cout << "Operation OK!\n\n" << std::endl;

		}
		this->GetConnection()->Disconnect();
	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}

int DBController::DeleteFromContact(int contact_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		std::string sqldelete = "DELETE FROM 'Contact' WHERE id = '" + std::to_string(contact_id) + "';";


		int connected = this->GetConnection()->Connect();

		sqlite3* db = this->GetConnection()->GetDatabase();
		rc = sqlite3_exec(db, sqldelete.c_str(), NULL, NULL, NULL);


		if (rc != SQLITE_OK)
			std::cerr << "Error DELETE" << std::endl;
		else {
			std::cout << "Operation OK!\n\n" << std::endl;

		}
		this->GetConnection()->Disconnect();

	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}

int DBController::DeleteFromAddress(int address_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		std::string sqldelete = "DELETE FROM 'Address' WHERE id = '" + std::to_string(address_id) + "';";


		this->GetConnection()->Connect();


		sqlite3* db = this->GetConnection()->GetDatabase();
		rc = sqlite3_exec(db, sqldelete.c_str(), NULL, NULL, NULL);


		if (rc != SQLITE_OK)
			std::cerr << "Error DELETE" << std::endl;
		else {
			std::cout << "Operation OK!\n\n" << std::endl;

		}
		this->GetConnection()->Disconnect();


	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}


//////////// GET CONTACTS //////////////////////////////

std::vector<Contact*>* DBController::GetContacts()
{
	std::string sql = "SELECT * FROM 'Contact' ";
	DBConnection* connection = GetConnection();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);

	return contactlist;
}
std::vector<Phone*>* DBController::GetContactPhones(int contact_id)
{
	DBConnection* connection = GetConnection();
	std::vector<Phone*>* list = RetrievePhones(contact_id);

	return list;
}
std::vector<Address*>* DBController::GetContactAddress(int contact_id)
{
	DBConnection* connection = GetConnection();
	std::vector<Address*>* list = RetrieveAddress(contact_id);
	return list;
}
std::vector<Contact*>* DBController::GetContactWithName(std::string firstName) {

	std::string sql = "SELECT * FROM 'Contact' WHERE firstName='" + firstName + "'";
	DBConnection *connection = GetConnection();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);

	return contactlist;
}
Contact* DBController::GetContactWithId(int id) {

	std::string sql = "SELECT * FROM 'Contact' WHERE id='" + std::to_string(id) + "'";
	DBConnection *connection = GetConnection();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);


	if (contactlist->size() > 0)
	{

		return contactlist->at(0);
	}
	return NULL;


}
std::vector<Contact*>* DBController::GetContactWithFullName(std::string firstName, std::string secondName)
{

	std::string sql = "SELECT * FROM 'Contact' WHERE firstName = '" + firstName + "'" + " AND " + "secondName='" + secondName + "'";
	DBConnection *connection = GetConnection();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);

	return contactlist;

}
std::vector<Contact*>* DBController::GetContactWithAgeInRange(int from, int to)
{
	if (from <0)from *= -1;
	if (to <0)from *= -1;

	if (from>to)
	{
		int temp = from;
		from = to;
		to = temp;
	}

	std::string sql = "SELECT id, firstName, secondName, CAST((DATE('now') - DATE(birthday))As Integer) AS age, DATE('now') AS today, birthday, personalPhoto FROM 'Contact' WHERE age BETWEEN '" + std::to_string(from) + "' AND '" + std::to_string(to) + "'";
	DBConnection *connection = GetConnection();
	sqlite3 *db = connection->GetDatabase();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);

	return contactlist;
}

std::vector<AddresLike*>* DBController::GetContactWithAddressLike(std::string firstname, std::string addresslike)
{
	std::string sql = "SELECT Contact.firstName, Contact.secondName, Address.description, Contact.id AS contact_id, Contact.birthday, Contact.personalPhoto, ContactAddress.address_id AS addres_id FROM 'Contact' INNER JOIN 'ContactAddress' ON Contact.id = ContactAddress.contact_id INNER JOIN 'Address' ON  ContactAddress.address_id = Address.id WHERE Address.description LIKE '%" + addresslike + "%' AND Contact.firstName = '" + firstname + "';";

	std::vector<AddresLike*>* list = new std::vector<AddresLike*>();
	this->GetConnection()->Connect();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;

	AddresLike* addreslike;
	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);


		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			addreslike = new AddresLike;

			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "contact_id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					addreslike->contact_id = valor;
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "firstName") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						addreslike->firstName = valor;
					}
					else
						if (strcmp(sqlite3_column_name(stmt, i), "secondName") == 0)
						{
							std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
							addreslike->secondName = valor;
						}
						else
							if (strcmp(sqlite3_column_name(stmt, i), "birthday") == 0)
							{
								std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
								addreslike->birthday = valor;
							}
							else
								if (strcmp(sqlite3_column_name(stmt, i), "personalPhoto") == 0)
								{
									std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
									addreslike->photo = valor;
								}
								else
									if (strcmp(sqlite3_column_name(stmt, i), "addres_id") == 0)
									{
										std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
										addreslike->address_id = valor;
									}
									else
										if (strcmp(sqlite3_column_name(stmt, i), "description") == 0)
										{
											std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
											addreslike->address_description = valor;
										}
			}

			list->push_back(addreslike);
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}

	return list;
}
std::vector<Contact*>* DBController::GetContactsWhoLiveIn(int address_id)
{
	std::string sql = "SELECT * FROM 'Contact' INNER JOIN ContactAddress ON Contact.id = ContactAddress.contact_id INNER JOIN 'Address' ON ContactAddress.address_id = Address.id WHERE Address.id='" + std::to_string(address_id) + "'";
	DBConnection* connection = GetConnection();
	sqlite3* db = connection->GetDatabase();
	std::vector<Contact*>* contactlist = RetrieveContacts(sql);

	return contactlist;
}

//////////////// GET PHONE////////////////////////
Phone* DBController::GetPhoneWithId(int id) {

	std::string sql = "SELECT * FROM 'Phone' WHERE id='" + std::to_string(id) + "'";
	DBConnection* connection = GetConnection();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	Phone* phone = NULL;

	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		if (rc == SQLITE_OK)
		{
			phone = new Phone();
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				int nCols = sqlite3_column_count(stmt);

				// Getting the current record of the given SQL query statement
				for (int i = 0; i < nCols; i++)
				{
					if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						int id = std::atoi(valor.c_str());
						phone->SetId(id);
					}
					else
						if (strcmp(sqlite3_column_name(stmt, i), "phone") == 0)
						{
							std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
							phone->SetPhone(valor);
						}

				}

			}
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return phone;




}
Phone* DBController::GetPhone(std::string phone) {

	std::string sql = "SELECT * FROM 'Phone' WHERE phone='" + phone + "'";
	DBConnection* connection = GetConnection();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;
	Phone* ph = NULL;

	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		if (rc == SQLITE_OK)
		{
			ph = new Phone();
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				int nCols = sqlite3_column_count(stmt);

				// Getting the current record of the given SQL query statement
				for (int i = 0; i < nCols; i++)
				{
					if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						int id = std::atoi(valor.c_str());
						ph->SetId(id);
					}
					else
						if (strcmp(sqlite3_column_name(stmt, i), "phone") == 0)
						{
							std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
							ph->SetPhone(valor);
						}

				}

			}
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return ph;




}



////////////////GET ADDRESS /////////////////////
Address* DBController::GetAddressWithId(int id) {

	std::string sql = "SELECT * FROM 'Address' WHERE id='" + std::to_string(id) + "'";
	DBConnection* connection = GetConnection();
	Address* address = NULL;

	this->GetConnection()->Connect();
	sqlite3* db = this->GetConnection()->GetDatabase();
	int rc = SQLITE_EMPTY;


	try
	{
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int nCols = sqlite3_column_count(stmt);

			address = new Address();
			// Getting the current record of the given SQL query statement
			for (int i = 0; i < nCols; i++)
			{
				if (strcmp(sqlite3_column_name(stmt, i), "id") == 0)
				{
					std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
					int id = std::atoi(valor.c_str());
					address->SetId(id);
				}
				else
					if (strcmp(sqlite3_column_name(stmt, i), "description") == 0)
					{
						std::string valor = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i));
						address->SetAddress(valor);
					}
			}
		}
		sqlite3_finalize(stmt);
		this->GetConnection()->Disconnect();
	}
	catch (const std::exception&)
	{
		rc = SQLITE_ERROR;
	}
	return address;

}

//////////// DELETE //////////////////////////////
int DBController::DeleteContactById(int contact_id)
{

	int rc = SQLITE_EMPTY;

	try
	{
		Contact* contact = GetContactWithId(contact_id);

		if (contact)
		{
			std::vector<ContactAddressPivot*>* contactaddress = RetrieveContactAddresPivot(contact->GetId());

			if (contactaddress->size() > 0)
			{
				rc = DeleteFromContactAddressPivot(contact_id);

				if (rc != SQLITE_OK)
				{
					return rc;
				}
			}
			rc = DeleteFromContact(contact_id);
		}
	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;


}
int DBController::DeleteAddressFromContact(int contact_id, int addres_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		Contact* contact = GetContactWithId(contact_id);

		if (contact)
		{
			std::vector<ContactAddressPivot*>* contactaddress = RetrieveContactAddresPivot(contact->GetId());

			if (contactaddress->size() > 0)
			{
				rc = DeleteFromContactAddressPivotWithAddressId(contact_id, addres_id);

				if (rc != SQLITE_OK)
				{
					return rc;
				}
			}

		}
	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}
int  DBController::DeletePhoneFromContact(int contact_id, int phone_id)
{
	int rc = SQLITE_EMPTY;

	try
	{
		Contact* contact = GetContactWithId(contact_id);

		if (contact)
		{
			//DELETE FROM Phone from contact
			std::string sqldelete = "DELETE FROM Phone WHERE Phone.contact_id = '" + std::to_string(contact_id) + "' AND Phone.id = '" + std::to_string(phone_id) + "'; ";

			this->GetConnection()->Connect();
			sqlite3* db = this->GetConnection()->GetDatabase();
			rc = sqlite3_exec(db, sqldelete.c_str(), NULL, NULL, NULL);

			if (rc != SQLITE_OK)
				std::cerr << "Error DELETE" << std::endl;
			else
			{
				std::cout << "Operation OK!\n\n" << std::endl;
			}
			this->GetConnection()->Disconnect();
		}
	}
	catch (...)
	{
		rc = SQLITE_ERROR;
	}

	return rc;
}

//INSERT
int DBController::InsertContact(std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL)
{

	std::string sql = "INSERT INTO 'Contact'(firstName, secondName, birthday, personalPhoto) VALUES ('" + firstName + "', '" + secondName + "', '" + birthday + "', '" + personalPhotoURL + "');";

	GetConnection()->Connect();

	sqlite3 *db = GetConnection()->GetDatabase();
	int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);


	if (rc != SQLITE_OK)
		std::cerr << "Error INSERTING" << std::endl;
	else
	{
		std::cout << "Operation OK!\n\n" << std::endl;
	}
	GetConnection()->Disconnect();

	return rc;

}
int DBController::AddAddressToContact(int contact_id, int address_id)
{
	Contact* contact = GetContactWithId(contact_id);

	int rc = SQLITE_EMPTY;
	if (contact)
	{
		Address* address = GetAddressWithId(address_id);

		if (address != NULL)
		{
			std::vector<Address*>* contactaddress = GetContactAddress(contact_id);
			int pos = -1;
			for (int i = 0; i < contactaddress->size(); i++)
			{
				if (contactaddress->at(i)->GetId() == address->GetId())
				{
					pos = i;
					break;
				}
			}
			if (pos < 0)
			{
				std::string sql = "INSERT INTO 'ContactAddress' (contact_id,address_id) VALUES('" + std::to_string(contact_id) + "'," + "'" + std::to_string(address_id) + "');";

				GetConnection()->Connect();

				sqlite3* db = GetConnection()->GetDatabase();
				rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);


				if (rc != SQLITE_OK)
				{
					std::cerr << "Error INSERTING" << std::endl;
					GetConnection()->Disconnect();
				}
				else
				{
					GetConnection()->Disconnect();
					return rc;
				}
			}
			else
			{
				rc = SQLITE_EMPTY;
			}
		}

	}

	return rc;
}
int DBController::InsertAddress(std::string description)
{

	std::string sql = "INSERT INTO 'Address' (description) VALUES('" + description + "');";

	GetConnection()->Connect();

	sqlite3* db = GetConnection()->GetDatabase();
	int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);


	if (rc != SQLITE_OK)
		std::cerr << "Error INSERTING" << std::endl;
	else {
		std::cout << "Operation OK!\n\n" << std::endl;

	}
	GetConnection()->Disconnect();

	return rc;
}
int DBController::AddPhoneToContact(int contact_id, std::string phone)
{
	Contact* contact = GetContactWithId(contact_id);

	int rc = SQLITE_EMPTY;
	if (contact)
	{
		std::vector<Phone*>* phonelist = GetContactPhones(contact_id);

		int pos = -1;

		for (int i = 0; i < phonelist->size(); i++)
		{
			if (strcmp(phonelist->at(i)->GetPhone().c_str(), phone.c_str()) == 0)
			{
				pos = i;
				break;
			}
		}

		if (pos < 0)
		{
			std::string sql = "INSERT INTO 'Phone' (phone,contact_id) VALUES('" + phone + "'," + "'" + std::to_string(contact_id) + "');";

			GetConnection()->Connect();

			sqlite3* db = GetConnection()->GetDatabase();
			rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);


			if (rc != SQLITE_OK)
				std::cerr << "Error INSERTING" << std::endl;
			else
			{

				return rc;

				GetConnection()->Disconnect();
			}

		}

	}

	return rc;



}


//UPDATE CONTACTS
int  DBController::UpdateContact(int contact_id, std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL)
{
	std::string sql = "UPDATE 'Contact' SET 'firstName' = '" + firstName + "', 'secondName' = '" + secondName + "' , 'birthday' = '" + birthday + "','personalPhoto' = '" + personalPhotoURL + "' WHERE id ='" + std::to_string(contact_id) + "';";
	GetConnection()->Connect();

	sqlite3 *db = GetConnection()->GetDatabase();
	int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

	if (rc != SQLITE_OK)
		std::cerr << "Error UPDATING" << std::endl;
	else {
		std::cout << "Operation OK!\n\n" << std::endl;

	}
	GetConnection()->Disconnect();

	return rc;
}
