#pragma once

#include "BaseAction.h"

class CTrackAction : public CBaseAction
{
public:
	CTrackAction();
	virtual ~CTrackAction();

	void SetAttribute(const std::string eventName, int value);
	bool ParseResponse(cJSON* jResponse);
};

