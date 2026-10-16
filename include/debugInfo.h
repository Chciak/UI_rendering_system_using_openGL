#pragma once

#define APPINFO     true
#define SHADERINFO  true
#define MESHINFO    true

#if APPINFO
    #define P_APPINFO(info) std::cout << "[APPINFO] " << info << '\n';
#else
    #define P_APPINFO(info)  {while(0){}}
#endif

#if SHADERINFO
    #define P_SHADERINFO(info) std::cout << "[SHADERINFO] " << info << '\n';
#else
    #define P_SHADERINFO(info) {while(0){}}
#endif

#if MESHINFO
    #define P_MESHINFO(info) std::cout << "[MESHINFO] " << info << '\n';
#else
    #define P_SHADERINFO(info) {while(0){}}
#endif