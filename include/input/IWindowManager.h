#ifndef IWINDOWMANAGER_H_
#define IWINDOWMANAGER_H_

#include "IInputHandler.h"
#include "KeyCode.h"

namespace scim
{

typedef void (*resizeCallback)(I32, I32);

struct Input
{
	U32 abc;
	U32 specialKeys;
	F64 mousePosX;
	F64 mousePosY;
	I32 window_w, window_h;
};

class IWindowManager : public IInputHandler
{
protected:
	void (*m_resizeCallback)(I32 width, I32 height);
	Input m_collectedInputs;
public:
	virtual ~IWindowManager() { }
	virtual void SetResizeCallback(resizeCallback resizeCallback)
	{
		m_resizeCallback = resizeCallback;
	}

	virtual void CollectInputs() = 0;
	virtual void PreRender() = 0;
	virtual void PostRender() = 0;	

	virtual const Input* GetCollectedInput() const
	{
		return &m_collectedInputs;
	}
};

}

#endif