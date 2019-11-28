/*
#include "Meter.h"
#include "myDirect3D.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************��
#define	Meter_SIZE_X		Texture_GetWidth(TEXTURE_INDEX_Meter)							// �X�R�A�̐����̕�
#define	Meter_SIZE_Y		Texture_GetHeight(TEXTURE_INDEX_Meter)							// �X�R�A�̐����̍���
#define	Meter_INTERVAL_X	(0.0f)															// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(8)																// �X�R�A�̌���

#define	Meter_POS_X			(SCREEN_WIDTH - (Meter_INTERVAL_X + Meter_SIZE_X) * NUM_PLACE - 10.0f)	// �X�R�A�̕\����ʒu�w���W
#define	Meter_POS_Y			(10.0f)																	// �X�R�A�̕\����ʒu�x���W

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice);
void SetTextureMeter(int nIdx, int nNumber);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMeter = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeter = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3				g_posMeter;				// �ʒu
D3DXVECTOR3				g_rotMeter;				// ����

int						g_nMeter;				// �X�R�A

												//=============================================================================
												// ����������
												//=============================================================================
HRESULT InitMeter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �ʒu�E�����̏�����
	g_posMeter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�R�A�̏�����
	g_nMeter = 0;

	// ���_���̍쐬
	MakeVertexMeter(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeter(void)
{
	if (g_pTextureMeter != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureMeter->Release();
		g_pTextureMeter = NULL;
	}

	if (g_pVtxBuffMeter != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffMeter->Release();
		g_pVtxBuffMeter = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeter(void)
{
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int nNumber;

		nNumber = (g_nMeter % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureMeter(nCntPlace, nNumber);


		if (Keyboard_IsPress(DIK_UP))
		{
			g_nMeter++;
		}
		if (Keyboard_IsPress(DIK_DOWN))
		{
			g_nMeter--;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffMeter, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_Meter));

	// �|���S���̕`��
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * NUM_PLACE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pVtxBuffMeter,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D* pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(Meter_POS_X + nCntPlace * (Meter_SIZE_X + Meter_INTERVAL_X), Meter_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Meter_POS_X + nCntPlace * (Meter_INTERVAL_X + Meter_SIZE_X) + Meter_SIZE_X, Meter_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Meter_POS_X + nCntPlace * (Meter_SIZE_X + Meter_INTERVAL_X), Meter_POS_Y + Meter_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Meter_POS_X + nCntPlace * (Meter_INTERVAL_X + Meter_SIZE_X) + Meter_SIZE_X, Meter_POS_Y + Meter_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffMeter->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureMeter(int nIdx, int nNumber)
{
	VERTEX_2D* pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffMeter->Unlock();
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeMeter(int nValue)
{
	g_nMeter += nValue;
	if (g_nMeter < 0)
	{
		g_nMeter = 0;
	}
	else if (g_nMeter >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
	{
		g_nMeter = (int)(powf(10.0f, (float)(NUM_PLACE + 1))) - 1;
	}
}

//=============================================================================
// �X�R�A�̃��Z�b�g
//=============================================================================
void ResetMeter(int nValue)
{
	g_nMeter = nValue;
}
*/