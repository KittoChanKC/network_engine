//---------------------------------------------------------------------------
//!	@file	ErrorHandle.h
//!	@brief	エラー処理 (仮)
//---------------------------------------------------------------------------
#pragma once

class ErrorHandler : public std::exception
{
public:
    ErrorHandler(const char* msg = "") {
        printf_s("Error(%s)\n", msg);
    }
};