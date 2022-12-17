#pragma once

#include <memory>

enum 
class CUIBase
{
public:
	using Ptr = std::shared_ptr<CUIBase>;
	using Ref = std::weak_ptr<CUIBase>;
	CUIBase();
	virtual ~CUIBase();

	virtual void Update();
	virtual void Draw();
private:

};