#include "ResourceManager.h"

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <stdexcept>

#define GLOBAL_FILE_DIR "../../res/"
#define LOCAL_FILE_DIR GLOBAL_FILE_DIR

namespace scim
{

ResourceManager::ResourceManager()
{

}

std::string ResourceManager::FindFileOrThrow(const std::string &strBasename)
{
    std::string strFilename = LOCAL_FILE_DIR + strBasename;
    std::ifstream testFile(strFilename.c_str());
    if(testFile.is_open())
        return strFilename.c_str();


    strFilename = GLOBAL_FILE_DIR + strBasename;
    testFile.open(strFilename.c_str());
    if(testFile.is_open())
        return strFilename.c_str();

    throw std::runtime_error("Could not find the file " + strBasename);
}
std::string ResourceManager::GetFileContents(const std::string &strFilename)
{
    std::ifstream resFile(strFilename.c_str());
    std::stringstream fileData;
    fileData << resFile.rdbuf();
    resFile.close();
    return fileData.str();
}

bool ResourceManager::IsFloatDevice(char t)
{
    if (((t >= 48) && (t <=57)) || (t == 46) || (t == 45) || (t == 43))
        return true;
    else
        return false;
}

template<>
I32 ResourceManager::ato<I32>(const char* c)
{
    return atoi(c);
}

template<>
F32 ResourceManager::ato<F32>(const char* c)
{
    return atof(c);
}

}
