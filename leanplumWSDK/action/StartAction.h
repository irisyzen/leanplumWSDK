#pragma once

#include "BaseAction.h"

class CStartAction : public CBaseAction
{
public:
	CStartAction();
	virtual ~CStartAction();

	bool ParseResponse(cJSON* jResponse);
};

