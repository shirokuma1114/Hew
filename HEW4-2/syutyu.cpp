#include "main.h"
#include "texture.h"
#include <d3d9.h>
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "syutyu.h"

bool zaitsu = false;

void Syutyu_Initialize(void)
{
}

void Syutyu_Finalize(void)
{
}

void Syutyu_Update(void)
{
	zaitsu = false;
	
	if (Keyboard_IsPress(DIK_UP))
	{
		//g_nSyutyu++;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		//g_nSyutyu--;
	}
	if (Keyboard_IsPress(DIK_P))
	{
		zaitsu = true;
	}



	
}

void Syutyu_Draw(void)
{
	if (zaitsu)
	{

	Sprite_Draw(TEXTURE_INDEX_EFFECT_SPEED, 0.0f, 0.0f,0,0,1280,1280,0, 0, 1.0f, 0.6f,0);
	}
}