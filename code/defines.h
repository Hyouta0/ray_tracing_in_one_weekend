#ifndef _DEFINES_H_

#define internal        static
#define local_presist   static
#define global_variable static

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

typedef signed char b8;
typedef signed int  b32;

#define TRUE 1
#define FALSE 0

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#elif defined(_MSC_VER)
#define STATIC_ASSERT static_assert
#else
#error "No static assertion defined\n"
#endif

STATIC_ASSERT(sizeof(u8) == 1,"unsigned 1 byte is not correct\n");
STATIC_ASSERT(sizeof(u16) == 2,"unsigned 2 byte is not correct\n");
STATIC_ASSERT(sizeof(u32) == 4,"unsigned 4 byte is not correct\n");
STATIC_ASSERT(sizeof(u64) == 8,"unsigned 8 byte is not correct\n");

STATIC_ASSERT(sizeof(i8) == 1,"signed 1 byte is not correct\n");
STATIC_ASSERT(sizeof(i16) == 2,"signed 2 byte is not correct\n");
STATIC_ASSERT(sizeof(i32) == 4,"signed 4 byte is not correct\n");
STATIC_ASSERT(sizeof(i64) == 8,"signed 8 byte is not correct\n");

STATIC_ASSERT(sizeof(f32) == 4,"float 4 byte is not correct\n");
STATIC_ASSERT(sizeof(f64) == 8,"float 8 byte is not correct\n");

#if defined(DEBUG)
  #define assert(expression) if(!(expression)){ *(int *)0 = 0; }
#elif
  #define assert(expression)
#endif 

#define kilobytes(value) ((value)*1024LL)
#define megabytes(value) (kilobytes(value) * 1024LL)
#define gigabytes(value) (megabytes(value) * 1024LL)
#define terabytes(value) (gigabytes(value) * 1024LL)

// NOTE: keep this if required
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_)
#define PLATFORM_WINDOWS 1
#ifndef _WIN64 
#error "requires only 64 bit computer"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX 1
#endif

#ifdef EXPORT // export
#ifdef _MSC_VER
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif
#else // import
#ifdef _MSC_VER
#define API __declspec(dllimport)
#else
#define API
#endif
#endif

#define _DEFINES_H_ 1
#endif


