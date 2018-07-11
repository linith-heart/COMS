//=============================================================================
//
// �^�[�Q�b�g�̏��� [terget.h]
// Author : ���c����
//
//=============================================================================
#ifndef _TERGET_H_
#define _TERGET_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`
#define TERGET_MAX	(1)											//�^�[�Q�b�g�ő吔
#define TERGET00_TEXTURE	("COMS/data/texture/chara/???.png")	//�e�N�X�`����
#define TERGET00_TEXTURE_SIZE_X		(242.0f)	//�e�N�X�`���T�C�YX
#define TERGET00_TEXTURE_SIZE_Y		(426.0f)	//�e�N�X�`���T�C�YY
#define TERGET00_FIRST_POS_X		(0.0f)		//�^�[�Q�b�g�����ʒu
#define TERGET00_FIRST_POS_Y		(0.0f)		//�^�[�Q�b�g�����ʒu

#define TERGET00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define TERGET00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define TERGET00_ANIM_PATTERN_NUM			(TEXTURE_TERGET_PATTERN_DIVIDE_X*TEXTURE_TERGET_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//�^�[�Q�b�g�\����
typedef struct
{

}TERGET;

//=============================================================================
// �v���g�^�C�v�錾
void InitTerget(int oldMode);
void UninitTerget(int oldMode);
void UpdateTerget(void);
void DrawTerget(void);
TERGET* GetTerget(void);
#endif