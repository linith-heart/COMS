//=============================================================================
//
// �X�P�W���[������ [schedule.cpp]
// Author : ���c����
//
//=============================================================================

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "game.h"
#include "oneweek.h"
#include "input.h"
#include "schedule.h"
#include "event.h"

#include "rival.h"
#include "basic.h"
#include "file data.h"
#include "bg.h"
#include "text.h"
#include "text box.h"
/******************************************************************************
* �}�N����`
******************************************************************************/
#define SELECTION_POP_UP_VAL	(100.0f)

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
int g_selection = ACTION_1;


/******************************************************************************
* ����������
******************************************************************************/
void InitSchedule(void)
{



	return;
}
/******************************************************************************
* �I������
******************************************************************************/
void UninitSchedule(void)
{



}
/******************************************************************************
* �X�V�֐�
******************************************************************************/
void UpdateSchedule(void)
{
	//�|�C���^�擾
	WEEKLOOP* weekloop = GetWeeekloop();
	RIVAL *rival = GetRival(0);

	int check = g_selection;


	if (GetKeyboardTrigger(DIK_D))
	{
		g_selection--;
		if (g_selection <= ACTION_NULL)
			g_selection = ACTION_MAX - 1;
	}

	if (GetKeyboardTrigger(DIK_A))
	{
		g_selection++;
		if (g_selection >= ACTION_MAX)
			g_selection = ACTION_NULL + 1;
	}

	switch (g_selection) // �Z���N�V�����A�j���[�V����
	{
	case ACTION_1:
		rival->poly.Pos = SCREEN_POS_LEFT;
		rival->poly.Pos.y -= SELECTION_POP_UP_VAL;
		(rival + 1)->poly.Pos = SCREEN_POS_MIDDLE;
		(rival + 2)->poly.Pos = SCREEN_POS_RIGHT;
		break;
	case ACTION_2:
		rival->poly.Pos = SCREEN_POS_LEFT;
		(rival + 1)->poly.Pos = SCREEN_POS_MIDDLE;
		(rival + 1)->poly.Pos.y -= SELECTION_POP_UP_VAL;
		(rival + 2)->poly.Pos = SCREEN_POS_RIGHT;
		break;
	case ACTION_3:
		rival->poly.Pos = SCREEN_POS_LEFT;
		(rival + 1)->poly.Pos = SCREEN_POS_MIDDLE;
		(rival + 2)->poly.Pos = SCREEN_POS_RIGHT;
		(rival + 2)->poly.Pos.y -= SELECTION_POP_UP_VAL;
		break;
	}

	if (g_selection != check)	// �Z���N�V�������ς���Ă�����A�ʒu�ύX
	{
		SetBasic2DPos(&rival->poly);
		SetBasic2DPos(&(rival + 1)->poly);
		SetBasic2DPos(&(rival + 2)->poly);
	}


	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetEventScene(g_selection);
	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		AdvanceText();
	}
}


//=============================================================================
// �X�P�W���[����ʂɃZ�b�g
void SetScheduleScene(void)
{
	//�|�C���^�擾
	RIVAL *rival = GetRival(0);
	WEEKLOOP *week = GetWeeekloop();

	week->status = WEEKLOOP_DAY_START;

	SetBgTextureIdx(BG_IDX_CLASS_ROOM);

	SetTextBoxPress(Idx_PRESS_SPACE);

	for (int i = 0; i < RIVAL_MAX; i++)
		(rival + i)->use = true;


	LoadDayStartText();	// ����̎n�܂�̃e�L�X�g���o�b�t�@�[�ɏ�������

}