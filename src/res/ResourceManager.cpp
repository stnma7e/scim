#include "ResourceManager.h"

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <stdexcept>

#define GLOBAL_FILE_DIR "../../assets/graphics/shader/"
#define LOCAL_FILE_DIR "../../assets/graphics/shader/"

namespace scim
{

ResourceManager::ResourceManager()
{

}

std::string ResourceManager::FindFileOrThrow( const std::string &strBasename )
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

}
