//=============================================================================
//
// �e�L�X�g�{�b�N�X�̏��� [text box.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// �\���̐錾

//�e�L�X�g�{�b�N�X�\����
typedef struct
{
	bool	use;
	POLY	poly;
	float	alpha;
	bool	display;
}TEXTBOX;

// �v���X�{�^���̍\����
typedef struct
{
	bool	use;
	POLY	poly;
	float	alpha;
	bool	isfade;
}TEXTBOXPRESS;

//=============================================================================
// �}�N����`

typedef enum
{
	Idx_PRESS_SPACE = 0,
	Idx_PRESS_ENTER,
	Idx_PRESS_123,
	TEX_BOX_PRESS_MAX
};
//=============================================================================
// �v���g�^�C�v�錾
void InitTextBox(void);
void UninitTextBox(void);
void UpdateTextBox(void);
void DrawTextBox(void);
void SetTextBoxPress(int no);
#endif