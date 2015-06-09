#include "CommandHandler.h"
#include <windows.h>
#include "BaseAction.h"

void CCommandHandler::ThreadProc()
{
	while (1)
    {		
		if (m_stop)
			break;

		m_mutex.lock();
		if (!m_cmdQueue.empty())
		{
			CommandInfo info = m_cmdQueue.front();
			m_cmdQueue.pop_front();
			if (info.action)
			{
				bool success = info.action->Do();
				if (m_statusCBFn)
				{
					m_statusCBFn(info.type, success, info.action->GetLastErrMsg(), info.action->GetResult(), m_context);
				}
			}
			m_mutex.unlock();
		}
		else
		{
			m_mutex.unlock();
		}
		Sleep(1);
	}
}

CCommandHandler::CCommandHandler(void)
	: m_thread(NULL)
	, m_stop(false)
	, m_statusCBFn(NULL)
{
}

CCommandHandler::~CCommandHandler(void)
{
}

void CCommandHandler::Start()
{
	m_stop = false;
	if (!m_thread)
	{		
		m_thread = new std::thread([this]{this->ThreadProc();});
	}
}

void CCommandHandler::Stop()
{
	if (m_thread)
	{
		m_stop = true;
		m_thread->join();		
		delete m_thread;
	}
}

bool CCommandHandler::IsStart()
{
	return (NULL != m_thread);
}

void CCommandHandler::AddCommand(ActionType type, CBaseAction* action)
{
	m_mutex.lock();	
	m_cmdQueue.push_back(CommandInfo(type, action));
	m_mutex.unlock();
}

void CCommandHandler::SetStatusCallbackFn(fnStatusCallBack fn, void* context) 
{ 
	m_statusCBFn = fn; 
	m_context = context;
}	