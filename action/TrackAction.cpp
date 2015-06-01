#include "TrackAction.h"
#include <sstream>

CTrackAction::CTrackAction()
	: CBaseAction(eAPIMethodType_Production, "track")
{	
}

CTrackAction::~CTrackAction()
{
}

bool CTrackAction::ParseResponse(cJSON* jResponse)
{
	return true;
}

void CTrackAction::SetAttribute(const std::string eventName, int value)
{
	std::stringstream ss;
	ss << ("&event=" + eventName);
	ss << "&value=" << value;
	m_optionalArg = ss.str();
}