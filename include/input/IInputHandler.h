#ifndef IINPUTHANDLER_H_
#define IINPUTHANDLER_H_

namespace scim
{

class IInputHandler
{
public:
	virtual void CollectInputs() = 0;
};

}

#endif