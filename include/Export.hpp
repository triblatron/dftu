#ifndef __CONFIG_EXPORT_H__
#define __CONFIG_EXPORT_H__

#pragma once

#if defined(_MSC_VER)
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4275 )
    #pragma warning( disable : 4290 )
    #pragma warning( disable : 4786 )
    #pragma warning( disable : 4305 )
    #pragma warning( disable : 4996 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( DFTU_LIBRARY_STATIC )
    #    define DFTU_API
    #  elif defined( DFTU_LIBRARY )
    #    define DFTU_API   __declspec(dllexport)
    #  else
    #    define DFTU_API   __declspec(dllimport)
    #  endif
#else
    #  define DFTU_API
#endif  

#endif // !__CONFIG_EXPORT_H__
