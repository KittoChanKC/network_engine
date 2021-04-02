#pragma once

#ifdef _WIN32
#include <Winsock2.h>   // must include before windows.h
#include <Windows.h>
#include <conio.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>      // sleep()
#include <arpa/inet.h>   // htons
#include <sys/socket.h>
#endif

#include <stdint.h>
#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <fmt/format.h>

//struct float2
//{
//    f32 _x;
//    f32 _y;
//
//    float2(f32 x = 0.0f,f32 y = 0.0f) {
//        _x = x;
//        _y = y;
//    }
//};