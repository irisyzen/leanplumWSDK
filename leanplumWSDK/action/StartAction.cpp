#include "StartAction.h"
#include <Windows.h>

CStartAction::CStartAction()
	: CBaseAction(eAPIMethodType_Production, "start")
{
}

CStartAction::~CStartAction()
{
}

bool CStartAction::ParseResponse(cJSON* jResponse)
{
	for (int i = 0 ; i < cJSON_GetArraySize(jResponse) ; ++i)
	{
		cJSON *jItem = cJSON_GetArrayItem(jResponse, i);
		if (!jItem)
			continue;

		cJSON *jVar = cJSON_GetObjectItem(jItem, "vars");
		if (jVar)
		{
			char *out = cJSON_Print(jVar);
			OutputDebugStringA(out);
			free(out);
		}
	}
	return true;
}