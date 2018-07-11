//=============================================================================
//
// スケジュール処理 [schedule.cpp]
// Author : 藤田高輔
//
//=============================================================================

/*******************************************************************************
* インクルードファイル
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
* マクロ定義
******************************************************************************/
#define SELECTION_POP_UP_VAL	(100.0f)

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/

/******************************************************************************
* グローバル変数
******************************************************************************/
int g_selection = ACTION_1;


/******************************************************************************
* 初期化処理
******************************************************************************/
void InitSchedule(void)
{



	return;
}
/******************************************************************************
* 終了処理
******************************************************************************/
void UninitSchedule(void)
{



}
/******************************************************************************
* 更新関数
******************************************************************************/
void UpdateSchedule(void)
{
	//ポインタ取得
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

	switch (g_selection) // セレクションアニメーション
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

	if (g_selection != check)	// セレクションが変わっていたら、位置変更
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
// スケジュール画面にセット
void SetScheduleScene(void)
{
	//ポインタ取得
	RIVAL *rival = GetRival(0);
	WEEKLOOP *week = GetWeeekloop();

	week->status = WEEKLOOP_DAY_START;

	SetBgTextureIdx(BG_IDX_CLASS_ROOM);

	SetTextBoxPress(Idx_PRESS_SPACE);

	for (int i = 0; i < RIVAL_MAX; i++)
		(rival + i)->use = true;


	LoadDayStartText();	// 一日の始まりのテキストをバッファーに書き込む

}