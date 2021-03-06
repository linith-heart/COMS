//=============================================================================
//
// スケジュールヘッダー [schedule.h]
// Author : 藤田高輔
//
//=============================================================================

/*******************************************************************************
* 多重インクルードの防止
*******************************************************************************/
#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* 構造体定義
*******************************************************************************/
enum
{
	ACTION_NULL = -1,
	ACTION_1,
	ACTION_2,
	ACTION_3,
	ACTION_MAX
};

/******************************************************************************
* プロトタイプ宣言
//****************************************************************************/
void InitSchedule(void);
void UninitSchedule(void);
void UpdateSchedule(void);
void SetScheduleScene(void);
#endif
