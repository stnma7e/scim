#include "res/ResourceManager.h"

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <IL/il.h>

#define GLOBAL_FILE_DIR "../../res/"
#define LOCAL_FILE_DIR GLOBAL_FILE_DIR

namespace scim
{

namespace ResourceManager
{

namespace
{
    std::string FindFileOrThrow(const std::string &strBasename)
    {
        std::string strFilename = LOCAL_FILE_DIR + strBasename;
        std::ifstream testFile(strFilename.c_str());
        if(testFile.is_open())
            return strFilename;

        strFilename = GLOBAL_FILE_DIR + strBasename;
        testFile.open(strFilename.c_str());
        if(testFile.is_open())
            return strFilename;

        throw std::runtime_error("Could not find the file " + strBasename);
    }
}

bool LoadRGBATexture(const std::string& textureName, GLuint* textureID)
{
	ILuint imageID;
	ILboolean success = false;
	std::string fullpath = FindFileOrThrow("graphics/texture/" + textureName);

	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	success = ilLoadImage((ILstring)fullpath.c_str());
	if (!success)
	{
		LOG_ERR("texture resource '%s' is unavailable", fullpath.c_str());
		ilDeleteImages(1, &imageID);
		return false;
	}
	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	if (!success)
	{
		LOG_ERR("could not convert texture resource '%s'", (fullpath + textureName).c_str());
		ilDeleteImages(1, &imageID);
		return false;
	}

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0, ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_TYPE),
		ilGetData()
	);
	ilDeleteImages(1, &imageID);

	return textureID;
}

std::string GetFileContents(const std::string &strBasename)
{
	std::string strFilename = FindFileOrThrow(strBasename);
	std::ifstream resFile(strFilename.c_str());
	std::stringstream fileData;
	fileData << resFile.rdbuf();
	resFile.close();
	if (fileData.str().size())
	{
		return fileData.str();
	} else
	{
		return std::string();
	}
}

bool IsFloatDevice(char t)
{
	if (((t >= 48) && (t <=57)) || (t == 46) || (t == 45) || (t == 43))
		return true;
	else
		return false;
}

}

}
