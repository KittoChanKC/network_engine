//---------------------------------------------------------------------------
//!	@file	Player.cpp
//!	@brief	プレイヤー
//---------------------------------------------------------------------------
#include "Player.h"

Player::Player()
: _pos(300, 400)
, _enable(false)
{
}

Player::~Player()
{
}

ImVec2 Player::GetPos() const
{
    return _pos;
}

void Player::SetPos(f32 x, f32 y)
{
    _pos.x = x;
    _pos.y = y;
}

void Player::SetId(int id)
{
    this->_id = id;
}

bool Player::IsEnable()
{
    return _enable;
}

void Player::Enable()
{
    _enable = true;
}

void Player::Disable()
{
    _enable = false;
}

void Player::MoveX(f32 m)
{
    _pos.x += m;
}

void Player::MoveY(f32 m)
{
    _pos.y += m;
}
