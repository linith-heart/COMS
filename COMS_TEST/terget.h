//=============================================================================
//
// ターゲットの処理 [terget.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _TERGET_H_
#define _TERGET_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義
#define TERGET_MAX	(1)											//ターゲット最大数
#define TERGET00_TEXTURE	("COMS/data/texture/chara/???.png")	//テクスチャ名
#define TERGET00_TEXTURE_SIZE_X		(242.0f)	//テクスチャサイズX
#define TERGET00_TEXTURE_SIZE_Y		(426.0f)	//テクスチャサイズY
#define TERGET00_FIRST_POS_X		(0.0f)		//ターゲット初期位置
#define TERGET00_FIRST_POS_Y		(0.0f)		//ターゲット初期位置

#define TERGET00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define TERGET00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define TERGET00_ANIM_PATTERN_NUM			(TEXTURE_TERGET_PATTERN_DIVIDE_X*TEXTURE_TERGET_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//ターゲット構造体
typedef struct
{

}TERGET;

//=============================================================================
// プロトタイプ宣言
void InitTerget(int oldMode);
void UninitTerget(int oldMode);
void UpdateTerget(void);
void DrawTerget(void);
TERGET* GetTerget(void);
#endif