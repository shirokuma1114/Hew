#pragma once

#include "main.h"

#define GRAVITY		(2.0f)			// �d��
#define MAXSPEED	(200.0f)		// �ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Player_Initialize(void);
void Player_Finalize(void);
void Player_Update(void);
void Player_Draw(void);
D3DXVECTOR3 GetPlayer_Pos();
D3DXVECTOR3 GetPlayer_Rot();
D3DXVECTOR3 GetNormalPlayer_Pos();
float GetMeter_Pos();
