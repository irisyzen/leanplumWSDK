// leanplumWSDK.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "leanplumWSDK.h"

ILeanplumWSDK* GetLeanplumWSDK()
{
	static CLeanplumWSDK leanplum;
    return &leanplum;
}

CLeanplumWSDK::CLeanplumWSDK()
	: m_asyncMode(false)
	, m_userID(0)
	, m_deviceID(0)
{	
}

CLeanplumWSDK::~CLeanplumWSDK()
{
	m_handler.Stop();
}

void CLeanplumWSDK::Initialize(const leanplumAPIKeys& apiKeys, unsigned int userID, unsigned int deviceID)
{	
	SetAPIKeys(apiKeys);
	SetUserID(userID);
	SetDeviceID(deviceID);
}

void CLeanplumWSDK::EnableAsyncMode(bool enable, fnStatusCallBack statusCBFn, void* context)
{
	m_asyncMode = enable;

	if (m_asyncMode && !m_handler.IsStart())
	{
		m_handler.Start();
	}
	
	m_handler.SetStatusCallbackFn(statusCBFn, context);
}

void CLeanplumWSDK::SetAPIKeys(const leanplumAPIKeys& apiKeys)
{
	m_apiKeys = apiKeys;
}

void CLeanplumWSDK::SetUserID(unsigned int userID)
{
	m_userID = userID;
}

void CLeanplumWSDK::SetDeviceID(unsigned int deviceID)
{
	m_deviceID = deviceID;
}

bool CLeanplumWSDK::Start()
{
	m_startAct.Initialize(m_apiKeys, m_userID, m_deviceID);	
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_Start, &m_startAct);
	}
	else
	{
		result = m_startAct.Do();
		m_lastErrMsg = m_startAct.GetLastErrMsg();
	}	
	return result;
}

bool CLeanplumWSDK::Stop()
{
	m_stopAct.Initialize(m_apiKeys, m_userID, m_deviceID);	
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_Stop, &m_stopAct);
	}
	else
	{
		result = m_stopAct.Do();
		m_lastErrMsg = m_stopAct.GetLastErrMsg();
	}	
	return result;
}

bool CLeanplumWSDK::SetVars(const std::vector<leanplumVar>& varList)
{
	m_setVarsAct.Initialize(m_apiKeys, m_userID, m_deviceID);
	m_setVarsAct.SetVars(varList);
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_SetVars, &m_setVarsAct);
	}
	else
	{	
		result = m_setVarsAct.Do();
		m_lastErrMsg = m_setVarsAct.GetLastErrMsg();
	}
	return result;
}

bool CLeanplumWSDK::GetVars(std::vector<leanplumVar>& varList)
{
	m_getVarsAct.Initialize(m_apiKeys, m_userID, m_deviceID);
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_GetVars, &m_getVarsAct);
	}
	else
	{
		result = m_getVarsAct.Do();
		m_lastErrMsg = m_getVarsAct.GetLastErrMsg();
		m_getVarsAct.GetVars(varList);
	}
	return result;
}

bool CLeanplumWSDK::SetUserAttributes(const std::vector<leanplumVar>& varList)
{
	m_setUserAttrAct.Initialize(m_apiKeys, m_userID, m_deviceID);
	m_setUserAttrAct.SetUserAttributes(varList);
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_SetUserAttributes, &m_setUserAttrAct);
	}
	else
	{
		result = m_setUserAttrAct.Do();
		m_lastErrMsg = m_setUserAttrAct.GetLastErrMsg();
	}
	return result;
}

bool CLeanplumWSDK::Track(const std::string eventName, int value)
{
	m_trackAct.Initialize(m_apiKeys, m_userID, m_deviceID);
	m_trackAct.SetAttribute(eventName, value);
	bool result = true;
	if (m_asyncMode)
	{
		m_handler.AddCommand(ActionType_Track, &m_trackAct);
	}
	else
	{
		result = m_trackAct.Do();
		m_lastErrMsg = m_trackAct.GetLastErrMsg();
	}
	return result;
}

void CLeanplumWSDK::GetLastErrorMsg(std::string& errMsg)
{
	errMsg = m_lastErrMsg;
}