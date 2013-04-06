#include "XMLMesh.h"
#include "res/ResourceManager.h"
#include "RenderFramework.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace scim
{

extern RenderFramework* g_renderFramework;

XMLMesh::XMLMesh(const XMLNode& compRootNode, GLuint program)
{
	XMLNode vertexNode = compRootNode.getChildNode("vertex");
	std::stringstream strVertex(vertexNode.getText());

	XMLNode colorNode = compRootNode.getChildNode("color");
	std::stringstream strColors(colorNode.getText());

	XMLNode indexNode = compRootNode.getChildNode("index");
	std::stringstream strIndicies(indexNode.getText());

	std::vector<F32> vertexList = ResourceManager::GetListFromSpacedString<F32>(strVertex.str());
	std::vector<F32> colorList  = ResourceManager::GetListFromSpacedString<F32>(strColors.str());
	std::vector<U32> indexList  = ResourceManager::GetListFromSpacedString<U32>(strIndicies.str());

	std::vector<glm::vec3> vertVectorList;
	glm::vec3 tmpVec;
	for (size_t i = 0; i < vertexList.size(); i += 3)
	{
		for (size_t k = 0; k < 3; ++k)
		{
			switch (k)
			{
			case 0:
				tmpVec.x = vertexList[i + k];
				break;
			case 1:
				tmpVec.y = vertexList[i + k];
				break;
			case 2:
				tmpVec.z = vertexList[i + k];
				break;
			}
		}

		vertVectorList.push_back(tmpVec);
	}

	std::vector<glm::vec4> colorVectorList;
	glm::vec4 tmpVec2;
	for (size_t i = 0; i < colorList.size(); i += 4)
	{
		for (size_t k = 0; k < 4; ++k)
		{
			switch (k)
			{
			case 0:
				tmpVec2.x = colorList[i + k];
				break;
			case 1:
				tmpVec2.y = colorList[i + k];
				break;
			case 2:
				tmpVec2.z = colorList[i + k];
				break;
			case 3:
				tmpVec2.w = colorList[i + k];
				break;
			}
		}

		colorVectorList.push_back(tmpVec2);
	}

	m_subMeshes.push_back(new MeshData(program,
		vertVectorList,
		indexList,
		colorVectorList,
		std::vector<glm::vec2>(),
		std::vector<glm::vec3>()
	));
}

}
