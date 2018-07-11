//=============================================================================
//
// �^�C�g���̔w�i���� [title BG.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "title BG.h"

//=============================================================================
// �}�N����`
#define TITLE_BG_TEX	"data/texture/BG/Spring.jpg"

//=============================================================================
// �v���g�^�C�v�錾
HRESULT MakeVertexTitleBG(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̐錾
typedef struct
{
	bool		use;	// �g�p���Ă��邩
	int			Idx;	// �C���f�b�N�X�ԍ��@�@����Ȃ��H

	float		Hight;	// ����
	float		Width;	// ��

	D3DXVECTOR2	Pos;	// �ʒu
	D3DXCOLOR	Col;	// �F�@�@����Ȃ��H

}TITLE_BG;
//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTitleBGTex = { NULL };		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DTitleBGVtxBuf = NULL;				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
HRESULT InitTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE_BG titleBG;

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TITLE_BG_TEX, &D3DTitleBGTex);

	MakeVertexTitleBG(pDevice);

	titleBG.use = true;
	titleBG.Idx = 0;	// ����Ȃ��H

	titleBG.Hight = SCREEN_HEIGHT;
	titleBG.Width = SCREEN_WIDTH;

	titleBG.Pos = { 0.0,0.0 };

	return S_OK;
}

//=============================================================================
// �I������
void UninitTitleBG(void)
{
	SAFE_RELEASE(D3DTitleBGTex);

	SAFE_RELEASE(D3DTitleBGVtxBuf);
}

//=============================================================================
// �ŐV����
void UpdateTitleBG(void)
{

}

//=============================================================================
// �`�揈��
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DTitleBGVtxBuf, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTitleBGTex);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}


//=============================================================================
// ���_�̍쐬
HRESULT MakeVertexTitleBG(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DTitleBGVtxBuf,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DTitleBGVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

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
		D3DTitleBGVtxBuf->Unlock();
	}
}