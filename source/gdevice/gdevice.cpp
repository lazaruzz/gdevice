/*#include <windows.h>

#define EXPORTING_GDEVICE_DLL
#include "gdevice.h"

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACHED: // A process is loading the DLL.
        break;
        case DLL_THREAD_ATTACHED: // A process is creating a new thread.
        break;
        case DLL_THREAD_DETACH: // A thread exits normally.
        break;
        case DLL_PROCESS_DETACH: // A process unloads the DLL.
        break;
    }
    return TRUE;
}

*/
//_declspec (dllexport) 

//#include <string>

extern "C"
{
    __declspec(dllexport) int gdCreateWindow()
    {
        return 53;
    }

        // Graphics Device = something you can plot upon

    // var screen = gdAdd(SCREEN);
    // var buffer = gdAdd(BUFFER, 512, 512, RGBA);

    enum Type {None = 0, Screen = 1, Window = 2, Buffer = 3}; 

    int gd_Open(Type type)
    {
        return 0;
    }

    #define FPOINTER(RETURN_VALUE, ptr_name, ...) RETURN_VALUE (*ptr_name)(__VA_ARGS__)

    struct {
        
        FPOINTER(int, gd_open, Type type);

        /*FPOINTER(FILE*, fopen, const char *restrict, const char *restrict);
        FPOINTER(int, fclose, FILE*);
        FPOINTER(int, fprintf, FILE *restrict, const char *restrict, ...);
        FPOINTER(int, printf, const char *restrict, ...);
        FPOINTER(int, puts, const char*);
        FPOINTER(void*, malloc, size_t);
        FPOINTER(void, free, void*);
        const int esuccess;
        const int efailure;*/
        /*etc.*/
    } gd;// = {
        /*C99 designated initializer*/
//        add = &gd_Add
        /*.fopen    = &fopen,
        .fclose   = &fclose,
        .fprintf  = &fprintf,
        .printf   = &printf,
        .puts     = &puts,
        .malloc   = &malloc,
        .free     = &free,
        .esuccess = EXIT_SUCCESS,
        .efailure = EXIT_FAILURE,*/
        /*...*/
 //   };


}