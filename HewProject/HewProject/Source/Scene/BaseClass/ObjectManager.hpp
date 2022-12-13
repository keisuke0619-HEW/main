#pragma once
//#define CRITICAL_LOW_FPS_TEMPORARY_RESPONSE	// “–‚½‚è”»’è‚Å‹É’[‚ÉFPS‚ª‰º‚ª‚é’v–½“IŒ‡Š×‚ðŽb’è“I‚É˜a‚ç‚°‚é


#include <list>
#include <IObjectBase.hpp>
class CObjectManager
{
public:
	static void CallDestroy();
private:
	static bool m_isCallDestroy;
public:
	CObjectManager();
	~CObjectManager();

	void UpdateAll();
	void DrawAll();

	void DestroyUpdate();
	std::weak_ptr<IObjectBase> Add(IObjectBase* obj);
	IObjectBase::Ptr FindTag(EObjectTag tag);
	IObjectBase::Ptr FindName(std::string name);
	std::list<IObjectBase::Ptr> FindTagAll(EObjectTag tag);
private:
	std::list<IObjectBase::Ptr> m_obj;
#ifdef CRITICAL_LOW_FPS_TEMPORARY_RESPONSE
	int m_frame;
#endif // CRITICAL_LOW_FPS_TEMPORARY_RESPONSE


};