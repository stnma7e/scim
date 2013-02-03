#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace scim
{

template <typename T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() { }

	static T& GetInstance()
	{
		static T m_instance;

		return m_instance;
	}
};

// template <typename T> T* Singleton<T>::m_instance = 0;

}
#endif
