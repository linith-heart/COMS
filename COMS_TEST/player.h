//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : ���c����
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`
#define PLAYER_MAX	(1)											//�v���C���[�ő吔
#define PLAYER00_TEXTURE	("COMS/data/texture/chara/��{��.png")	//�e�N�X�`����
#define PLAYER00_TEXTURE_SIZE_X		(242.0f)	//�e�N�X�`���T�C�YX
#define PLAYER00_TEXTURE_SIZE_Y		(426.0f)	//�e�N�X�`���T�C�YY
#define PLAYER00_FIRST_POS_X		(0.0f)		//�v���C���[�����ʒu
#define PLAYER00_FIRST_POS_Y		(0.0f)		//�v���C���[�����ʒu

#define PLAYER00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define PLAYER00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define PLAYER00_ANIM_PATTERN_NUM			(TEXTURE_PLAYER_PATTERN_DIVIDE_X*TEXTURE_PLAYER_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//�v���C���[�\����
typedef struct
{
	int attraction; // will use later
}PLAYER;

//=============================================================================
// �v���g�^�C�v�錾
void InitPlayer(int oldMode);
void UninitPlayer(int oldMode);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif