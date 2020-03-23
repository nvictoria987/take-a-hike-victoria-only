#pragma once

#include<string>

#include "C:\Users\Victoria\Desktop\takeahikevictoria\takeahikevictoria\PersistenceHandler.hpp"

namespace AccountManagement
{
	//this is where we would the persistance handler
	using Persistence::UserCredentials;

	class AccountManagementHandler
	{
		public:
			//constructors and assignment operations 
			AccountManagementHandler() = default;
			AccountManagementHandler(const AccountManagementHandler & original) = default;
			AccountManagementHandler(AccountManagementHandler && original) = default;

			//operations
			virtual bool isAuthenticated(const UserCredentials & credent) = 0;


			// Abstract class destructor
			virtual ~AccountManagementHandler() noexcept = 0;  // must be virtual and pure

	protected:
		// Copy assignment operators, protected to prevent mix derived-type assignments
		AccountManagementHandler & operator=(const AccountManagementHandler &  rhs) = default;    // copy assignment
		AccountManagementHandler & operator=(AccountManagementHandler && rhs) = default;    // move assignment
	};

	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline AccountManagementHandler::~AccountManagementHandler() noexcept
	{}


} // namespace Domain::AccountManagem