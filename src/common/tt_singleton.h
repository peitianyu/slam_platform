#ifndef __COMMON_SINGLETON_H__
#define __COMMON_SINGLETON_H__


namespace common
{

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	const Singleton& operator=(const Singleton&) = delete;

	Singleton():m_pointer(nullptr) 
	{}

	virtual ~Singleton() { delete m_pointer; }

	T* Get()
	{
		if(m_pointer == nullptr)
			m_pointer = new T;

		return m_pointer;
	}

private:
	T* m_pointer;
};


} // namespace common

#endif // __COMMON_SINGLETON_H__