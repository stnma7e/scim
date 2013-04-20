#include "XMLMesh.h"
#include "res/ResourceManager.h"
#include "RenderFramework.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stdexcept>

#include <GL/glfw.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <logging/logging.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace scim
{

XMLMesh::XMLMesh(const XMLNode& meshNode, GLuint program)
{
	std::string strVertex,
				strColors,
				strIndicies,
				strTextures;
	try
	{
		strVertex = meshNode.getChildNode("vertex").getText();
		strColors = meshNode.getChildNode("color").getText();
		strIndicies = meshNode.getChildNode("index").getText();
		strTextures = meshNode.getChildNode("texture").getText();
	} catch (std::logic_error& e)
	{
		logging::log::emit<logging::Error>() << "XMLMesh not set up right: " << e.what() << logging::log::endl;
	}

	std::vector<F32> vertexList = ResourceManager::GetListFromSpacedString<F32>(strVertex);
	std::vector<U32> indexList  = ResourceManager::GetListFromSpacedString<U32>(strIndicies);
	std::vector<F32> colorList, textureList;
	std::vector<GLuint> textureIDs;

	if (!strColors.empty())
	{
		colorList = ResourceManager::GetListFromSpacedString<F32>(strColors);
	};
	if (!strTextures.empty())
	{
		textureList = ResourceManager::GetListFromSpacedString<F32>(strTextures);

		std::string textureName = meshNode.getChildNode("texture").getAttribute("name");
		GLuint textureID;
		if (ResourceManager::LoadRGBATexture(textureName, &textureID))
		{
			textureIDs.push_back(textureID);
		}
	}

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

	std::vector<glm::vec2> textureVectorList;
	glm::vec2 tmpVec3;
	for (size_t i = 0; i < textureList.size(); i += 2)
	{
		for (size_t k = 0; k < 2; ++k)
		{
			switch (k)
			{
			case 0:
				tmpVec3.x = textureList[i + k];
				break;
			case 1:
				tmpVec3.y = textureList[i + k];
				break;
			}
		}

		textureVectorList.push_back(tmpVec3);
	}

	m_subMeshes.push_back(new MeshData(program,
		vertVectorList,
		indexList,
		colorVectorList,
		textureVectorList,
		std::vector<glm::vec3>(),	// empty normal list
		textureIDs
	));
}

}
