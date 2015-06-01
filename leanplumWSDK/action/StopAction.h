#pragma once

#include "BaseAction.h"

class CStopAction : public CBaseAction
{
public:
	CStopAction();
	virtual ~CStopAction();

	bool ParseResponse(cJSON* jResponse);
};

