#include <memory>
#include <iostream>
#include <fstream>
#include <any>

#include "TrailAdminSession.hpp"
#include "Trails.hpp"
#include "PersistenceHandler.hpp"
//#include "useraccounts.hpp"

struct TempCredentials
{
	std::string             userName;
	std::string             passPhrase;
	std::string				roles;
};

namespace TrailManagement
{
	std::vector<std::string> TrailAdminSession::getCommands()
	{
		return { "Add Trail","Delete Trail" ,"Edit Trail", "Print Database", "Change Password", "Change Username" };
		//edit Password"
	}
	
	std::any TrailAdminSession::getCommandfunction(std::string & command, const std::vector<std::string> & args)
	{

		if (command == "Add Trail ")
		{
			addTrail(args);
		}
		else if (command == "Delete Trail")
		{
			deleteTrail(args);
		}
		else if (command == "Edit Trail")
		{
			editTrail(args);
		}
		else if (command == "Print Database")
		{
			printTrail(args);
		}
		else if (command == "Change Password")
		{
			
		}
		else if (command == "Change Username")
		{

		}
		else
			return 0;
			//std::cout << "invalid choice \n"; 

	}

	void TrailAdminSession::addTrail(const std::vector<std::string> & args)
	{
		//Trailinfo db;
		
		std::fstream datafile;
		std::string trailname, category, difficulty, distance, steepness, info;
		trailname = args[0];
		category = args[1];
		difficulty = args[2];
		distance = args[3];
		steepness = args[4];
		info = args[5];

		datafile.open("trailinfotext.txt", std::ios::app);
		if (datafile.is_open())
		{
			//std::cout << "enter trail name: ";
			//std::cin.ignore();
			//std::getline(std::cin, trailname);
			//std::cout << std::endl;
			////tafile >> storedtrails[count].trailname;

			//std::cout << "enter category {walking, biking, pet}: ";
			//std::cin >> category;
			//std::cin.ignore();
			//std::cout << std::endl;
			////tafile >> storedtrails[count].category;

			//std::cout << "enter difficullty {easy, medium, high}: ";
			//std::cin >> difficulty;
			//std::cin.ignore();
			//std::cout << std::endl;
			////tafile >> storedtrails[count].difficulty;

			//std::cout << "enter distance: ";
			//std::cin >> distance;
			//std::cin.ignore();
			//std::cout << std::endl;
			////tafile >> storedtrails[count].distance;

			//std::cout << "enter steepness level {low, medium, high}: ";
			//std::cin >> steepness;
			//std::cin.ignore();
			//std::cout << std::endl;
			////tafile >> storedtrails[count].steepness;

			//std::cout << "enter any info about the trail: ";
			//std::getline(std::cin, info);
			//std::cout << std::endl;
			////tafile >> storedtrails[count].info;

			datafile << trailname << std::endl << category << " " << difficulty << " " << distance << " " << steepness << " " << info << std::endl;
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}

	void TrailAdminSession::deleteTrail(const std::vector<std::string> & args)
	{
		std::fstream datafile;
		datafile.open("trailinfotext.txt");
		int count = 0, choice;
		struct Trailinfo storedtrails[100];

		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].category >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count - 1; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].category << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
			}

		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

		datafile.open("trailinfotext.txt", std::ios::out | std::ios::trunc);
		if (datafile.is_open())
		{
			std::cout << "Please select the trail you want deleted: ";
			std::cin >> choice;
			std::cout << std::endl;

			for (int i = 0; i < count - 1; i++)
			{
				if (i != choice)
				{
					datafile << storedtrails[i].trailname << std::endl << storedtrails[i].category << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << std::endl;

				}
			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}

	void TrailAdminSession::editTrail(const std::vector<std::string> & args)
	{

		std::fstream datafile;
		datafile.open("trailinfotext.txt");
		int count = 0, choice;
		struct Trailinfo storedtrails[100];
		std::string trailname, category, difficulty, distance, steepness, info;

		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].category >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count - 1; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].category << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
			}

		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.open("trailinfotext.txt", std::ios::out | std::ios::trunc);
		if (datafile.is_open())
		{
			std::cout << "Please select the trail you want to edit: ";
			std::cin >> choice;
			std::cout << std::endl;
			std::cout << "Enter 'N/n' if no change is needed for that attribute." << std::endl;

			std::string trailname, difficulty, distance, steepness, info;
			std::cout << "enter trail name: ";
			std::cin.ignore();
			std::getline(std::cin, trailname);
			if (trailname != "N" || trailname != "n") { storedtrails[choice].trailname = trailname; }
			std::cout << std::endl;
			//tafile >> storedtrails[count].trailname;

			std::cout << "enter category {walking, biking, pet}: ";
			std::cin >> category;
			if (trailname != "N" || trailname != "n") { storedtrails[choice].category = category; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].category;

			std::cout << "enter difficullty {easy, medium, high}: ";
			std::cin >> difficulty;
			if (difficulty != "N" || difficulty != "n") { storedtrails[choice].difficulty = difficulty; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].difficulty;

			std::cout << "enter distance: ";
			std::cin >> distance;
			if (distance != "N " || distance != "n") { storedtrails[choice].distance = distance; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].distance;

			std::cout << "enter steepness level {low, medium, high}: ";
			std::cin >> steepness;
			if (steepness != "N" || steepness != "n") { storedtrails[choice].steepness = steepness; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].steepness;

			std::cout << "enter any info about the trail: ";
			std::getline(std::cin, info);
			if (info != "N" || info != "n") { storedtrails[choice].info = info; }
			std::cout << std::endl;
			//tafile >> storedtrails[count].info;

			for (int i = 0; i < count - 1; i++)
			{

				datafile << storedtrails[i].trailname << std::endl << storedtrails[i].category << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << std::endl;

			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}

	void TrailAdminSession::printTrail(const std::vector<std::string> & args)
	{
		int count = 0;
		struct Trailinfo storedtrails[100];
		std::fstream datafile;

		datafile.open("trailinfotext.txt");
		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].category >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

		for (int i = 0; i < count - 1; i++)
		{
			std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].category << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
		}
	}

	void TrailAdminSession::manageAccount()
	{
		std::string newpassword, oldpassword;
		std::fstream datafile;
		int count = 0, choice = 0;
		struct TempCredentials storedUsers[100], temp;

		datafile.open("loggeduser.txt");
		if (datafile.is_open())
		{
			datafile >> temp.userName >> temp.passPhrase;
		}
		else
			throw Persistence::PersistenceHandler::NoSuchUser("did not open");

		datafile.close();


		datafile.open("useraccountinfo.txt");
		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				datafile >> storedUsers[count].userName >> storedUsers[count].passPhrase >> storedUsers[count].roles;
				/*
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
				*/
				++count;
			}

			while (choice != 3)
			{
				std::cout << "1: Change Password\n2: Change Username\n3: Quit" << std::endl;
				std::cout << "Enter choice: ";
				std::cin >> choice;
				std::cout << std::endl;

				if (choice == 1)
				{
					for (int i = 0; i < count; i++)
					{
						if (temp.userName == storedUsers[i].userName)
						{
							std::cout << "enter password: ";
							std::cin >> oldpassword;
							if (oldpassword == storedUsers[i].passPhrase)
							{
								std::cout << "enter new password: ";
								std::cin >> newpassword;
								storedUsers[i].passPhrase = newpassword;
							}
						}
					}
				}
				else if (choice == 2)
				{
					for (int i = 0; i < count; i++)
					{
						if (temp.userName == storedUsers[i].userName)
						{
							std::cout << "enter password: ";
							std::cin >> oldpassword;
							if (oldpassword == storedUsers[i].passPhrase)
							{
								std::cout << "enter new username: ";
								std::cin >> newpassword;
								storedUsers[i].userName = newpassword;

							}
						}
					}
				}
				else if (choice == 3)
				{
					break;
				}
				else
				{
					std::cout << "Please enter a valid choice." << std::endl;
				}
			}
		}
		else
			throw Persistence::PersistenceHandler::NoSuchUser("did not open");

		datafile.close();

		datafile.open("useraccountinfo.txt", std::ios::out | std::ios::trunc);
		if (datafile.is_open())
		{
			for (int i = 0; i < count; i++)
			{
				datafile << storedUsers[i].userName << " " << storedUsers[i].passPhrase << " " << storedUsers[i].roles << std::endl;
			}
		}
		else
			throw Persistence::PersistenceHandler::NoSuchUser("did not open");

		datafile.close();
	}

	
}
