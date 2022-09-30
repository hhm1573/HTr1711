//#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template<typename T>
void SafeDelete(T& pObj) {
	if (pObj)
		delete pObj;
	pObj = nullptr;
}

#endif // !__FUNCTION_H__
