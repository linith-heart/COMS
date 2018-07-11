//=============================================================================
//
// �e�L�X�g�̏��� [text.h]
// Author : ���c����
// ���ώ� : ���
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`

#define FONT_SIZE		(25)

#define TEXT_POS_X		(60)
#define TEXT_POS_Y		((SCREEN_HEIGHT/2) + 50)

#define TEXT_COLUMN_MAX	(MAX_PATH)
#define TEXT_ROW_MAX	(5)
#define TEXT_ROW_HEIGHT	(25)

#define TEST_SPEED		(3)

#define BUFF_COLUMN_MAX	(MAX_PATH)
#define BUFF_ROW_MAX	(MAX_PATH)

//=============================================================================
// �\���̐錾
//�e�L�X�g�\����
typedef struct
{
	char	textbuf[BUFF_ROW_MAX][BUFF_COLUMN_MAX];	// �o�b�t�@������
	char	textdis[TEXT_ROW_MAX][TEXT_COLUMN_MAX];	// �`�悷�镶����
	int		order;									// �\������
	int		currbufrow;								// �o�b�t�@�[�̓ǂݎ��ʒu

	int		rowmax;									// �ǂݍ���ł�s�̃}�b�N�X

	RECT	rectPos[TEXT_ROW_MAX];					// �e�L�X�g�̕`��ʒu
	int		drawcnt[TEXT_ROW_MAX];					// �`�悷��e�L�X�g�̐�
	int		drawcntmax[TEXT_ROW_MAX];				// �`�悷��e�L�X�g�̐�

	int		wait;									// �e�L�X�g�X�s�[�h(�҂�����)
}TEXT;


//=============================================================================
// �v���g�^�C�v�錾
void InitText(void);
void ClearText(char *text);
void UpdateText(void);
void DrawTextData(void); // DrawText�̓��C�u�����[�̃f�t�@�C���ł��邩��DrawTextData
void AdvanceText(void);
TEXT* GetText(void);
#endif