#pragma once

#include "BaseAction.h"

class CSetUserAttributesAction : public CBaseAction
{
public:
	CSetUserAttributesAction();
	virtual ~CSetUserAttributesAction();

	bool ParseResponse(cJSON* jResponse);
	void SetUserAttributes(const std::vector<leanplumVar>& varList);
};

