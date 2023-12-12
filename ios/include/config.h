/* config.h.  not autogenerated for iOS */

/* Package Name */
#define PACKAGE "exult"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Exult"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "exult"

/* Package Version */
#define VERSION "1.9.0git"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.9.0git"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Exult 1.9.0git"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://exult.info/"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Have zip support */
#define HAVE_ZIP_SUPPORT 1

/* Build hq2x scaler */
#define USE_HQ2X_SCALER 1

/* Build hq3x scaler */
#define USE_HQ3X_SCALER 1

/* Build hq4x scaler */
#define USE_HQ4X_SCALER 1

/* Build NxBR scalers */
#define USE_XBR_SCALER 1

#define USE_FMOPL_MIDI

#define USE_FLUIDSYNTH_MIDI

#define USE_MT32EMU_MIDI

#ifndef MT32EMU_CONFIG_H
#define MT32EMU_CONFIG_H

#define MT32EMU_WITH_INTERNAL_RESAMPLER 1

/* MT32EMU Version */
#define MT32EMU_VERSION_MAJOR 2
#define MT32EMU_VERSION_MINOR 7
#define MT32EMU_VERSION_PATCH 0
#define MT32EMU_VERSION "$(MT32EMU_VERSION_MAJOR).$(MT32EMU_VERSION_MINOR).$(MT32EMU_VERSION_PATCH)" 

/* Library Exports Configuration
 *
 * This reflects the API types actually provided by the library build.
 * 0: The full-featured C++ API is only available in this build. The client application may ONLY use MT32EMU_API_TYPE 0.
 * 1: The C-compatible API is only available. The library is built as a shared object, only C functions are exported,
 *    and thus the client application may NOT use MT32EMU_API_TYPE 0.
 * 2: The C-compatible API is only available. The library is built as a shared object, only the factory function
 *    is exported, and thus the client application may ONLY use MT32EMU_API_TYPE 2.
 * 3: All the available API types are provided by the library build.
 */
#define MT32EMU_EXPORTS_TYPE  3
#endif

/* Enable Midi Sfx */
/* #undef ENABLE_MIDISFX */

/* Enable fluidsynth midi */
/* #undef USE_FLUIDSYNTH_MIDI */

/* Enable timidity midi */
/*#define USE_TIMIDITY_MIDI 1*/

/* Default timidity path */
/* #undef DEFAULT_TIMIDITY_PATH */

/* Enable ALSA midi */
/* #undef USE_ALSA_MIDI */

/* Display non-readied objects */
/* #undef SHOW_NONREADIED_OBJECTS */

/* Display Usecode container */
/* #undef SHOW_USECODE_CONTAINER */

/* Enable Usecode debugging on console */
/* #undef USECODE_CONSOLE_DEBUGGER */

/* Enable Usecode debugging */
/* #undef USECODE_DEBUGGER */

/* Use Exult Studio */
/* #undef USE_EXULTSTUDIO */

/* Have OpenGL */
/* #undef HAVE_OPENGL */

/* Define to 1 if you have the <png.h> header file. */
/*#define HAVE_PNG_H 1*/

/* Enable debug mode */
/* #undef DEBUG */

/* Using Cygwin */
/* #undef CYGWIN */

/* Using MacOSX */
/* #undef MACOSX */

/* Disable SDL parachute */
/* #undef NO_SDL_PARACHUTE */

/* Doesn't have hash map */
#define DONT_HAVE_HASH_MAP 1

/* Doesn't have hash set */
#define DONT_HAVE_HASH_SET 1

/* Define to 1 if you have the <ext/hash_map> header file. */
#define HAVE_EXT_HASH_MAP 1

/* Define to 1 if you have the <ext/hash_set> header file. */
#define HAVE_EXT_HASH_SET 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* define if the compiler supports basic C++14 syntax */
/* #undef HAVE_CXX14 */

/* define if the compiler supports basic C++17 syntax */
#define HAVE_CXX17 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* Have addrinfo/getaddrinfo */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if the system has the type `int16_t'. */
#define HAVE_INT16_T 1

/* Define to 1 if the system has the type `int32_t'. */
#define HAVE_INT32_T 1

/* Define to 1 if the system has the type `int64_t'. */
#define HAVE_INT64_T 1

/* Define to 1 if the system has the type `int8_t'. */
#define HAVE_INT8_T 1

/* Define to 1 if the system has the type `intptr_t'. */
#define HAVE_INTPTR_T 1

/* Have addrinfo/getaddrinfo */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isascii' function. */
#define HAVE_ISASCII 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Have mkstemp */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the `pow' function. */
#define HAVE_POW 1

/* Define to 1 if you have the "SDL.h" header file */
#define HAVE_SDL_H 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Have snprintf */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the <sstream> header file. */
#define HAVE_SSTREAM 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if the system has the type `uint16_t'. */
#define HAVE_UINT16_T 1

/* Define to 1 if the system has the type `uint32_t'. */
#define HAVE_UINT32_T 1

/* Define to 1 if the system has the type `uint64_t'. */
#define HAVE_UINT64_T 1

/* Define to 1 if the system has the type `uint8_t'. */
#define HAVE_UINT8_T 1

/* Define to 1 if the system has the type `uintptr_t'. */
#define HAVE_UINTPTR_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

#ifdef __LP64__
#define SIZEOF_VOIDP 8
#else
#define SIZEOF_VOIDP 4
#endif

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `int*', as computed by sizeof. */
#define SIZEOF_INTP SIZEOF_VOIDP

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG SIZEOF_VOIDP

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
