//=============================================================================
//
// �o�b�N�O���E���h�̏��� [bg.h]
// Author : ���c����
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// �}�N����`
#define BG_00_FILE_PATH	("data/texture/BG/class_room.jpg")	//�e�N�X�`����
#define BG_01_FILE_PATH	("data/texture/BG/outside.jpg")		//�e�N�X�`����
#define BG_02_FILE_PATH	("data/texture/BG/dark_room.png")	//�e�N�X�`����
#define BG_SIZE_X		(SCREEN_WIDTH)					//�e�N�X�`���T�C�YX
#define BG_SIZE_Y		(SCREEN_HEIGHT)					//�e�N�X�`���T�C�YY
#define BG_POS_X		(SCREEN_WIDTH/2)					//�o�b�N�O���E���h�����ʒu
#define BG_POS_Y		(SCREEN_HEIGHT/2)					//�o�b�N�O���E���h�����ʒu

#define BG00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define BG00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define BG00_ANIM_PATTERN_NUM			(TEXTURE_BG_PATTERN_DIVIDE_X*TEXTURE_BG_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//�o�b�N�O���E���h�\����
typedef struct
{
	bool	use;
	POLY	poly;
}BG;

typedef enum
{
	BG_IDX_NULL = -1,
	BG_IDX_CLASS_ROOM,
	BG_IDX_OUTSIDE,
	BG_IDX_DARK_ROOM,
	BG_IDX_MAX
};
//=============================================================================
// �v���g�^�C�v�錾
void InitBg(void);
void UninitBg(void);
void DrawBg(void);
void SetBgTextureIdx(int no);
BG* GetBg(void);
#endif