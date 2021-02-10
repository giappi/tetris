/* 
 * File:   Singleton.h
 * Author: giappi
 *
 * Created on 2017-03-28, 2017, 20:18
 */

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
	//friend T;
public:
	static T* GetInstance(void)
	{
		if (!instance)
		{
			instance = new T;
		}
		return instance;
	}
	static void DestroyInstance()
	{
		if (instance != 0x00)
		{
			delete instance;
			instance = 0x00;
		}
	};
	Singleton& operator=(Singleton const&){};


protected:
    Singleton();
    static T* instance;
	virtual ~Singleton(){};
};

template <class T>
T* Singleton<T>::instance = 0x00;



#endif /* SINGLETON_H */

