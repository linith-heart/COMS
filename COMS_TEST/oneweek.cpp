//=============================================================================
//
// ウィークループモードの処理 [oneweek.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "fade.h"
#include "oneweek.h"
#include "Prologue.h"
#include "schedule.h"
#include "event.h"
#include "text.h"
#include "weekresult.h"
#include "bg.h"
#include "game.h"

#include "rival.h"
#include "text box.h"

#include "file data.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
WEEKLOOP g_weekloop;
//=============================================================================
// ウィークループモードの初期化処理
void InitWeekloop(void)
{
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;

	weekloop->week_cnt = 0;
	weekloop->status = WEEKLOOP_PROLOGUE;

	OpenEventFile(weekloop->week_cnt);
	//各Init呼び出し
	InitPrologue();
	InitSchedule();
	InitBg();
	InitEvent();
	InitText();
	InitTextBox();


	InitRival();
	InitWeekresult();

	SetPrologueScene();

	return;
}

//=============================================================================
// ウィークループモードの初期化処理
void UninitWeekloop(void)
{
	UninitBg();
	UninitPrologue();
	UninitSchedule();
	UninitEvent();
	UninitRival();
	UninitTextBox();
	UninitWeekresult();
}

//=============================================================================
// ウィークループモードの最新処理
void UpdateWeekloop(void)
{
	//ゲーム取得
	GAME* game = GetGame();
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;

	switch (weekloop->status)
	{
	case WEEKLOOP_PROLOGUE:
		UpdatePrologue();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_DAY_START:
		UpdateRival();
		UpdateSchedule();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_EVENT:
		UpdateRival();
		UpdateEvent();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_RESULT:
		UpdateWeekresult();
		UpdateText();
		UpdateTextBox();
		break;
	}

}

//=============================================================================
// ウィークループモードの描画処理
void DrawWeekloop(void)
{
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;
	//現在の週ループを判別し描画
	switch (weekloop->status)
	{
	case WEEKLOOP_PROLOGUE:
		DrawBg();
		DrawTextBox();
		DrawTextData();

		break;
	case WEEKLOOP_DAY_START:
		DrawBg();
		DrawRival();
		DrawTextBox();
		DrawTextData();

		break;
	case WEEKLOOP_EVENT:
		DrawBg();
		DrawEvent();
		DrawRival();
		DrawTextBox();
		DrawTextData();
		break;
	case WEEKLOOP_RESULT:
		DrawBg();
		DrawWeekresult();
		DrawTextBox();
		DrawTextData();
		break;
	}
}

//=============================================================================
// ウィークループゲット関数
WEEKLOOP* GetWeeekloop(void)
{
	return &g_weekloop;
}

//=============================================================================
// ウィークの更新
void AdvanceWeek(void)
{
	WEEKLOOP *weekloop = &g_weekloop;
	//ここで週のカウントアップを行う
	weekloop->week_cnt++;
	// 次の週のデータ読み込み
	OpenEventFile(weekloop->week_cnt);
	// 一日の始まりに設定
	SetScheduleScene();

}
