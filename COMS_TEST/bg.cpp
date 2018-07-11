//=============================================================================
//
// �o�b�N�O���E���h�̏��� [bg.cpp]
// Author : ���c����
//=============================================================================
#include "main.h"
#include "bg.h"

#include "basic.h"
//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�	
BG						g_bg;						// �\����
LPDIRECT3DTEXTURE9		g_BgTexture[BG_IDX_MAX];	// �e�N�X�`��

//=============================================================================
// �o�b�N�O���E���h���[�h�̏���������
void InitBg(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bg�̐擪�A�h���X�擾
	BG *bg = &g_bg;

	// �e�N�X�`���[�ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_00_FILE_PATH, &g_BgTexture[BG_IDX_CLASS_ROOM]);
	D3DXCreateTextureFromFile(pDevice, BG_01_FILE_PATH, &g_BgTexture[BG_IDX_OUTSIDE]);
	D3DXCreateTextureFromFile(pDevice, BG_02_FILE_PATH, &g_BgTexture[BG_IDX_DARK_ROOM]);

	bg->use = true;
	// �ʒu
	bg->poly.Pos.x = BG_POS_X;
	bg->poly.Pos.y = BG_POS_Y;

	// �傫��
	bg->poly.Size.x = BG_SIZE_X;
	bg->poly.Size.y = BG_SIZE_Y;

	// ��]
	bg->poly.Rot = 0.0f;
	
	// �e�N�X�`���[�̃C���f�b�N�X�ԍ�
	bg->poly.TexId = BG_IDX_CLASS_ROOM;

	// ���@�[�e�b�N�X�o�b�t�@�̐ݒ�
	SetBasic2DVtxdata(pDevice, &bg->poly);

	// �ʒu�ݒ�
	SetBasic2DPos(&bg->poly);

	// �F�̐ݒ�
	SetBasic2DCol(&bg->poly, 1.0f, 1.0f, 1.0f, 1.0f);

	return;
}

//=============================================================================
// �o�b�N�O���E���h���[�h�̏���������
void UninitBg(void)
{
	BG *bg = &g_bg;

	SAFE_RELEASE(bg->poly.VtxBuff);

	for (int i = 0; i < BG_IDX_MAX; i++)
	{	// �e�N�X�`���[�̃����[�X
		SAFE_RELEASE(g_BgTexture[i])
	}
}

//=============================================================================
// �o�b�N�O���E���h���[�h�̕`�揈��
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG* bg = &g_bg;
	//�X�V���[�v
	if (bg->use == true)
	{	// �e�N�X�`���[�̕`��
		DrawBasic2DObject(pDevice, &bg->poly.VtxBuff,&g_BgTexture[bg->poly.TexId]);
	}
}

//=============================================================================
// �e�N�X�`���[�ύX����
void SetBgTextureIdx(int no)
{
	BG* bg = &g_bg;
	bg->poly.TexId = no;
}

//=============================================================================
// BG�Q�b�g�֐�
BG* GetBg(void)
{
	return &g_bg;
}