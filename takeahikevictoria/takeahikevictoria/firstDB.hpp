#pragma once

#include <memory>    // unique_ptr
#include <string>
#include <vector>

//#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "PersistenceHandler.hpp"




namespace Persistence
{
  class SimpleDB : public Persistence::PersistenceHandler
  {
    public:
      using PersistenceHandler::PersistenceHandler;    // inherit constructors
      SimpleDB();
	  //static SimpleDB & instance();

      // Operations
      std::vector<std::string> findRoles()                                       override;  // Returns list of all legal roles
      UserCredentials          findCredentialsByName( const std::string & name ) override;  // Returns credentials for specified user, throws NoSuchUser if user not found


      ~SimpleDB() noexcept override;

    private:
      //std::unique_ptr<TechnicalServices::Logging::LoggerHandler>             _loggerPtr;

      // convenience reference object enabling standard insertion syntax
      // This line must be physically after the definition of _loggerPtr
     // TechnicalServices::Logging::LoggerHandler                            & _logger = *_loggerPtr;

  }; // class SimpleDB
}  // namespace TechnicalServices::Persistence

