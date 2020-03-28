#include <string>
#include <vector>
#include <memory>     // make_unique()
#include<fstream>
#include<iostream>

#include "firstDB.hpp"
//#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "PersistenceHandler.hpp"


namespace Persistence
{
	SimpleDB::SimpleDB()
		//: _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())     // will replace these factory calls with abstract factory calls next increment
	{
		//_logger << "Simple DB being used and has been successfully initialized";
	}

	SimpleDB & SimpleDB::instance()
	{
		static SimpleDB theInstance;
		return theInstance;
	}

	SimpleDB::~SimpleDB() noexcept
	{
		//_logger << "Simple DB shutdown successfully";
	}



	std::vector<std::string> SimpleDB::findRoles()
	{
		return { "TrailAdmin", "TrailUser" };
	}

	UserCredentials SimpleDB::findCredentialsByName(const std::string & name)
	{
		
		std::fstream datafile;
		datafile.open("useraccountinfo.txt");
		int count = 0;
		char roles;
		struct UserCredentials storedUsers[100];
		//static std::vector<UserCredentials> storedUsers;
		if (datafile.is_open())
		{
			std::cout << "open\n";
			while (!datafile.eof())
			{
				datafile >> storedUsers[count].userName >> storedUsers[count].passPhrase >> roles;
				switch (roles)
				{
					case '0': storedUsers[count].roles = { "TrailAdmin" };
							  break;
					case '1': storedUsers[count].roles = { "TrailUser" };
							  break;
					case '2': storedUsers[count].roles = { "TrailAdmin", "TrailUser" };
						  break;
					default: throw PersistenceHandler::NoSuchUser("user account error");
						break;
				}

				++count;
			}
		
			//return storedUsers;
		}
		else
			throw PersistenceHandler::NoSuchUser("did not open");

		//datafile.close();
		
		//static std::vector<UserCredentials> storedUsers =
		//{
		//	// userName    Pass Phrase         Authorized roles
		//	  {"victoria",     "please work",  {"TrailUser","TrailAdmin"}},
		//	  {"eric", "password123",   {"TrailAdmim" }},
		//	  {"chase",  "123",                 {"TrailUser" }}
		//};

		//for (const auto & user : storedUsers) if (user.userName == name) return { user.userName, user.passPhrase, user.roles };
		
		for (int i = 0; i < count - 1; i++)
		{
			if (name == storedUsers[i].userName)
			{
				return { storedUsers[i].userName, storedUsers[i].passPhrase, storedUsers[i].roles };
			}
			 
		}
		datafile.close();
		// Name not found, throw something
		std::string message = __func__;
		message += " attempt to find user \"" + name + "\" failed";

		//	_logger << message;

		throw PersistenceHandler::NoSuchUser(message);
	}

} // namespace TechnicalServices::Persistence