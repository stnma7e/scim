#ifndef INPUTTOOLS_H_
#define INPUTTOOLS_H_

#include "KeyCode.h"
#include "IWindowManager.h"

namespace scim
{

bool IsKeyDown(const Input& inputStruct, char key);
void GetKeypressAndUpdate(const char, Input* inpt);

}

#endif