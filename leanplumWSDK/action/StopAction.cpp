#include "StopAction.h"

CStopAction::CStopAction()
	: CBaseAction(eAPIMethodType_Production, "stop")
{
}

CStopAction::~CStopAction()
{
}

bool CStopAction::ParseResponse(cJSON* jResponse)
{
	return true;
}