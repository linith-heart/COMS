//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
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
