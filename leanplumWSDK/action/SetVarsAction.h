#pragma once

#include "BaseAction.h"

class CSetVarsAction : public CBaseAction
{
public:
	CSetVarsAction();
	virtual ~CSetVarsAction();

	void SetVars(const std::vector<leanplumVar>& varList);

	bool ParseResponse(cJSON* jResponse);
};

