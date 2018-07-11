//=============================================================================
//
// �^�C�g���̔w�i���� [game BG.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "game BG.h"

//=============================================================================
// �}�N����`
#define GAME_BG_TEX	"data/texture/BG/game bg.png"

//=============================================================================
// �v���g�^�C�v�錾
HRESULT MakeVertexGameBG(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̐錾
typedef struct
{
	bool		use;	// �g�p���Ă��邩

	float		Hight;	// ����
	float		Width;	// ��

	D3DXVECTOR2	Pos;	// �ʒu

}GAME_BG;
//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DGameBGTex = { NULL };		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DGameBGVtxBuf = NULL;				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
HRESULT InitGameBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAME_BG gameBG;

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, GAME_BG_TEX, &D3DGameBGTex);

	MakeVertexGameBG(pDevice);

	gameBG.use = true;

	gameBG.Hight = SCREEN_HEIGHT;
	gameBG.Width = SCREEN_WIDTH;

	gameBG.Pos = { 0.0,0.0 };

	return S_OK;
}

//=============================================================================
// �I������
void UninitGameBG(void)
{
	SAFE_RELEASE(D3DGameBGTex);

	SAFE_RELEASE(D3DGameBGVtxBuf);
}

//=============================================================================
// �ŐV����
void UpdateGameBG(void)
{

}

//=============================================================================
// �`�揈��
void DrawGameBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DGameBGVtxBuf, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DGameBGTex);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}


//=============================================================================
// ���_�̍쐬
HRESULT MakeVertexGameBG(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DGameBGVtxBuf,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DGameBGVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DGameBGVtxBuf->Unlock();
	}
}