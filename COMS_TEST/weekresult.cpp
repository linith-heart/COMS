//=============================================================================
//
// ウィークリザルト処理 [dayresult.cpp]
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
#include "weekresult.h"
#include "debugproc.h"

#include "rival.h"
#include "file data.h"
#include "text.h"
#include "text box.h"
#include "bg.h"
#include "schedule.h"
#include "fade.h"
/******************************************************************************
* マクロ定義
******************************************************************************/

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/

/******************************************************************************
* グローバル変数
******************************************************************************/
WEEKRESULT g_weekresult;		//グローバル変数（複数作成必要なし)

/******************************************************************************
* 初期化処理
******************************************************************************/
void InitWeekresult(void)
{


	return;
}
/******************************************************************************
* 終了処理
******************************************************************************/
void UninitWeekresult(void)
{

}
/******************************************************************************
* 更新関数
******************************************************************************/
void UpdateWeekresult(void)
{
	//ポインタ取得
	WEEKRESULT* weekresult = GetWeekresult();
	WEEKLOOP* weekloop = GetWeeekloop();

	//エンターで遷移＆週のカウントを進める
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (weekloop->week_cnt + 1 < DAYS_TILL_WEEK_LOOP)
			AdvanceWeek();
		else
			SetFade(FADE_OUT, MODE_RESULT);

	}

	//ページ送り
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		AdvanceText();
	}

	//デバッグ文字
#ifdef _DEBUG
	//PrintDebugProc("エンターで進む\n");
#endif
}

/******************************************************************************
* 描画関数
******************************************************************************/
void DrawWeekresult(void)
{

}

/******************************************************************************
* 描画関数
******************************************************************************/
WEEKRESULT* GetWeekresult(void)
{
	return &g_weekresult;
}
void SetWeekresult(int no)
{
	//ポインタ取得
	RIVAL *rival = GetRival(0);
	WEEKLOOP *week = GetWeeekloop();
	week->status = WEEKLOOP_RESULT;

	SetBgTextureIdx(BG_IDX_DARK_ROOM);

	SetTextBoxPress(Idx_PRESS_SPACE);

	for (int i = 0; i < RIVAL_MAX; i++)
		(rival + i)->use = false;

	LoadResultText(no);	// リザルトのテキストをバッファーに書き込む

}