#ifndef ASSIMPMESH_H_
#define ASSIMPMESH_H_

#include "IMesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <string>

namespace scim
{

class AssimpMesh: public IMesh
{
public:
	AssimpMesh(const aiScene* pScene, GLuint shaderProgram);
};

}

#endif
