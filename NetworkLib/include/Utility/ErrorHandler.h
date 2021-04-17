//---------------------------------------------------------------------------
//!	@file	ErrorHandle.h
//!	@brief	エラー処理 (仮)
//---------------------------------------------------------------------------
#pragma once
#include "Utility/Common.h"

class ErrorHandler : public std::exception
{
public:
    ErrorHandler(const char* msg = "") {
        printf_s("Error(%s)\n", msg);
    }

    ErrorHandler(const int errorCode,const char* msg = "")
    {
        printf_s("Error: %s, code: %d \n", msg, errorCode);
    }
};