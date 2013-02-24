#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "../common/Singleton.h"

#include <string>

namespace scim
{

class ResourceManager: public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
	ResourceManager();
public:
	std::string FindFileOrThrow(const std::string &strBasename); // returns name of file if in resource directory
	std::string GetFileContents(const std::string &strFilename);
};

}
#endif
