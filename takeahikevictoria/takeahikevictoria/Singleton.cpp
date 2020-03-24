//#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "Singleton.hpp"


namespace Persistence
{
	SingletonDB & SingletonDB::instance()
	{
		static SingletonDB theInstance;
		return theInstance;
	}



	SingletonDB::SingletonDB()
		//: _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())     // will replace these factory calls with abstract factory calls next increment
	{
		//_logger << "Singleton DB being used and has been successfully initialized";
	}



	SingletonDB::~SingletonDB() noexcept
	{
		//_logger << "Singleton DB shutdown successfully";
	}




} // namespace TechnicalServices::Persistence
