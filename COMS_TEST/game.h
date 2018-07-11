//=============================================================================
//
// ゲームモードの処理 [game.h]
// Author : 川井一生
// 改変者 : 藤田高輔
// 改変内容 : ゲーム内環境の追加など
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//=============================================================================
// マクロ定義
#define WEEK_NUM_PROTO_MAX		(5)		//プロトタイプ難易度における最大の週数


#define SCREEN_POS_RIGHT	(D3DXVECTOR2(SCREEN_WIDTH/4,(SCREEN_HEIGHT/2)))
#define SCREEN_POS_LEFT		(D3DXVECTOR2((SCREEN_WIDTH/4) * 3,(SCREEN_HEIGHT/2)))
#define SCREEN_POS_MIDDLE	(D3DXVECTOR2(SCREEN_WIDTH/2,(SCREEN_HEIGHT/2)))

//=============================================================================
// 構造体宣言
typedef struct //ゲーム本編を制御するもの（経過週数、難易度）
{
	int difficult;	//選択された難易度
}GAME;

enum
{
	RIGHT_POS_Idx = 0,
	LEFT_POS_Idx,
	MIDDLE_POS_Idx,
};


//難易度のタイプ
enum
{
	DIFFICULT_NULL = -1,	//難易度が選択されてない状態
	DIFFICULT_PROTO,		//プロトタイプ
	DIFFICULT_MAX	//難易度最大数
};

//キャラクター番号列挙
enum
{
	IDX_PLAYER = 0,
	IDX_TERGET,
	IDX_RIVAL00,
	IDX_RIVAL01,
	IDX_RIVAL02,
	IDX_MAX
};

//=============================================================================
// プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetDifficult(int difficult);
GAME* GetGame(void);
#endif