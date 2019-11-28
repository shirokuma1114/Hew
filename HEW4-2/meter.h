#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeter(void);
void UninitMeter(void);
void UpdateMeter(void);
void DrawMeter(void);

void ChangeMeter(int nValue);
void ResetMeter(int nMeter = 0);
