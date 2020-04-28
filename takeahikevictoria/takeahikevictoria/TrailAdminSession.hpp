#pragma once

#include <memory>
#include <string>
#include <vector>
#include <any>

#include "createSession.hpp"
#include "MaintainTrailHandler.hpp"


namespace TrailManagement
{
	class TrailAdminSession : public TrailManagement::SessionHandler
	{
	public:
		using SessionHandler::SessionHandler;  // inherit constructors

		// Operations
		std::vector<std::string> getCommands() override;  // retrieves the list of actions (commands)
		std::any getCommandfunction(std::string & command, const std::vector<std::string> & args) override;
		bool Signoff()override;
		//operations only accessible by the Trail Admin
		void manageTrailDatabase();
		void addTrail(const std::vector<std::string> & args);
		void editTrail(const std::vector<std::string> & args);
		void deleteTrail(const std::vector<std::string> & args);
		void printTrail(const std::vector<std::string> & args);
		void manageAccount();
		
		


		// Destructor
		// Pure virtual destructor helps force the class to be abstract, but must still be implemented
		~TrailAdminSession() noexcept override;
	}; // class BorrowerSession





	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline TrailAdminSession::~TrailAdminSession() noexcept
	{}


	/*inline std::vector<std::string> TrailAdminSession::getCommands()
	{
		return { "add Trail", "delete Trail","edit Trail" };
	}*/

} // namespace Domain::Library
