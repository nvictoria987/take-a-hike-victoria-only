#pragma once

#include "MaintainTrailHandler.hpp"

namespace TrailManagement
{
	class Trails : public TrailManagement::MaintainTrailHandler
	{
	public:
		// Constructors
		using MaintainTrailHandler::MaintainTrailHandler;  // inherit constructors

		// Operations
		virtual Trailinfo displaytrailDB() override;

		~Trails() noexcept override;
	}; // class Trails


	/*****************************************************************************
	** Inline implementations
	******************************************************************************/
	inline Trails::~Trails() noexcept
	{}


}  // namespace TrailManagement