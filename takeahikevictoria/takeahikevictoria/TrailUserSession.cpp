#include<memory>
#include<iostream>
#include <fstream>
#include <vector>

#include "TrailUserSession.hpp"
#include "Trails.hpp"

namespace TrailManagement
{
	std::vector<std::string> TrailUserSession::getCommands()
	{
		return { "select trail(s)" };
	}

	void TrailUserSession::getCommandfunction(std::string & command)
	{
		if (command == "select trail(s)")
		{
			selectTrail();
		}
		else
			std::cout << "invalid choice \n";
	}

	Trailinfo TrailUserSession::selectCate(Trailinfo filterTrail)
	{
		int choice = 0;

		std::cout << "1: walking\n2: biking\n3: pet\n4: unfiltered" << std::endl;
		std::cout << "Enter choice: ";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1: filterTrail.category = "walking";
			break;
		case 2: filterTrail.category = "biking";
			break;
		case 3: filterTrail.category = "pet";
			break;
		case 4: filterTrail.category = "!";
			break;
		default:
			break;
		}

		return filterTrail;
	}

	Trailinfo TrailUserSession::selectAttr(Trailinfo filterTrail)
	{
		std::cout << "Please enter ! in each attribute you want unfiltered." << std::endl;

		std::cout << "enter difficullty {easy, medium, high}: ";
		std::cin >> filterTrail.difficulty;
		std::cin.ignore();
		std::cout << std::endl;

		std::cout << "enter distance: ";
		std::cin >> filterTrail.distance;
		std::cin.ignore();
		std::cout << std::endl;

		std::cout << "enter steepness level {low, medium, high}: ";
		std::cin >> filterTrail.steepness;
		std::cin.ignore();
		std::cout << std::endl;

		return filterTrail;
	}

	Trailinfo TrailUserSession::trailChoice(Trailinfo filterTrail)
	{
		std::fstream datafile;
		Trailinfo storedtrails[100], filteredtrails[100];
		int count = 0, countFiltered = 0, repeatCheck = 0, choice = 0;

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

		if (filterTrail.category == "!" && filterTrail.difficulty == "!" && filterTrail.distance == "!" && filterTrail.steepness == "!")
		{
			for (int i = 0; i < count; i++)
			{
				filteredtrails[i] = storedtrails[i];
			}
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				if (filterTrail.category != "!")
				{
					if (storedtrails[i].category == filterTrail.category)
					{
						filteredtrails[countFiltered++] = storedtrails[i];
					}
				}

				if (filterTrail.difficulty != "!")
				{
					if (storedtrails[i].difficulty == filterTrail.difficulty)
					{
						if (countFiltered > 0)
						{
							for (int j = 0; j < countFiltered; j++)
							{
								if (filteredtrails[j].trailname == storedtrails[i].trailname)
								{
									repeatCheck = 1;
								}
							}
						}

						if (repeatCheck != 1)
						{
							filteredtrails[countFiltered++] = storedtrails[i];
						}
					}
					repeatCheck = 0;
				}

				if (filterTrail.distance != "!")
				{
					if (storedtrails[i].distance == filterTrail.distance)
					{
						if (countFiltered > 0)
						{
							for (int j = 0; j < countFiltered; j++)
							{
								if (filteredtrails[j].trailname == storedtrails[i].trailname)
								{
									repeatCheck = 1;
								}
							}
						}

						if (repeatCheck != 1)
						{
							filteredtrails[countFiltered++] = storedtrails[i];
						}
					}
					repeatCheck = 0;
				}

				if (filterTrail.steepness != "!")
				{
					if (storedtrails[i].steepness == filterTrail.steepness)
					{
						if (countFiltered > 0)
						{
							for (int j = 0; j < countFiltered; j++)
							{
								if (filteredtrails[j].trailname == storedtrails[i].trailname)
								{
									repeatCheck = 1;
								}
							}
						}

						if (repeatCheck != 1)
						{
							filteredtrails[countFiltered++] = storedtrails[i];
						}
					}
					repeatCheck = 0;
				}
			}
		}

		for (int i = 0; i < countFiltered; i++)
		{
			std::cout << i << " " << filteredtrails[i].trailname << " " << filteredtrails[i].category << " " << filteredtrails[i].difficulty << " " << filteredtrails[i].distance << " " << filteredtrails[i].steepness << " " << filteredtrails[i].info << std::endl;
		}

		std::cout << "Please choose a trail: ";
		std::cin >> choice;
		std::cout << std::endl;

		return filteredtrails[choice];
	}

	void TrailUserSession::printTrail(std::vector<Trailinfo> chosentrails)
	{
		for (int i = 0; i < chosentrails.size(); i++)
		{
			std::cout << i << " " << chosentrails[i].trailname << " " << chosentrails[i].category << " " << chosentrails[i].difficulty << " " << chosentrails[i].distance << " " << chosentrails[i].steepness << " " << chosentrails[i].info << std::endl;
		}
	}

	void TrailUserSession::selectTrail()
	{
		std::fstream datafile;
		int count = 0, choice = 0;
		Trailinfo storedtrails[100], filterTrail;
		std::vector<Trailinfo> chosentrails;
		std::string trailname, difficulty, distance, steepness, info;

		filterTrail.category = "!";
		filterTrail.difficulty = "!";
		filterTrail.distance = "!";
		filterTrail.steepness = "!";

		while (choice != 5)
		{
			std::cout << "1: Select category\n2: Select attribute(s)\n3: Choose trail from filtered list\n4: Print trail(s)\n5: Quit" << std::endl;
			std::cout << "Enter choice: ";
			std::cin >> choice;
			std::cout << std::endl;

			switch (choice)
			{
			case 1: filterTrail = selectCate(filterTrail);
				break;
			case 2: filterTrail = selectAttr(filterTrail);
				break;
			case 3: chosentrails.push_back(trailChoice(filterTrail));
				break;
			case 4: printTrail(chosentrails);
				break;
			case 5:
				break;
			default: std::cout << "Please enter a value 1-5" << std::endl;
				break;
			}
		}
	}
}