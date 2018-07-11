//=============================================================================
//
// ライヴァルの処理 [rival.h]
// Author : 川井
//
//=============================================================================
#ifndef _RIVAL_H_
#define _RIVAL_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// マクロ定義

#define RIVAL_MAX (3)

enum
{
	RIVAL_01 = 0,
	RIVAL_02,
	RIVAL_03
};
//=============================================================================
// 構造体宣言

//ライヴァル構造体
typedef struct
{
	bool	use;
	POLY	poly;
	int		attraction;

	int		posid;

	float	alpha;
}RIVAL;

//=============================================================================
// プロトタイプ宣言
void InitRival(void);
void UninitRival(void);
void UpdateRival(void);
void DrawRival(void);
RIVAL *GetRival(int no);
#endif