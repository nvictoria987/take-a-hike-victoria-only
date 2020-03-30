#pragma once

#include <memory>    // std::unique_ptr
#include <string>

#include "AccountManagementHandler.hpp"

#include "PersistenceHandler.hpp"


namespace AccountManagement
{
	class UserAccounts : public AccountManagement::AccountManagementHandler
	{
	public:
		using AccountManagementHandler::AccountManagementHandler;  // inherit constructors
		UserAccounts();

		// Operations
		bool isAuthenticated(const UserCredentials & credentials) override;
		//void editPassword(const UserCredentials & credentials);


		// Destructor
		~UserAccounts() noexcept override;


	private:
		// These smart pointers hold pointers to lower architectural layer's interfaces
		Persistence::PersistenceHandler &   _persistentData;
		
	
	};
} // namespace Domain::AccountManagement
