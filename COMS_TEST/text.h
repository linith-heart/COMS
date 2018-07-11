//=============================================================================
//
// テキストの処理 [text.h]
// Author : 藤田高輔
// 改変者 : 川井
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義

#define FONT_SIZE		(25)

#define TEXT_POS_X		(60)
#define TEXT_POS_Y		((SCREEN_HEIGHT/2) + 50)

#define TEXT_COLUMN_MAX	(MAX_PATH)
#define TEXT_ROW_MAX	(5)
#define TEXT_ROW_HEIGHT	(25)

#define TEST_SPEED		(3)

#define BUFF_COLUMN_MAX	(MAX_PATH)
#define BUFF_ROW_MAX	(MAX_PATH)

//=============================================================================
// 構造体宣言
//テキスト構造体
typedef struct
{
	char	textbuf[BUFF_ROW_MAX][BUFF_COLUMN_MAX];	// バッファ文字列
	char	textdis[TEXT_ROW_MAX][TEXT_COLUMN_MAX];	// 描画する文字列
	int		order;									// 表示順番
	int		currbufrow;								// バッファーの読み取り位置

	int		rowmax;									// 読み込んでる行のマックス

	RECT	rectPos[TEXT_ROW_MAX];					// テキストの描画位置
	int		drawcnt[TEXT_ROW_MAX];					// 描画するテキストの数
	int		drawcntmax[TEXT_ROW_MAX];				// 描画するテキストの数

	int		wait;									// テキストスピード(待ち時間)
}TEXT;


//=============================================================================
// プロトタイプ宣言
void InitText(void);
void ClearText(char *text);
void UpdateText(void);
void DrawTextData(void); // DrawTextはライブラリーのデファインであるからDrawTextData
void AdvanceText(void);
TEXT* GetText(void);
#endif