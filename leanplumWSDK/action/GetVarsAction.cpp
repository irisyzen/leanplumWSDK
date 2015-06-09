#include "GetVarsAction.h"
#include <Windows.h>

CGetVarsAction::CGetVarsAction()
	: CBaseAction(eAPIMethodType_Development, "getVars")
{
}

CGetVarsAction::~CGetVarsAction()
{
}

bool CGetVarsAction::ParseResponse(cJSON* jResponse)
{
	m_varList.clear();
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

			for (int j = 0; j < cJSON_GetArraySize(jVar); ++j)
			{
				cJSON *jSubItem = cJSON_GetArrayItem(jVar, i);
				if (!jSubItem)
					continue;

				leanplumVar var;
				var.name = jSubItem->string;
				switch (jSubItem->type)
				{
				case cJSON_Number:
					var.type = eLeanplumVarType_Int;
					var.nValue = jSubItem->valueint;
					break;
				case cJSON_String:
					var.type = eLeanplumVarType_String;
					var.sValue = jSubItem->valuestring;
					break;
				case cJSON_False:
					var.type = eLeanplumVarType_Bool;
					var.bValue = false;
					break;
				case cJSON_True:
					var.type = eLeanplumVarType_Bool;
					var.bValue = true;
					break;
				default:
					// ASSERT
					break;
				}
				m_varList.push_back(var);
			}
		}
	}
	return true;
}

void CGetVarsAction::GetVars(std::vector<leanplumVar>& varList)
{
	varList = m_varList;
}

void* CGetVarsAction::GetResult()
{
	return (void*)&m_varList;
}