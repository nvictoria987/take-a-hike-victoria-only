#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include<iostream>



#include "MaintainTrailHandler.hpp"
#include "Trails.hpp"

namespace TrailManagement
{
	Trailinfo Trails::displaytrailDB()
	{
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
				std::getline(datafile,storedtrails[count].info);
				++count;
			}
			for (int i= 0; i<count-1; i++)
			{
				std::cout <<i<<" "<< storedtrails[i].trailname << " " << storedtrails[i].difficulty << " " << storedtrails[i].distance << " " << storedtrails[i].steepness << " " << storedtrails[i].info <<"\n";
			}
			return storedtrails[100];
		}
		else
			throw Trails::NoSuchUser("did not open");
	
		datafile.close();

	}
}
