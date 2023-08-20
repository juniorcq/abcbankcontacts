# abcbankcontacts
Developer Test

Project developed: BestVision Technical Test

Tools:   

0-Compiler  Tool                : Cake_minimum_required(VERSION 3.15)  
1-C++ compiler                  : gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0     
2-Portable C++ source libraries : boost_1_79_0 url: https://www.boost.org/       
3-C++ microframework for the web: crow_all.h   url: https://crowcpp.org/master/
4-Sqlite                        : Ssqlite3.h sqlite3.c    


Api url:


GETS DATA:

1- Get contacts:                         http://localhost:18080/contacts 
2- Get contacts by id:                   http://localhost:18080/contactbyid/<id> 
3- Get contact's phones by contact id:   http://localhost:18080/contactbyidphones/<id>
4- Get contact's address by contact id:  http://localhost:18080/contactaddressbycontactid/id
5- Get contacts in range of age:         http://localhost:18080//contactbyidrangeofage/age/age
6- Get contacts who lives in address_id: http://localhost:18080/contactslivesin/address_id
7- Get contact with address like:        http://localhost:18080/addreslike/firstname/addreslike  



INSERT DATA:

1- Insert address:                       http://localhost:18080/insertaddress/description
2- Add phone to contact:                 http://localhost:18080/addphonetocontact/contact_id/phone
3- Insert contact:                       http://localhost:18080/insertcontact/firstName,secondName,birthday,photoURL   
4- Add address to contact:               http://localhost:18080/addaddresstocontact/contact_id/address_id


UPDATE DATA:

1- Update contact:                       http://localhost:18080/updatecontact/contact_id/firstName/secondName/birthday/personalPhotoURL


DELETE DATA:                             

1-Delete contact by contact id           http://localhost:18080/deletecontact/id
2-Delete address from contact            http://localhost:18080/deleteaddressfromContact/contact_id/address_id
3-Delete phone from contact              http://localhost:18080/contact_id/phone_id