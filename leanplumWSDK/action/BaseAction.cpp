#include "BaseAction.h"
#include "curl/cURLClient.h"
#include <sstream>
#include <Windows.h>

CBaseAction::CBaseAction(eAPIMethodType methodType, const std::string& actionName)
	: m_methodType(methodType)
	, m_actionName(actionName)	
{
}

CBaseAction::~CBaseAction()
{
}

void CBaseAction::Initialize(const leanplumAPIKeys& apiKeys, unsigned int userID, unsigned int deviceID)
{
	m_apiKeys = apiKeys;
	m_userID = userID;
	m_deviceID = deviceID;
}

std::string CBaseAction::GetCommand()
{
	std::stringstream command;
	command << "https://www.leanplum.com/api?";
	command << ("action=" + m_actionName + "&appId=" + m_apiKeys.appID);
	command << "&userId=" << m_userID << "&deviceId=" << m_deviceID;
	switch (m_methodType)
	{
	case eAPIMethodType_Production:
		command << ("&clientKey=" + m_apiKeys.productionKey);
		break;
	case eAPIMethodType_Development:
		command << ("&clientKey=" + m_apiKeys.developmentKey);
		break;
	case eAPIMethodType_DataExport:
		command << ("&clientKey=" + m_apiKeys.dataExportKey);
		break;
	case eAPIMethodType_ContentReadOnly:
		command << ("&clientKey=" + m_apiKeys.contentReadOnlyKey);
		break;
	}
	
	if (!m_optionalArg.empty())
		command << m_optionalArg;

	command << ("&apiVersion=1.0.6");
	OutputDebugStringA(command.str().c_str());
	return command.str();
}

bool CBaseAction::Do()
{
	CURLClient client;
	std::string response;
	if (!m_requestBody.empty())
		response = client.GetWithRequest(GetCommand(), m_requestBody);
	else
		response = client.Get(GetCommand());

	cJSON *jRoot = cJSON_Parse(response.c_str());
	if (!jRoot)
	{
		return false;
	}

	cJSON *jResponse = cJSON_GetObjectItem(jRoot, "response");
	for (int i = 0 ; i < cJSON_GetArraySize(jResponse) ; ++i)
	{
		cJSON *jItem = cJSON_GetArrayItem(jResponse, i);
		if (!jItem)
			continue;
		
		cJSON *jResult = cJSON_GetObjectItem(jItem, "success");
		if (!jResult)
			return false;

		if (cJSON_False == jResult->type)
		{
			cJSON *jErr = cJSON_GetObjectItem(jItem, "error");
			if (jErr)
			{
				cJSON *errMsg = cJSON_GetObjectItem(jErr, "message");
				OutputDebugStringA(errMsg->valuestring);
				m_lastErrMsg = errMsg->valuestring;
				return false;
			}
		}
		else
		{
			ParseResponse(jResponse);
		}
	}

	cJSON_Delete(jRoot);
	return true;
}

std::string CBaseAction::TransVarsToJsonFormat(const std::vector<leanplumVar>& varList)
{
	std::stringstream ss("{");
	for (size_t i=0; i<varList.size(); ++i)
	{
		ss << "\"" << varList[i].name << "\":";
		switch (varList[i].type)
		{
		case eLeanplumVarType_Int:
			ss << varList[i].nValue;
			break;
		case eLeanplumVarType_String:
			ss << "\"" << varList[i].sValue;
			break;
		case eLeanplumVarType_Bool:
			varList[i].bValue?(ss << "true"): (ss << "false");			
			break;
		}

		if (i != varList.size()-1)
			ss << ",";
	}
	ss << "}";
	return ss.str();
}