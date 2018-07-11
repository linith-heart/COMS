//=============================================================================
//
// ウィークリザルトヘッダー [dayresult.h]
// Author : 藤田高輔
//
//=============================================================================

/*******************************************************************************
* 多重インクルードの防止
*******************************************************************************/
#ifndef _WEEKRESULT_H_
#define _WEEKRESULT_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct
{

}WEEKRESULT;


/******************************************************************************
* プロトタイプ宣言
//****************************************************************************/
void InitWeekresult(void);
void UninitWeekresult(void);
void UpdateWeekresult(void);
void DrawWeekresult(void);
WEEKRESULT* GetWeekresult(void);
void SetWeekresult(int no);
/*******************************************************************************
* 多重インクルード防止終了
*******************************************************************************/
#endif
