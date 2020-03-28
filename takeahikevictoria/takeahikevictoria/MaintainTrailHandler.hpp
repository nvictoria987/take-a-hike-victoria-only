#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace TrailManagement
{
	struct Trailinfo
	{
		std::string             trailname;
		std::string		category;
		std::string             difficulty;
		std::string             distance;
		std::string           	steepness;
		std::string             info;

	};
	// Library Package within the Domain Layer Abstract class
	class MaintainTrailHandler
	{
	public:
		//exceptions
		struct NoSuchUser : std::domain_error { using domain_error::domain_error; };

		// Constructors
		MaintainTrailHandler() = default;        // default ctor
		MaintainTrailHandler(const MaintainTrailHandler &  original) = default;        // copy ctor
		MaintainTrailHandler(MaintainTrailHandler && original) = default;        // move ctor
		
		// Operations
		virtual Trailinfo searchtrailDB() = 0;// opening database an searching

		// Destructor
		// Pure virtual destructor helps force the class to be abstract, but must still be implemented
		virtual ~MaintainTrailHandler() noexcept = 0;

	protected:
		// Copy assignment operators, protected to prevent mix derived-type assignments
		MaintainTrailHandler & operator=(const MaintainTrailHandler &  rhs) = default;  // copy assignment
		MaintainTrailHandler & operator=(MaintainTrailHandler && rhs) = default;  // move assignment

	};    // class MaintainBooksHandler





	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline MaintainTrailHandler::~MaintainTrailHandler() noexcept
	{}


} // namespace Domain::Library
