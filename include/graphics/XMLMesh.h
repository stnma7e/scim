#ifndef XMLMESH_H_
#define XMLMESH_H_

#include "IMesh.h"

#include <xmlParser.h>

namespace scim
{

class XMLMesh: public IMesh
{
public:
	XMLMesh(const XMLNode& compRootNode, GLuint program);
};

}

#endif
