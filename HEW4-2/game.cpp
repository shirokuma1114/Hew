#include <time.h>
#include "myDirect3D.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "meter.h"
#include "ground.h"
#include "scene.h"
#include "fade.h"
#include "Player.h"
#include "grid.h"
#include "drink.h"
#include "start.h"


typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,
	PHASE_INDEX_PLAYER_MUTEKI,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;
static int g_GameFrameCount;

static int g_Score = 0;// �_��
static int g_KillCount = 0;


static bool Game_EndCheck(void);



void Game_Initialize(void)
{
	// �J�����̏���������
	Camera_Initialize();
	//Camera2_Initialize();

	// ���C�g�̏���������
	Light_Initialize();

	//�O���b�h�̏���������
	Grid_Initialize();

	// �v���C���[
	Player_Initialize();

	// �O���E���h
	Ground_Initialize();

	// �X�^�[�g
	//Start_Initialize();

	// �h�����N
	Drink_Initialize();

	// �X�R�A
	InitScore();

	// ���[�^�[
	Meter_Initialize();
}

void Game_Finalize(void)
{
	// �J�����̏I������
	Camera_Finalize();
	//Camera2_Finalize();

	// ���C�g�̏I������
	Light_Finalize();

	// �O���b�h�̏I��
	Grid_Finalize();

	// �v���C���[
	Player_Finalize();

	// �O���E���h
	Ground_Finalize();

	// �X�^�[�g
	//Start_Finalize();

	// �h�����N
	Drink_Finalize();

	// �X�R�A
	UninitScore();

	// ���[�^�[
	Meter_Finalize();
}

void Game_Update(void)
{
	// �J�����̍X�V����
	Camera_Update();
	//Camera2_Update();

	// ���C�g�̍X�V����
	Light_Update();

	//�O���b�h��
	Grid_Update();

	// �v���C���[
	Player_Update();

	// �O���E���h
	Ground_Update();

	// �X�^�[�g
	//Start_Update();

	// �h�����N
	Drink_Update();

	// �X�R�A
	UpdateScore();	

	// ���[�^�[
	Meter_Update();

	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		Scene_Change(SCENE_INDEX_RESULT);
	}

}

void Game_Draw(void)
{
	// �J�����̐ݒ�
	Camera_SetCamera();
	//Camera2_SetCamera();

	//�O���b�h�̕`��
	Grid_Draw();

	// �v���C���[
	Player_Draw();

	// �O���E���h
	Ground_Draw();

	// �X�^�[�g
	//Start_Draw();

	// �h�����N
	Drink_Draw();

	// �X�R�A
	DrawScore();

	// ���[�^�[
	Meter_Draw();
}



bool Game_EndCheck(void)
{

}



void Game_AddScore(int score)
{
	//g_Score += score;
}

void Game_AddKillCount()
{
	//g_KillCount += 1;
}
