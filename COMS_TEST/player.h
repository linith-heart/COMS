//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義
#define PLAYER_MAX	(1)											//プレイヤー最大数
#define PLAYER00_TEXTURE	("COMS/data/texture/chara/二宮飛鳥.png")	//テクスチャ名
#define PLAYER00_TEXTURE_SIZE_X		(242.0f)	//テクスチャサイズX
#define PLAYER00_TEXTURE_SIZE_Y		(426.0f)	//テクスチャサイズY
#define PLAYER00_FIRST_POS_X		(0.0f)		//プレイヤー初期位置
#define PLAYER00_FIRST_POS_Y		(0.0f)		//プレイヤー初期位置

#define PLAYER00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define PLAYER00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define PLAYER00_ANIM_PATTERN_NUM			(TEXTURE_PLAYER_PATTERN_DIVIDE_X*TEXTURE_PLAYER_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//プレイヤー構造体
typedef struct
{
	int attraction; // will use later
}PLAYER;

//=============================================================================
// プロトタイプ宣言
void InitPlayer(int oldMode);
void UninitPlayer(int oldMode);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
#endif