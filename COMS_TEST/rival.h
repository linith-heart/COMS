//=============================================================================
//
// ���C���@���̏��� [rival.h]
// Author : ���
//
//=============================================================================
#ifndef _RIVAL_H_
#define _RIVAL_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// �}�N����`

#define RIVAL_MAX (3)

enum
{
	RIVAL_01 = 0,
	RIVAL_02,
	RIVAL_03
};
//=============================================================================
// �\���̐錾

//���C���@���\����
typedef struct
{
	bool	use;
	POLY	poly;
	int		attraction;

	int		posid;

	float	alpha;
}RIVAL;

//=============================================================================
// �v���g�^�C�v�錾
void InitRival(void);
void UninitRival(void);
void UpdateRival(void);
void DrawRival(void);
RIVAL *GetRival(int no);
#endif