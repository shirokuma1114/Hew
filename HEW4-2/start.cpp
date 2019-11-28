#include "Start.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "camera.h"
#include "debugproc.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE		(1.0f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��

#define	Start_WIDTH		(15.0f)						// �n�ʂ̕�(X����)
#define	Start_DEPTH		(15.0f)						// �n�ʂ̉��s(Z����)
#define	Start_HEIGHT	(15.0f)						// �n�ʂ̍���(Y����)

#define Start_ANGLE		(8)
#define Start_NUM		(5)

#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}//���S�ɉ������
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldStart;		// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posStart;				// �n�ʂ̈ʒu
D3DXVECTOR3				g_rotStart;				// �n�ʂ̌���(��])
D3DXVECTOR3				g_sclStart;				// �n�ʂ̑傫��(�X�P�[��)
bool					isUse=true;				// �X�^�[�g�̎g�p����


static bool Hit = false;

static LPDIRECT3DDEVICE9		pDevice;
static DWORD					dwNumMaterials = 0;
static LPD3DXMESH				pMesh = NULL;				//���b�V��
static D3DMATERIAL9*			pMaterials = NULL;			//�}�e���A��
static LPDIRECT3DTEXTURE9*		pTextures = NULL;			//�e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Collision_Start();

//=============================================================================
// ����������
//=============================================================================
HRESULT Start_Initialize(void)
{
	pDevice = GetD3DDevice();

	// X�t�@�C�����烁�b�V�������[�h���� 
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("start.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMaterials = new D3DMATERIAL9[dwNumMaterials];
	pTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];

	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		pMaterials[i] = d3dxMaterials[i].MatD3D;
		pMaterials[i].Ambient = pMaterials[i].Diffuse;
		pTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�

	g_posStart = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	g_rotStart = D3DXVECTOR3(D3DX_PI / 6, 0.0f, 0.0f);
	g_sclStart = D3DXVECTOR3(15.0f, 15.0f, 15.0f);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Start_Finalize(void)
{
	if (g_pVtxBuffStart != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffStart->Release();
		g_pVtxBuffStart = NULL;
	}

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pDevice);
}

//=============================================================================
// �X�V����
//=============================================================================
void Start_Update(void)
{
	Collision_Start();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Start_Draw(void)
{
	//�f�o�C�X�������Ȃ�I��
	if (NULL == pDevice) { return; }

	D3DXMATRIXA16 mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldStart);

	// �X�P�[�����]
	D3DXMatrixScaling(&mtxScl, g_sclStart.x, g_sclStart.y, g_sclStart.z);
	D3DXMatrixMultiply(&g_mtxWorldStart, &g_mtxWorldStart, &mtxScl);

	// ��]�𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotStart.y, g_rotStart.x, g_rotStart.z);
	D3DXMatrixMultiply(&g_mtxWorldStart, &g_mtxWorldStart, &mtxRot);

	// �ړ��𔽓]
	D3DXMatrixTranslation(&mtxTranslate, g_posStart.x, g_posStart.y, g_posStart.z);
	D3DXMatrixMultiply(&g_mtxWorldStart, &g_mtxWorldStart, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldStart);

	//���_�V�F�[�_���Z�b�g(�g��Ȃ��ꍇ��NULL)
	GetD3DDevice()->SetVertexShader(NULL);

	//���_�t�H�[�}�b�g���Z�b�g
	GetD3DDevice()->SetFVF(pMesh->GetFVF());

	//�����ɏ������e������
	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		pDevice->SetMaterial(&pMaterials[i]);
		pDevice->SetTexture(0, pTextures[i]);
		pMesh->DrawSubset(i);
	}
}

// �X�^�[�g�̓����蔻��
void Collision_Start()
{
	D3DXVECTOR3 Player = GetPlayer_Pos();
	D3DXVECTOR3 dst1(Player.x, Player.y, Player.z);

	Hit = false;
	D3DXVECTOR3 dst2(g_posStart.x, g_posStart.y, g_posStart.z);
	D3DXVECTOR3 distance;
	distance = dst2 - dst1;
	float length = D3DXVec3Length(&distance);
	float size = 15;
	if (length < size)
	{
		Hit = true;
		isUse = false;
		return;

	}
	return;
}

bool Get_StartHit()
{
	return Hit;
}