/*#pragma once

#ifdef EXPORTING_GDEVICE_DLL
#define GDEVICE_API __declspec(dllexport)
#else
#define GDEVICE_API __declspec(dllimport)
#endif

#ifdef __cpluscplus
extern "C" {
#endif


GDEVICE_API int summit(int, int);



#ifdef __cpluscplus
}
#endif
*/



#if defined(_MSC_VER)
	#pragma comment( lib, "gdevice.lib" )
#elif
	#error unhandled compiler!
#endif



#ifdef __cpluscplus
extern "C" {
#endif

__declspec(dllimport) int gdCreateWindow();

#ifdef __cpluscplus
}
#endif