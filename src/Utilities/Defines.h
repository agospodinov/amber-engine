#ifndef DEFINES_H
#define DEFINES_H

#if defined(WIN32) || defined(_WIN32)
#  if defined(COMPILING_DLL)
#    ifdef __GNUC__
#      define AMBER_EXPORTS __attribute__((dllexport))
#    else
#      define  AMBER_EXPORTS __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define AMBER_EXPORTS __attribute__((dllimport))
#    else
#      define  AMBER_EXPORTS __declspec(dllimport)
#    endif
#  endif /* COMPILING_DLL */
#  define AMBER_PRIVATE
#else /* defined (_WIN32) */
#    if __GNUC__ >= 4
#      define AMBER_EXPORTS __attribute__((visibility("default")))
#      define AMBER_PRIVATE __attribute__((visibility("hidden")))
#    else
#      define AMBER_EXPORTS
#      define AMBER_PRIVATE
#    endif
#endif

#define AMBER_UNUSED(variable) ((void) variable)

#endif // DEFINES_H
