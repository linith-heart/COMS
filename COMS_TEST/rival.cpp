//=============================================================================
//
// ���C���@���̏��� [rival.cpp]
// Author : ���
//=============================================================================
#include "main.h"
#include "rival.h"
#include "basic.h"
#include "game.h"

#include "input.h"
//=============================================================================
// �}�N����`
#define RIVAL_01_FILE_PATH	"data/texture/chara/��{��.png"
#define RIVAL_02_FILE_PATH	"data/texture/chara/���e�ق���.png"
#define RIVAL_03_FILE_PATH	"data/texture/chara/�I�ꗜ��.png"


#define RIVAL_01_SIZE_X	(256)
#define RIVAL_01_SIZE_Y	(285)

#define RIVAL_02_SIZE_X	(256)
#define RIVAL_02_SIZE_Y	(285)

#define RIVAL_03_SIZE_X	(256)
#define RIVAL_03_SIZE_Y	(285)

#define RIVAL_ALPHA_RATE (0.02)
//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
RIVAL					g_rival[RIVAL_MAX];
LPDIRECT3DTEXTURE9		g_rivalTexture[RIVAL_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// ���C���@�����[�h�̏���������
void InitRival(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RIVAL *rival = &g_rival[0];


	D3DXCreateTextureFromFile(pDevice, RIVAL_01_FILE_PATH, &g_rivalTexture[RIVAL_01]);
	D3DXCreateTextureFromFile(pDevice, RIVAL_02_FILE_PATH, &g_rivalTexture[RIVAL_02]);
	D3DXCreateTextureFromFile(pDevice, RIVAL_03_FILE_PATH, &g_rivalTexture[RIVAL_03]);

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		rival->use = true;
		rival->attraction = 0.0f;

		rival->poly.TexId = i;

		switch (i)
		{
		case RIVAL_01:	// ��ʂ̉E����
			rival->poly.Pos = SCREEN_POS_LEFT;
			break;
		case RIVAL_02:	// ��ʂ̍�����
			rival->poly.Pos = SCREEN_POS_MIDDLE;
			break;
		case RIVAL_03:		// ��ʂ̐^�񒆂�
			rival->poly.Pos = SCREEN_POS_RIGHT;
			break;
		}
		rival->poly.Rot = 0.0f;
		
		rival->alpha = 0.0f;

		rival->posid = i;

		switch (i)		// �傫�����ʂɂ�����
		{
		case RIVAL_01:
			rival->poly.Size.x = RIVAL_01_SIZE_X;
			rival->poly.Size.y = RIVAL_01_SIZE_Y;
			break;
		case RIVAL_02:
			rival->poly.Size.x = RIVAL_02_SIZE_X;
			rival->poly.Size.y = RIVAL_02_SIZE_Y;
			break;
		case RIVAL_03:
			rival->poly.Size.x = RIVAL_03_SIZE_X;
			rival->poly.Size.y = RIVAL_03_SIZE_Y;
			break;
		}

		SetBasic2DVtxdata(pDevice, &rival->poly);

		SetBasic2DPos(&rival->poly);

		SetBasic2DCol(&rival->poly, 1.0f, 1.0f, 1.0f, rival->alpha);
	}

}

//=============================================================================
// ���C���@�����[�h�̏���������
void UninitRival(void)
{
	RIVAL *rival = &g_rival[0];
	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		SAFE_RELEASE(rival->poly.VtxBuff);

		SAFE_RELEASE(g_rivalTexture[i]);
	}
}

//=============================================================================
// ���C���@�����[�h�̍ŐV����
void UpdateRival(void)
{
	RIVAL *rival = &g_rival[0];

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		//============================================
		// �A���t�@�̐ݒ�
		float talpha = rival->alpha;
		if (rival->use)	// �\�����邩
		{
			if (rival->alpha < 1.0f)	// �����x���Ȃ���
			{
				rival->alpha += RIVAL_ALPHA_RATE;
			}
			else
				rival->alpha = 1.0f;


			//============================================
			// �\���ʒu�ݒ�
			D3DXVECTOR2 tcheck = rival->poly.Pos;	// ���ݒn�ۑ�

			//switch (rival->posid)
			//{
			//case RIGHT_POS_Idx:	// ��ʂ̉E����
			//	rival->poly.Pos = SCREEN_POS_RIGHT;
			//	break;
			//case LEFT_POS_Idx:	// ��ʂ̍�����
			//	rival->poly.Pos = SCREEN_POS_LEFT;
			//	break;
			//case MIDDLE_POS_Idx:		// ��ʂ̐^�񒆂�
			//	rival->poly.Pos = SCREEN_POS_MIDDLE;
			//	break;
			//}
			if (tcheck != rival->poly.Pos)			// �ۑ������ʒu�Ɣ�r
				SetBasic2DPos(&rival->poly);		// ���g���Ⴆ�Έʒu�ϊ�

		}
		else if (rival->alpha > 0.0f)	// �\�����Ȃ��A�܂������x��0�ł͂Ȃ�
		{
			rival->alpha -= RIVAL_ALPHA_RATE;
		}
		if (rival->alpha != talpha)
			SetBasic2DCol(&rival->poly, 1.0f, 1.0f, 1.0f, rival->alpha);


		// temp
		if (GetKeyboardTrigger(DIK_9))
		{
			if (rival->use)
				rival->use = false;
			else
				rival->use = true;
		}

	}

}

//=============================================================================
// ���C���@�����[�h�̕`�揈��
void DrawRival(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RIVAL *rival = &g_rival[0];

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		DrawBasic2DObject(pDevice, &rival->poly.VtxBuff, &g_rivalTexture[rival->poly.TexId]);
	}
}

//=============================================================================
// ���C���@���擾�֐�
RIVAL *GetRival(int no)
{
	return &g_rival[no];
}