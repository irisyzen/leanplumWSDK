#pragma once

#include "IleanplumWSDK.h"
#include "ActionList.h"

class CLeanplumWSDK : public ILeanplumWSDK
{
public:
	void Initialize(const leanplumAPIKeys& apiKeys, unsigned int userID, unsigned int deviceID);

	void SetAPIKeys(const leanplumAPIKeys& apiKeys);	
	void SetUserID(unsigned int userID);
	void SetDeviceID(unsigned int deviceID);
	
	bool Start();
	bool Stop();

	bool SetVars(const std::vector<leanplumVar>& varList);
	bool GetVars(std::vector<leanplumVar>& varList);

	bool SetUserAttributes(const std::vector<leanplumVar>& varList);

	bool Track(const std::string eventName, int value);
	
	void GetLastErrorMsg(std::string& errMsg);

private:
	CStartAction m_startAct;
	CStopAction m_stopAct;
	CGetVarsAction m_getVarsAct;
	CSetVarsAction m_setVarsAct;
	CSetUserAttributesAction m_setUserAttrAct;
	CTrackAction m_trackAct;

	std::string m_lastErrMsg;

	leanplumAPIKeys m_apiKeys;

	unsigned int m_userID;
	unsigned int m_deviceID;
};
