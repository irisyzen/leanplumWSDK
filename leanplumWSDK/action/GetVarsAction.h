#pragma once

#include "BaseAction.h"

class CGetVarsAction : public CBaseAction
{
public:
	CGetVarsAction();
	virtual ~CGetVarsAction();

	bool ParseResponse(cJSON* jResponse);
	void GetVars(std::vector<leanplumVar>& varList);

	void* GetResult();

private:
	std::vector<leanplumVar> m_varList;
};

