#pragma once

#include <memory>
#include <string>
#include <vector>

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
		void getCommandfunction(std::string & command);
		bool addTrail();
		//bool deleteTrail(Trailinfo db, std::string name);


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