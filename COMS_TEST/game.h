//=============================================================================
//
// �Q�[�����[�h�̏��� [game.h]
// Author : ���ꐶ
// ���ώ� : ���c����
// ���ϓ��e : �Q�[�������̒ǉ��Ȃ�
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//=============================================================================
// �}�N����`
#define WEEK_NUM_PROTO_MAX		(5)		//�v���g�^�C�v��Փx�ɂ�����ő�̏T��


#define SCREEN_POS_RIGHT	(D3DXVECTOR2(SCREEN_WIDTH/4,(SCREEN_HEIGHT/2)))
#define SCREEN_POS_LEFT		(D3DXVECTOR2((SCREEN_WIDTH/4) * 3,(SCREEN_HEIGHT/2)))
#define SCREEN_POS_MIDDLE	(D3DXVECTOR2(SCREEN_WIDTH/2,(SCREEN_HEIGHT/2)))

//=============================================================================
// �\���̐錾
typedef struct //�Q�[���{�҂𐧌䂷����́i�o�ߏT���A��Փx�j
{
	int difficult;	//�I�����ꂽ��Փx
}GAME;

enum
{
	RIGHT_POS_Idx = 0,
	LEFT_POS_Idx,
	MIDDLE_POS_Idx,
};


//��Փx�̃^�C�v
enum
{
	DIFFICULT_NULL = -1,	//��Փx���I������ĂȂ����
	DIFFICULT_PROTO,		//�v���g�^�C�v
	DIFFICULT_MAX	//��Փx�ő吔
};

//�L�����N�^�[�ԍ���
enum
{
	IDX_PLAYER = 0,
	IDX_TERGET,
	IDX_RIVAL00,
	IDX_RIVAL01,
	IDX_RIVAL02,
	IDX_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetDifficult(int difficult);
GAME* GetGame(void);
#endif