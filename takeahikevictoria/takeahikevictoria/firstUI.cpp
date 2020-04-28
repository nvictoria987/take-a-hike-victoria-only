#include <iostream>                                                                   // streamsize
#include <limits>                                                                     // numeric_limits
#include <memory>                                                                     // unique_ptr, make_unique<>()
#include <string>                                                                     // string, getline()
#include <vector>
#include <iomanip>

#include "useraccounts.hpp"                                  // Include for now - will replace next increment

#include "createSession.hpp"

#include "loggerHandler.hpp"
#include "simpleLogger.hpp" 
#include "firstDB.hpp"                                 // Include for now - will replace next increment

#include "firstUI.hpp"

namespace UI
{
	// Default constructor
	SimpleUI::SimpleUI() : _accounts(std::make_unique<AccountManagement::UserAccounts>()),  //victoria- i cannot get this line to work // will replace these factory calls with abstract factory calls in the next increment
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
				for (unsigned i = 0; i != roleLegalValues.size(); i++)   std::cout << std::setw(2) << i << " - " << roleLegalValues[i] << '\n';
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
		do
		{ 
			std::vector<std::string> commands = sessionControl->getCommands();
			std::string selectedCommand;
			unsigned menuSelection;
			
			do
			{
				for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
				//std::cout << std::setw(2) << commands.size() << " - " << "Quit\n";

				std::cout << "  action (0-" << commands.size() << "): ";
				std::cin >> menuSelection;
			} while (menuSelection > commands.size());

			//if (menuSelection == commands.size()) break;

			selectedCommand = commands[menuSelection];
			_logger << "Selected command \"" + selectedCommand + "\" chosen";
		
			if (selectedCommand== "Add Trail")
			{
				std::vector<std::string> parameters(6);

				std::cout << " enter trail name :   ";  std::cin >> std::ws;  std::getline(std::cin, parameters[0]);
				std::cout << " enter category {walking, biking, pet}:  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
				std::cout << " enter difficullty {easy, medium, high}:  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[2]);
				std::cout << " enter distance:  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[3]);
				std::cout << " enter steepness level {low, medium, high}:   ";  std::cin >> std::ws;  std::getline(std::cin, parameters[4]);
				std::cout << " enter any info about the trail:   ";  std::cin >> std::ws;  std::getline(std::cin, parameters[5]);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Print Database")
			{
				sessionControl->getCommandfunction(selectedCommand, {});
			}
			else if (selectedCommand == "Edit Trail")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Delete Trail")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Change Password")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Change Username")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Select Category")
			{
				std::vector<std::string> parameters(1);

				int choice = 0;

				std::cout << "1: walking\n2: biking\n3: pet\n4: unfiltered" << std::endl;
				std::cout << "Enter choice: ";
				std::cin >> choice;
				std::cout << std::endl;

				switch (choice)
				{
				case 1: parameters[0] = "walking";
					break;
				case 2: parameters[0] = "biking";
					break;
				case 3: parameters[0] = "pet";
					break;
				case 4: parameters[0] = "!";
					break;
				default:
					break;
				}

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Select Attribute(s)")
			{
				std::vector<std::string> parameters(3);

				std::cout << "Please enter ! in each attribute you want unfiltered." << std::endl;

				std::cout << "enter difficullty {easy, medium, high}: ";
				std::cin >> parameters[0];
				std::cin.ignore();
				std::cout << std::endl;

				std::cout << "enter distance: ";
				std::cin >> parameters[1];
				std::cin.ignore();
				std::cout << std::endl;

				std::cout << "enter steepness level {low, medium, high}: ";
				std::cin >> parameters[2];
				std::cin.ignore();
				std::cout << std::endl;

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Choose Trail")
			{
				std::vector<std::string> parameters(1);
				std::string init = "Filtered";

				sessionControl->getCommandfunction(init, parameters);

				std::cout << "Please choose a trail: ";
				std::cin >> parameters[0];
				std::cout << std::endl;

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "Print Chosen Trails")
			{
				sessionControl->getCommandfunction(selectedCommand, {});
			}
			else if (selectedCommand == "")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "")
			{
				std::vector<std::string> parameters(6);

				sessionControl->getCommandfunction(selectedCommand, parameters);
			}
			else if (selectedCommand == "")
			{

			}
			else if (selectedCommand == "")
			{

			}
			else if (selectedCommand == "")
			{

			}
			else if (selectedCommand == "")
			{

			}
			else if (selectedCommand == "Quit")
			{
				sessionControl->Signoff();
				break;
			}
			//then we would implement the other functions
			else 
			{
				_logger << "Invalid options";
			}

		
		} while (true);
		
		system("pause");
	}

}
