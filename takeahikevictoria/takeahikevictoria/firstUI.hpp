#pragma once

#include <memory>    // std::unique_ptr

#include "AccountManagementHandler.hpp"
#include "MaintainTrailHandler.hpp"
#include"loggerHandler.hpp"

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
		bool Signoff() ;

		// Destructor
		~SimpleUI() noexcept override;


	private:
		// These smart pointers hold pointers to lower architectural layer's interfaces
		std::unique_ptr<AccountManagement::AccountManagementHandler>  _accounts;
		std::unique_ptr<TrailManagement::MaintainTrailHandler>        _TrailHandler;
		std::unique_ptr<Logging::LoggerHandler>            _loggerPtr;
		Persistence::PersistenceHandler                  & _persistentData;


		// convenience reference object enabling standard insertion syntax
		// This line must be physically after the definition of _loggerPtr
		Logging::LoggerHandler                            & _logger = *_loggerPtr;
		
	};
} // namespace UI
