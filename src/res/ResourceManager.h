#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "../common/Singleton.h"

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
	    for (std::string::iterator it = s.begin(); it != s.end(); ++it)
	    {
	        char t = (*it);
	        if (IsFloatDevice(t))
	        {
	            // printf("char: %c\n", t);

	            tmp += t;
	        } else
	        {
	            // printf("%c: is not float device\n", t);

	            --it;
	            if (IsFloatDevice(*it))
	            {
	            	std::string ss(tmp);
	                // printf("string: %s\n", ss.c_str());

                	vertVector.push_back(ato<T>(ss.c_str()));
	                // printf("%f\n", vertVector.back());
	                tmp.clear();
	                tmp += t;
	            }
	            ++it;
	        }
	    }

	    return vertVector;
	}
};

}
#endif
