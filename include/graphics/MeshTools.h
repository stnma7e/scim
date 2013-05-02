#ifndef ASSIMPTOOLS_H_
#define ASSIMPTOOLS_H_

#include "AssimpMesh.h"
#include "XMLMesh.h"

#include <string>

namespace scim
{

namespace MeshTools
{
	template <typename T>
	T* GetMesh(const std::string& entityName);
}

}

#endif
