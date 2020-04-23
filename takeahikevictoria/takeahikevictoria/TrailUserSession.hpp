#pragma once

#include <memory>
#include <string>
#include <vector>

#include "createSession.hpp"
#include "MaintainTrailHandler.hpp"

namespace TrailManagement
{
	class TrailUserSession : public TrailManagement::SessionHandler
	{
	public:
		using SessionHandler::SessionHandler;  // inherit constructors

		// Operations
		std::vector<std::string> getCommands() override;  // retrieves the list of actions (commands)
		void getCommandfunction(std::string & command) override;
		
		//operations only accessible byt the Trail User
		void selectTrail();
		Trailinfo selectCate(Trailinfo);
		Trailinfo selectAttr(Trailinfo);
		Trailinfo trailChoice(Trailinfo);
		void printTrail(std::vector<Trailinfo>);
		void manageAccount();
		
		// Destructor
		// Pure virtual destructor helps force the class to be abstract, but must still be implemented
		~TrailUserSession() noexcept override;
	}; // class BorrowerSession





	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline TrailUserSession::~TrailUserSession() noexcept
	{}

	/*
	inline std::vector<std::string> TrailUserSession::getCommands()
	{
		return { "filter trail", "look up trail","working" };
	}
	inline void TrailUserSession::getCommandfunction(std::string & command)
	{
	}
	*/
} // namespace Domain::Library
