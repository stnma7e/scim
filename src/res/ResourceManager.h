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

	template<typename T>
	static T ato(const char* c);
	bool IsFloatDevice(char t);
	bool IsPrintableChar(char t);
public:
	std::string FindFileOrThrow(const std::string &strBasename); // returns name of file if in resource directory
	std::string GetFileContents(const std::string &strFilename);

	template <typename T>
	std::vector<T> GetListFromSpacedString(const std::string &strDataList)
	{
	    std::string s(strDataList);
	    std::string tmp;
	    std::vector<T> vertVector;
	    bool lastCharWasPrintable = true;
	    for (std::string::iterator it = s.begin(); it != s.end(); ++it)
	    {
	        char t = (*it);
	        if (IsFloatDevice(t))
	        {
	            // printf("char: %c\n", t);
	            if (lastCharWasPrintable)
	                tmp += t;
	            else
	            {
	                std::string ss(tmp);
	                // printf("string: %s\n", ss.c_str());

	                vertVector.push_back(ato<T>(ss.c_str()));
	                // printf("%f\n", vertVector.back());
	                tmp.clear();
	                tmp += t;

	                lastCharWasPrintable = true;
	            }
	        } else
	        {
	            lastCharWasPrintable = false;
	        }
	    }
	    vertVector.push_back(ato<T>(tmp.c_str()));

	    return vertVector;
	}
};

}
#endif
