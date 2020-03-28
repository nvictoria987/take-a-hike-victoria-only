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
		int count = 0;
		struct Trailinfo storedtrails[100];
		std::string trailname, difficulty, distance, steepness, info;

		datafile.open("trailinfotext.txt");
		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count - 1; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
			}
			--count;

		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

		datafile.open("trailinfotext.txt", std::ios::app);
		if (datafile.is_open())
		{
			std::cout << "enter trail name: ";
			std::cin.ignore();
			std::getline(std::cin, trailname);
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
			std::cin >> steepness;
			std::cin.ignore();
			std::cout << std::endl;
			//tafile >> storedtrails[count].steepness;

			std::cout << "enter any info about the trail: ";
			std::getline(std::cin, info);
			std::cout << std::endl;
			//tafile >> storedtrails[count].info;

			datafile << trailname << std::endl << difficulty << " " << distance << " " << steepness << " " << info << std::endl;
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
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count - 1; i++)
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

			for (int i = 0; i < count - 1; i++)
			{
				if (i != choice)
				{
					datafile << storedtrails[i].trailname << std::endl << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << std::endl;

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

		if (datafile.is_open())
		{
			while (!datafile.eof())
			{
				std::getline(datafile >> std::ws, storedtrails[count].trailname);
				datafile >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile >> std::ws, storedtrails[count].info);
				++count;
			}

			for (int i = 0; i < count - 1; i++)
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
			std::cout << "Enter 'N/n' if no change is needed for that attribute." << std::endl;

			std::string trailname, difficulty, distance, steepness, info;
			std::cout << "enter trail name: ";
			std::cin.ignore();
			std::getline(std::cin, trailname);
			if (trailname != "N" || trailname != "n") { storedtrails[choice].trailname = trailname; }
			std::cout << std::endl;
			//tafile >> storedtrails[count].trailname;

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

				datafile << storedtrails[i].trailname << std::endl << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << std::endl;

			}
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}
}
