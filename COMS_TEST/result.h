//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
int GetChangeResultBG(void);

enum
{
	HAPPYEND = 0,
	NORMALEND,
	BADEND,
	END_MAX
};

#endif
