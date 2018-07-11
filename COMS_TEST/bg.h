//=============================================================================
//
// バックグラウンドの処理 [bg.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "basic.h"


//=============================================================================
// マクロ定義
#define BG_00_FILE_PATH	("data/texture/BG/class_room.jpg")	//テクスチャ名
#define BG_01_FILE_PATH	("data/texture/BG/outside.jpg")		//テクスチャ名
#define BG_02_FILE_PATH	("data/texture/BG/dark_room.png")	//テクスチャ名
#define BG_SIZE_X		(SCREEN_WIDTH)					//テクスチャサイズX
#define BG_SIZE_Y		(SCREEN_HEIGHT)					//テクスチャサイズY
#define BG_POS_X		(SCREEN_WIDTH/2)					//バックグラウンド初期位置
#define BG_POS_Y		(SCREEN_HEIGHT/2)					//バックグラウンド初期位置

#define BG00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define BG00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define BG00_ANIM_PATTERN_NUM			(TEXTURE_BG_PATTERN_DIVIDE_X*TEXTURE_BG_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//バックグラウンド構造体
typedef struct
{
	bool	use;
	POLY	poly;
}BG;

typedef enum
{
	BG_IDX_NULL = -1,
	BG_IDX_CLASS_ROOM,
	BG_IDX_OUTSIDE,
	BG_IDX_DARK_ROOM,
	BG_IDX_MAX
};
//=============================================================================
// プロトタイプ宣言
void InitBg(void);
void UninitBg(void);
void DrawBg(void);
void SetBgTextureIdx(int no);
BG* GetBg(void);
#endif