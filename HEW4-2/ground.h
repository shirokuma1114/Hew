
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Ground_Initialize(void);
void Ground_Finalize(void);
void Ground_Update(void);
void Ground_Draw(void);

float SetGroundHit(int g_num);

HRESULT MakeVertexGround(int ground_num);
void MakeIdx(WORD *Idx, int g_num);
int Ground_Check();

class GROUND
{
public:
	D3DXMATRIX				g_mtxWorldGround;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3				g_posGround;				// �n�ʂ̈ʒu
	D3DXVECTOR3				g_rotGround;				// �n�ʂ̌���(��])
	D3DXVECTOR3				g_sclGround;				// �n�ʂ̑傫��(�X�P�[��)

	void SetGround_Pos(int ground_num, int ground_type, D3DXVECTOR3 x_z_pos);//�y�������F�u���b�N�ԍ��z�y�������F�u���b�N��ށz�y��O�����F�u���b�N���W�z


	int		ground_type;	//�u���b�N�̎��

	//Max,Min���W
	D3DXVECTOR3	Point0;
	D3DXVECTOR3	Point1;
	D3DXVECTOR3	Point2;
	D3DXVECTOR3	Point3;

	GROUND() {};
	~GROUND() {};

	VERTEX_3D *LookVtx;//�|�C���^�̃|�C���^
	int		  *LookIdxNum;//�C���f�b�N�X�̃|�C���^
};


//�u���b�N�����֐�
void Block0_Stage(VERTEX_3D *pvtx, int g_num);
void Block1_Stage(VERTEX_3D *pvtx, int g_num);
void Block2_Stage(VERTEX_3D *pvtx, int g_num);
void Block3_Stage(VERTEX_3D *pvtx, int g_num);
void Block4_Stage(VERTEX_3D *pvtx, int g_num);
void Block5_Stage(VERTEX_3D *pvtx, int g_num);
void Block6_Stage(VERTEX_3D *pvtx, int g_num);
void Block7_Stage(VERTEX_3D *pvtx, int g_num);
void Block8_Stage(VERTEX_3D *pvtx, int g_num);


//void Block_Stage(VERTEX_3D *pvtx, int g_num, D3DXVECTOR3 pos_algorithm, D3DXVECTOR3 texture);