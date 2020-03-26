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
		/*else if (command == "delete Trail")
		{

		}
		else if (command == "edit Trail")
		{

		}*/
		else
			std::cout << "invalid choice \n";



	}
	bool TrailAdminSession::addTrail()// my problem
	{
		//Trailinfo db;
		

		std::fstream datafile;
		datafile.open("trailinfotext.txt");
		int count = 0;
		struct Trailinfo storedtrails[100];
		if (datafile.is_open())
		{
			std::cout << "open\n";
			while (!datafile.eof())
			{
				datafile >> storedtrails[count].trailname >> storedtrails[count].difficulty >> storedtrails[count].distance >> storedtrails[count].steepness;
				std::getline(datafile, storedtrails[count].info);
				++count;
			}
			//count++;
			std::string trailname, difficulty, steepness, info;
			float distance;
			std::cout << "enter trail name\n";
			std::cin >> trailname;
			//tafile >> storedtrails[count].trailname;
			std::cout << "enter difficullty {easy, meduim, high}\n";
			std::cin >> difficulty;
			//tafile >> storedtrails[count].difficulty;
			std::cout << "enter distance\n";
			std::cin >> distance;
			//tafile >> storedtrails[count].distance;
			std::cout << "enter steepness level {low,medium,high}\n";
			std::cin >>steepness;
			//tafile >> storedtrails[count].steepness;
			std::cout << "enter any info about the trail\n";
			std::getline(std::cin, info);
				//tafile >> storedtrails[count].info;
			datafile <<trailname << " " << difficulty << " " << distance << " " << steepness << " " << info << "\n";
			
			for (int i = 0; i < count - 1; i++)
			{
				std::cout << i << " " << storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info << "\n";
			}
			
		}
		else
			throw Trails::NoSuchUser("did not open");

		datafile.close();

	}
}