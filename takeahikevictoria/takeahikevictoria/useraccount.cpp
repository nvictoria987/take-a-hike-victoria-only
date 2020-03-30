#include <algorithm>    // std::any_of()
#include <memory>       // make_unique<>()
#include<fstream>
#include<iostream>

#include "useraccounts.hpp"

//#include "TechnicalServices/Logging/SimpleLogger.hpp"
//#include "TechnicalServices/Persistence/SingletonDB.hpp"
#include "firstDB.hpp"

namespace AccountManagement
{
	// Default constructor
	UserAccounts::UserAccounts() : _persistentData(Persistence::SimpleDB::instance())        // will replace hard coded implementation class next increment
			//_loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())    // will replace hard coded implementation class next increment
	{
		//_logger << "UserAccounts being used and has been successfully initialized";
	}


	// Destructor
	UserAccounts::~UserAccounts() noexcept
	{
		//_logger << "UserAccounts shutdown successfully";
	}



	// Operations
	bool UserAccounts::isAuthenticated(const UserCredentials & credentials)
	{
		std::fstream datafile;
		datafile.open("loggeduser.txt", std::ios::out | std::ios::trunc);
		if (datafile.is_open())
		{
			datafile << credentials.userName << " " << credentials.passPhrase << " " << credentials.roles[0];
		}
		datafile.close();

		try
		{
			UserCredentials credentialsFromDB = _persistentData.findCredentialsByName(credentials.userName);

			// std::set_intersection might be a better choice, but here I'm assuming there will be one and only one role in the passed-in
			// credentials I just need to verify the requested role is in the set of authorized roles.  Someday, if a user can sign in
			// with many roles combined, I may have to revisit this approach.  But for now, this is good enough.
			if (credentials.userName == credentialsFromDB.userName
				&& credentials.passPhrase == credentialsFromDB.passPhrase
				&& std::any_of(credentialsFromDB.roles.cbegin(), credentialsFromDB.roles.cend(),
					[&](const std::string & role) { return credentials.roles.size() > 0 && credentials.roles[0] == role; }
				)
				) return true;
		}
		catch (const Persistence::PersistenceHandler::NoSuchUser &) {}  // Catch and ignore this anticipated condition

		return false;
	}

	/*
	void UserAccounts::editPassword()
	{
		_persistentData;
		std::string newpassword,oldpassword;
		char roles;

		std::fstream datafile;
		datafile.open("useraccountinfo.txt");
		int count = 0, choice;
		struct UserCredentials storedUsers[100];
		if (datafile.is_open())
		{
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
				default: throw Persistence::PersistenceHandler::NoSuchUser("user account error");
					break;
				}

				++count;
			}
			for (int i = 0; i< count-1; i++)
			{
				if (temp.userName == storedUsers[count].userName)
				{
					std::cout << "enter password: ";
					std::cin >> oldpassword;
					if (oldpassword == storedUsers[count].passPhrase)
					{
						std::cout << "enter new password: ";
						std::cin >> newpassword;
						storedUsers[count].passPhrase = newpassword;

					}
				}
			}

			for (int i = 0; i < count - 1; i++)
			{
				std::cout << i << " " << storedUsers[i].userName << " " << storedUsers[i].passPhrase << " " << storedUsers[i].roles[0] << std::endl;
			}

		}
		else
			throw Persistence::PersistenceHandler::NoSuchUser("did not open");

		datafile.close();


	}
	*/
} // namespace Domain::AccountManagement
