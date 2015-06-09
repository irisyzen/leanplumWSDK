#pragma once

#include "IleanplumWSDK.h"
#include "ActionList.h"
#include "CommandHandler.h"

class CLeanplumWSDK : public ILeanplumWSDK
{
public:
	CLeanplumWSDK();
	~CLeanplumWSDK();

	void Initialize(const leanplumAPIKeys& apiKeys, unsigned int userID, unsigned int deviceID);
	void EnableAsyncMode(bool enable, fnStatusCallBack statusCBFn, void* context); 

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
	bool m_asyncMode;

	CStartAction m_startAct;
	CStopAction m_stopAct;
	CGetVarsAction m_getVarsAct;
	CSetVarsAction m_setVarsAct;
	CSetUserAttributesAction m_setUserAttrAct;
	CTrackAction m_trackAct;

	CCommandHandler m_handler;

	std::string m_lastErrMsg;

	leanplumAPIKeys m_apiKeys;

	unsigned int m_userID;
	unsigned int m_deviceID;
};
