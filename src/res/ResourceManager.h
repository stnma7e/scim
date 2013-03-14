#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "common/Singleton.h"

#include <string>
#include <vector>

namespace scim
{

class ResourceManager: public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
	ResourceManager();

public:
	std::string FindFileOrThrow(const std::string &strBasename); // returns name of file if in resource directory
	std::string GetFileContents(const std::string &strFilename);

	template<typename T>
	static T ato(const char* c);
	bool IsFloatDevice(char t);

	template <typename T>
	std::vector<T> GetListFromSpacedString(const std::string &strDataList)
	{
	    std::string s(strDataList);
	    std::string tmp;
	    std::vector<T> vertVector;
	    for (size_t i = 0; i < s.size(); ++i)
	    {
	        char t = s[i];
	        if (IsFloatDevice(t))
	        {
	            // printf("char: %c\n", t);

	            tmp += t;
	        } else
	        {
	            // printf("%c: is not float device\n", t);

	            if (IsFloatDevice(s[i-1]))
	            {
	            	std::string ss(tmp);
	                // printf("string: %s\n", ss.c_str());

                	vertVector.push_back(ato<T>(ss.c_str()));
	                // printf("%f\n", vertVector.back());
	                tmp.clear();
	                tmp += t;
	            }
	        }
	    }

	    return vertVector;
	}
};

}
#endif
