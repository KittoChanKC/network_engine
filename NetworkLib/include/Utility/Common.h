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