#pragma once
#include "cJSON\cJSON.h"
#include "leanplumWSDKDefine.h"
#include <vector>

enum eAPIMethodType
{
	eAPIMethodType_Production,
	eAPIMethodType_Development,
	eAPIMethodType_DataExport,
	eAPIMethodType_ContentReadOnly
};

class CBaseAction
{
public:
	CBaseAction(eAPIMethodType methodType, const std::string& actionName);
	virtual ~CBaseAction();
	
	void Initialize(const leanplumAPIKeys& apiKeys, unsigned int userID, unsigned int deviceID);
	
	bool Do();
	std::string GetLastErrMsg() { return m_lastErrMsg; }

	virtual bool ParseResponse(cJSON* jRoot) = 0;
	virtual void* GetResult() { return NULL; }

protected:
	std::string TransVarsToJsonFormat(const std::vector<leanplumVar>& varList);

	std::string m_optionalArg;
	std::string m_requestBody;

private:
	std::string GetCommand();

	eAPIMethodType m_methodType;

	std::string m_actionName;

	std::string m_lastErrMsg;

	leanplumAPIKeys m_apiKeys;
	unsigned int m_userID;
	unsigned int m_deviceID;
};