#include "SetUserAttributesAction.h"
#include <Windows.h>

CSetUserAttributesAction::CSetUserAttributesAction()
	: CBaseAction(eAPIMethodType_Production, "setUserAttributes")
{
}

CSetUserAttributesAction::~CSetUserAttributesAction()
{
}

bool CSetUserAttributesAction::ParseResponse(cJSON* jResponse)
{
	return true;
}

void CSetUserAttributesAction::SetUserAttributes(const std::vector<leanplumVar>& varList)
{
	m_optionalArg = ("&userAttributes=" + TransVarsToJsonFormat(varList));
}