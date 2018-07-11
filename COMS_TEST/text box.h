//=============================================================================
//
// テキストボックスの処理 [text box.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// 構造体宣言

//テキストボックス構造体
typedef struct
{
	bool	use;
	POLY	poly;
	float	alpha;
	bool	display;
}TEXTBOX;

// プレスボタンの構造体
typedef struct
{
	bool	use;
	POLY	poly;
	float	alpha;
	bool	isfade;
}TEXTBOXPRESS;

//=============================================================================
// マクロ定義

typedef enum
{
	Idx_PRESS_SPACE = 0,
	Idx_PRESS_ENTER,
	Idx_PRESS_123,
	TEX_BOX_PRESS_MAX
};
//=============================================================================
// プロトタイプ宣言
void InitTextBox(void);
void UninitTextBox(void);
void UpdateTextBox(void);
void DrawTextBox(void);
void SetTextBoxPress(int no);
#endif