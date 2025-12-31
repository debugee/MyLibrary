#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef BUILDING_MY_LIBRARY
    #define MY_LIBRARY_API __declspec(dllexport)
  #else
    #define MY_LIBRARY_API __declspec(dllimport)
  #endif
#else
  #define MY_LIBRARY_API
#endif

MY_LIBRARY_API
int add(int a, int b);

#ifdef __cplusplus
}
#endif

#endif // MY_LIBRARY_H