#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace scim
{

template <typename T>
class Singleton
{
protected:
	static T* m_instance;
public:
	Singleton() {}
	virtual ~Singleton() {}

	//
	static T* GetInstance()
	{
		if (m_instance == 0)
			m_instance = new T;

		return m_instance;
	}
};

template <typename T> T* Singleton<T>::m_instance = 0;

}
#endif
