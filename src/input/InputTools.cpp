#include "input/InputTools.h"

#include <cmath>
#include <stdio.h>

namespace scim
{

namespace
{
	bool IsLowerCaseKeyDown(const Input& inptStruct, const char key)
	{
		I8 pow = key - 97;
		return ((1 << pow) & inptStruct.abc);
	}
	inline bool IsLowercaseKey(const char key)
	{
		return (key >= 97 && key <= 122);
	}
	inline bool IsUppercaseKey(const char key)
	{
		return (key >= 65 && key <= 90);
	}
}

bool IsKeyDown(const Input& inptStruct, const char key)
{
	printf("%d\n", key);

	if (IsUppercaseKey(key))
	{
		if ((inptStruct.specialKeys & SCIM_KEY_LSHIFT) || (inptStruct.specialKeys & SCIM_KEY_RSHIFT))
		{
			return IsLowerCaseKeyDown(inptStruct, key + 32);
		} else
		{
			return false;
		}
	} else if (IsLowercaseKey(key))
	{
		if ((inptStruct.specialKeys & SCIM_KEY_LSHIFT) || (inptStruct.specialKeys & SCIM_KEY_RSHIFT))
		{
			return false;
		} else
			return IsLowerCaseKeyDown(inptStruct, key);
	} else
	{
		return false;
	}
}
void GetKeypressAndUpdate(const char key, Input* inpt)
{
	if (IsUppercaseKey(key))
	{
		I32 pow = key - 65;
		I32 hex = (1 << pow);
		inpt->abc = inpt->abc | hex | SCIM_KEY_LSHIFT;
	} else if (IsLowercaseKey(key))
	{
		I32 pow = key - 97;
		I32 hex = (1 << pow);
		inpt->abc = inpt->abc | hex;
	} else
	{
		switch (key)
		{
		case 27: // ESC
			{
				inpt->specialKeys = inpt->specialKeys | SCIM_KEY_ESC;
			}
			break;
		}
	}
}

}