#include<memory>
#include<iostream>
#include <fstream>

#include "TrailAdminSession.hpp"
#include"Trails.hpp"


namespace TrailManagement
{
	std::vector<std::string> TrailAdminSession::getCommands()
	{
		return { "add Trail", "delete Trail","edit Trail" };
	}
	
	void TrailAdminSession::getCommandfunction(std::string & command)
	{
		if (command == "add Trail")
		{
			addTrail();
		}
		else if (command == "delete Trail")
		{
			deleteTrail();
		}
		else if (command == "edit Trail")
		{
			editTrail();
		}
		else
			std::cout << "invalid choice \n";



	}

	void TrailAdminSession::addTrail()// my problem
	{
		//Trailinfo db;
		

		std::fstream datafile;
		datafile.open("trailinfotext.txt", std::ios::app);
		struct Trailinfo storedtrails[100];

		if (datafile.is_open())
		{

			std::string trailname, difficulty, distance, steepness, info;
			std::cout << "enter trail name: ";
			std::cin >> trailname;
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].trailname;

			std::cout << "enter difficullty {easy, medium, high}: ";
			std::cin >> difficulty;
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].difficulty;

			std::cout << "enter distance: ";
			std::cin >> distance;
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].distance;

			std::cout << "enter steepness level {low, medium, high}: ";
			std::cin >>steepness;
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].steepness;

			std::cout << "enter any info about the trail: ";
			std::getline(std::cin, info);
			std::cout << std::endl;
			//tafile >> storedtrails[count].info;

			datafile << std::endl << trailname << " " << difficulty << " " << distance << " " << steepness << " " << info;
			
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}

	void TrailAdminSession::deleteTrail()
	{
		std::fstream datafile;
		datafile.open("trailinfotext.txt");
		int count = 0, choice;
		struct Trailinfo storedtrails[100];

		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				datafile >> storedtrails[count].trailname >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
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

			for (int i = 0; i < count; i++)
			{
				if (i != choice)
				{
					datafile << std::endl << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info;

				}
			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}

	void TrailAdminSession::editTrail()
	{

		std::fstream datafile;
		datafile.open("trailinfotext.txt");
		int count = 0, choice;
		struct Trailinfo storedtrails[100];
		std::string trailname, difficulty, distance, steepness, info;

		std::cout << "open\n";
		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				datafile >> storedtrails[count].trailname >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
			}

		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

		datafile.open("trailinfotext.txt", std::ios::out | std::ios::trunc);
		if (datafile.is_open())
		{
			std::cout << "Please select the trail you want to edit: ";
			std::cin >> choice;
			std::cout << std::endl;
			std::cout << "Enter 'N' if no change is needed.";


			std::string trailname, difficulty, distance, steepness, info;
			std::cout << "enter trail name: ";
			std::cin >> trailname;
			if (trailname != "N") { storedtrails[choice].trailname = trailname; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].trailname;

			std::cout << "enter difficullty {easy, medium, high}: ";
			std::cin >> difficulty;
			if (difficulty != "N") { storedtrails[choice].difficulty = difficulty; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].difficulty;

			std::cout << "enter distance: ";
			std::cin >> distance;
			if (distance != "N") { storedtrails[choice].distance = distance; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].distance;

			std::cout << "enter steepness level {low, medium, high}: ";
			std::cin >> steepness;
			if (steepness != "N") { storedtrails[choice].steepness = steepness; }
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].steepness;

			std::cout << "enter any info about the trail: ";
			std::getline(std::cin, info);
			if (info != "N") { storedtrails[choice].info = info; }
			std::cout << std::endl;
			//tafile >> storedtrails[count].info;

			for (int i = 0; i < count; i++)
			{

				datafile << std::endl << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info;

			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}
}
