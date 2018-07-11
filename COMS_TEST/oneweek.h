//=============================================================================
//
// �E�B�[�N���[�v���[�h�̏��� [oneweek.h]
// Author : ���c����
//
//=============================================================================
#ifndef _ONE_WEEK_H_
#define _ONE_WEEK_H_

#include "main.h"


//=============================================================================
// �}�N����`
#define DAYS_TILL_WEEK_LOOP	(3)
//=============================================================================
// �\���̐錾
//�T���[�v�\����
typedef struct
{
	int status;			//���ݏT���[�v�̃��[�h�i�[�ϐ�
	int week_cnt;		//�T�o�ߐ��J�E���g�ϐ�
}WEEKLOOP;
//�T���[�v�����[�h�ԍ�
enum
{
	WEEKLOOP_NULL = -1,
	WEEKLOOP_PROLOGUE,
	WEEKLOOP_DAY_START,
	WEEKLOOP_EVENT,
	WEEKLOOP_RESULT,
	WEEKLOOP_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
void InitWeekloop(void);
void UninitWeekloop(void);
void UpdateWeekloop(void);
void DrawWeekloop(void);
WEEKLOOP* GetWeeekloop(void);
void AdvanceWeek(void);
#endif