#pragma once

//#include "TechnicalServices/Logging/LoggerHandler.hpp"

#include "firstDB.hpp"




namespace Persistence
{
	class SingletonDB : public SimpleDB
	{
	public:
		SingletonDB(const SingletonDB &) = delete;
		SingletonDB & operator=(const SingletonDB &) = delete;
		static SingletonDB & instance();

		~SingletonDB() noexcept override;

	private:
		using SimpleDB::SimpleDB;        // privately inherit SimpleDB constructors
		SingletonDB();

		//std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
		// convenience reference object enabling standard insertion syntax
		// This line must be physically after the definition of _loggerPtr
		//TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;

	};    // class SingletonDB
}  // namespace TechnicalServices::Persistence