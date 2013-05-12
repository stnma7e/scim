#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "common/Singleton.h"

#include <string>
#include <vector>
#include <GL/glew.h>

namespace scim
{

namespace ResourceManager
{

template <typename T>
T GetFileContents(const std::string &strBasename);

bool LoadRGBATexture(const std::string& textureName, GLuint* textureID);

template <typename T>
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
    vertVector.push_back(ato<T>(tmp.c_str()));
    return vertVector;
}

template<>
inline I32 ato<I32>(const char* c)
{
    return atoi(c);
}
template<>
inline U32 ato<U32>(const char* c)
{
    return (U32)atoi(c);
}

template<>
inline F32 ato<F32>(const char* c)
{
    return atof(c);
}

}

}
#endif
