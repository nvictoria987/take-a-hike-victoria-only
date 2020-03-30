#include <iostream>                                                                   // streamsize
#include <limits>                                                                     // numeric_limits
#include <memory>                                                                     // unique_ptr, make_unique<>()
#include <string>                                                                     // string, getline()
#include <vector>
#include <iomanip>

#include "useraccounts.hpp"                                  // Include for now - will replace next increment
#include "Trails.hpp"                                                   // Include for now - will replace next increment
#include "createSession.hpp"

#include "loggerHandler.hpp"
#include "simpleLogger.hpp" 
#include "firstDB.hpp"                                 // Include for now - will replace next increment
//#include "TechnicalServices/Persistence/SingletonDB.hpp"                              // Include for now - will replace next increment

#include "firstUI.hpp"

namespace UI
{
	// Default constructor
	SimpleUI::SimpleUI() : _accounts(std::make_unique<AccountManagement::UserAccounts>()),  //victoria- i cannot get this line to work // will replace these factory calls with abstract factory calls in the next increment
	  _TrailHandler(std::make_unique<TrailManagement::Trails>()),   // will replace these factory calls with abstract factory calls in the next increment
	  _loggerPtr(std::make_unique<Logging::SimpleLogger>()),   // will replace these factory calls with abstract factory calls in the next increment
	  _persistentData(Persistence::SimpleDB::instance()) {}    // will replace these factory calls with abstract factory calls in the next increment
	


	// Destructor
	SimpleUI::~SimpleUI() noexcept
	{
		_logger << "Simple UI shutdown successfully";
	}



	// Operations
	void SimpleUI::launch()
	{
		// 1) Fetch Role legal value list

		std::vector<std::string> roleLegalValues = _persistentData.findRoles();
		std::string selectedRole;

		// 2) Present login screen to user and get username, password, and valid role
		do
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::string userName;
			std::cout << "  name: ";
			std::getline(std::cin, userName);

			std::string passPhrase;
			std::cout << "  pass phrase: ";
			std::getline(std::cin, passPhrase);

			unsigned menuSelection;
			do
			{
				for (unsigned i = 0; i != roleLegalValues.size(); ++i)   std::cout << std::setw(2) << i << " - " << roleLegalValues[i] << '\n';
				std::cout << "  role (0-" << roleLegalValues.size() - 1 << "): ";
				std::cin >> menuSelection;
			} while (menuSelection >= roleLegalValues.size() + 1);

			selectedRole = roleLegalValues[menuSelection];


			// 3) Validate user is authorized for this role
			if (_accounts->isAuthenticated({ userName, passPhrase, {selectedRole} }))
			{
				//_logger << "Login Successful for \"" + userName + "\" as role \"" + selectedRole + "\"";
				_logger<< "Login Successful for \"" + userName + "\" as role \"" + selectedRole + "\"" ;
				break;
			}

			//std::cout << "** Login failed\n";
			_logger << "Login failure for \"" + userName + "\" as role \"" + selectedRole + "\"";

		} while (true);

		// 4) Fetch functionality options for this role
	    std::unique_ptr<TrailManagement::SessionHandler> sessionControl = TrailManagement::SessionHandler::createSession(selectedRole);

		std::vector<std::string> commands = sessionControl->getCommands();
		unsigned menuSelection;
		do
		{
			for (unsigned i = 0; i != commands.size(); ++i)   std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
			std::cout << "  role (0-" << commands.size() - 1 << "): ";
			std::cin >> menuSelection;
		} while (menuSelection >= roleLegalValues.size()+1);

		std::string selectedCommand = commands[menuSelection];
		_logger << "Selected command \"" + selectedCommand + "\" chosen";
		//std::cout<< "Selected command \"" + selectedCommand + "\" chosen \n";

		//TrailManagement::Trailinfo test = _TrailHandler->searchtrailDB();
		sessionControl->getCommandfunction(selectedCommand);
		
		
		
		system("pause");
	}

}
