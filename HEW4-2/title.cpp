#include "input.h"
#include "main.h"
#include "scene.h"
#include "texture.h"
#include "fade.h"
#include <d3d9.h>
#include "sprite.h"



static bool g_bEnd = false;


void Title_Initialize(void)
{
	g_bEnd = false;
}

void Title_Finalize(void)
{
}

void Title_Update(void)
{

	if (Keyboard_IsTrigger(DIK_SPACE)) {
		Scene_Change(SCENE_INDEX_GAME);
	}
}

void Title_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_BG, 0.0f, 0.0f);
	Sprite_Draw(TEXTURE_INDEX_TITLE, 260.0f, 100.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	Sprite_Draw(TEXTURE_INDEX_PRESS, 480.0f, 420.0f);
}
