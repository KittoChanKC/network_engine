﻿//---------------------------------------------------------------------------
//!	@file	Main.cpp
//!	@brief	クライアント側のメインプログラム
//!         自分のネットワークエンジンの使い方忘れないように
//! 　　　　 簡単なサンプルを書きました
//!         UIは SDL2 と Imgui　をもとに組み立てます
//---------------------------------------------------------------------------

#include "MyApp.h"
int main()
{
    MyApp::Instance()->run();
    return 0;
}