//---------------------------------------------------------------------------
//!	@file	Player.h
//!	@brief	プレイヤー
//---------------------------------------------------------------------------
#pragma once
#include <imgui.h>

class Player
{
public:
    Player();
    ~Player();

    ImVec2 GetPos() const;

    //void Move();
    void MoveX(f32 m);
    void MoveY(f32 m);

    void SetPos(f32 x, f32 y);
    void SetId(int id);
    int GetId() { return _id; };


    bool IsEnable();
    void Enable();
    void Disable();
private:
    //float2 pos;
    ImVec2 _pos;
    bool   _enable;

    int _id;
};