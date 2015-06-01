#include "SetVarsAction.h"
#include <sstream>
#include <Windows.h>

CSetVarsAction::CSetVarsAction()
	: CBaseAction(eAPIMethodType_Development, "setVars")
{	
}

CSetVarsAction::~CSetVarsAction()
{
}

void CSetVarsAction::SetVars(const std::vector<leanplumVar>& varList)
{
	m_requestBody.clear();
	m_requestBody = "{\"vars\":" + TransVarsToJsonFormat(varList) + "}";
	OutputDebugStringA(m_requestBody.c_str());
}

bool CSetVarsAction::ParseResponse(cJSON* jResponse)
{
	return true;
}