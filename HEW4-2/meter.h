#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeter(void);
void UninitMeter(void);
void UpdateMeter(void);
void DrawMeter(void);

void ChangeMeter(int nValue);
void ResetMeter(int nMeter = 0);
