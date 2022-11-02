#pragma once

#include <GL/glew.h>
//#include "vendor/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <signal.h>
#include <memory>
#include <iostream>
#include <vector>

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
template<typename F, typename S>
using Pair = std::pair<F, S>;

template<typename T>
using Vector = std::vector<T>;

// print
#define PRINT(x) std::cout << (x) << std::endl;

// regular assert, just raises signal if false
#define GLASSERT(x) \
    if (!(x))     \
        raise(SIGTRAP);

// allmän macro info: #x turns x into a string
// this macro does an assertion on passed in function and prints out:
// error code, file, line
// #define GLCall(x)   \
//     GLClearError(); \
//     x;              \
//     GLASSERT(GLLogCall(#x, __FILE__, __LINE__));

#define ASSERT(x)   \
    if(!(x))    \
        AssertFailedLog(#x, __FILE__, __LINE__);

#define PASSERT(x)   \
    if(!(x))    \
    {   \
        AssertFailedLog(#x, __FILE__, __LINE__); \
        raise(SIGTRAP);  \
    };

inline void AssertFailedLog(const char *value, const char *file, int line)
{
    std::cout << "[Assert Failed] value: " << value << ", file: " << file << ", line: " << line << std::endl;
}

inline void ConsoleLogLocation(const char *function, const char *file, int line)
{
    std::cout << "[Location] function: " << function << ", file: " << file << ", line: " << line << std::endl;
}