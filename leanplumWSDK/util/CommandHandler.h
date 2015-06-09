#pragma once

#include <thread>
#include <mutex>
#include <list>
#include <vector>
#include "leanplumWSDKDefine.h"

typedef void (*fnStatusCallBack)(ActionType type, bool success, std::string errorMsg, void* extraInfo, void* context);

class CBaseAction;

struct CommandInfo
{
	ActionType type;
	CBaseAction* action;

	CommandInfo()
		: type(ActionType_None)
		, action(NULL)
	{
	}

	CommandInfo(ActionType inType, CBaseAction* inAction)
		: type(inType), action(inAction)
	{
	}
};

class CCommandHandler
{
public:
	CCommandHandler();
	~CCommandHandler();

	bool IsStart();
	void Start();
	void Stop();
	void AddCommand(ActionType type, CBaseAction* action);
	void SetStatusCallbackFn(fnStatusCallBack fn, void* context);

protected:
	void ThreadProc();

private:
	bool m_stop;
	std::list<CommandInfo> m_cmdQueue;
	fnStatusCallBack m_statusCBFn;
	void* m_context;

	std::thread* m_thread;
	std::mutex m_mutex;
};

