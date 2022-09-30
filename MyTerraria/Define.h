//#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define MAX_VIRTUAL_KEY 0xff

#define MAX_TIME 600

#define WINCX 800
#define WINCY 600

#define MAP_SIZE_WIDTH_DEBUG 100
#define MAP_SIZE_HEIGHT_DEBUG 100

#define BLOCKCX 16
#define BLOCKCY 16

#define HP_HEART_SCALE_X 16
#define HP_HEART_SCALE_Y 16

#define PI 3.141592f

#define ToRadian(angle) angle * PI / 180.f
#define ToDegree(angle) angle * 180.f / PI

#define NO_COPY(ClassName)					\
private:									\
ClassName(const ClassName& Obj);			\
ClassName& operator=(const ClassName& Obj);	\

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance(){		\
		if( m_pInstance == nullptr ){		\
			m_pInstance = new ClassName;	\
		}									\
		return m_pInstance;					\
	}										\
	void DestroyInstance(){					\
		if(m_pInstance){					\
			delete m_pInstance;				\
		}									\
		m_pInstance = nullptr;				\
	}										\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;

#endif // !__DEFINE_H__
