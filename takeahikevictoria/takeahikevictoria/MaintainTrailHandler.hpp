#pragma once

namespace TrailManagement
{
	// Library Package within the Domain Layer Abstract class
	class MaintainTrailHandler
	{
	public:
		// Constructors
		MaintainTrailHandler() = default;        // default ctor
		MaintainTrailHandler(const MaintainTrailHandler &  original) = default;        // copy ctor
		MaintainTrailHandler(MaintainTrailHandler && original) = default;        // move ctor

		// Operations

		// Destructor
		// Pure virtual destructor helps force the class to be abstract, but must still be implemented
		virtual ~MaintainTrailHandler() noexcept = 0;

	protected:
		// Copy assignment operators, protected to prevent mix derived-type assignments
		MaintainTrailHandler & operator=(const MaintainTrailHandler &  rhs) = default;  // copy assignment
		MaintainTrailHandler & operator=(MaintainTrailHandler && rhs) = default;  // move assignment

	};    // class MaintainBooksHandler





	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline MaintainTrailHandler::~MaintainTrailHandler() noexcept
	{}


} // namespace Domain::Library