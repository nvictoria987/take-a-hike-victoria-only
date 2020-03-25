#pragma once

#include <memory>    // std::unique_ptr

#include "AccountManagementHandler.hpp"
#include "MaintainTrailHandler.hpp"


#include "PersistenceHandler.hpp"

#include "userinterfacehandler.hpp"




namespace UI
{
	/*****************************************************************************
	** Simple UI definition
	**   Simple UI is a console application meant only as a driver to the Domain Layer application. This UI will someday be replaced
	**   by a more sophisticated, user friendly implementation
	******************************************************************************/
	class SimpleUI : public UI::UserInterfaceHandler
	{
	public:
		// Constructors
		using UserInterfaceHandler::UserInterfaceHandler;  // inherit constructors
		SimpleUI();


		// Operations
		void launch() override;


		// Destructor
		~SimpleUI() noexcept override;


	private:
		// These smart pointers hold pointers to lower architectural layer's interfaces
		std::unique_ptr<AccountManagement::AccountManagementHandler>  _accounts;
		std::unique_ptr<TrailManagement::MaintainTrailHandler>        _TrailHandler;

		
		Persistence::PersistenceHandler                  & _persistentData;


		
	};
} // namespace UI
