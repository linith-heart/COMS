//=============================================================================
//
// ライヴァルの処理 [rival.cpp]
// Author : 川井
//=============================================================================
#include "main.h"
#include "rival.h"
#include "basic.h"
#include "game.h"

#include "input.h"
//=============================================================================
// マクロ定義
#define RIVAL_01_FILE_PATH	"data/texture/chara/二宮飛鳥.png"
#define RIVAL_02_FILE_PATH	"data/texture/chara/白菊ほたる.png"
#define RIVAL_03_FILE_PATH	"data/texture/chara/的場梨沙.png"


#define RIVAL_01_SIZE_X	(256)
#define RIVAL_01_SIZE_Y	(285)

#define RIVAL_02_SIZE_X	(256)
#define RIVAL_02_SIZE_Y	(285)

#define RIVAL_03_SIZE_X	(256)
#define RIVAL_03_SIZE_Y	(285)

#define RIVAL_ALPHA_RATE (0.02)
//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
RIVAL					g_rival[RIVAL_MAX];
LPDIRECT3DTEXTURE9		g_rivalTexture[RIVAL_MAX];		// テクスチャへのポインタ

//=============================================================================
// ライヴァルモードの初期化処理
void InitRival(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RIVAL *rival = &g_rival[0];


	D3DXCreateTextureFromFile(pDevice, RIVAL_01_FILE_PATH, &g_rivalTexture[RIVAL_01]);
	D3DXCreateTextureFromFile(pDevice, RIVAL_02_FILE_PATH, &g_rivalTexture[RIVAL_02]);
	D3DXCreateTextureFromFile(pDevice, RIVAL_03_FILE_PATH, &g_rivalTexture[RIVAL_03]);

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		rival->use = true;
		rival->attraction = 0.0f;

		rival->poly.TexId = i;

		switch (i)
		{
		case RIVAL_01:	// 画面の右側へ
			rival->poly.Pos = SCREEN_POS_LEFT;
			break;
		case RIVAL_02:	// 画面の左側へ
			rival->poly.Pos = SCREEN_POS_MIDDLE;
			break;
		case RIVAL_03:		// 画面の真ん中へ
			rival->poly.Pos = SCREEN_POS_RIGHT;
			break;
		}
		rival->poly.Rot = 0.0f;
		
		rival->alpha = 0.0f;

		rival->posid = i;

		switch (i)		// 大きさ共通にしたい
		{
		case RIVAL_01:
			rival->poly.Size.x = RIVAL_01_SIZE_X;
			rival->poly.Size.y = RIVAL_01_SIZE_Y;
			break;
		case RIVAL_02:
			rival->poly.Size.x = RIVAL_02_SIZE_X;
			rival->poly.Size.y = RIVAL_02_SIZE_Y;
			break;
		case RIVAL_03:
			rival->poly.Size.x = RIVAL_03_SIZE_X;
			rival->poly.Size.y = RIVAL_03_SIZE_Y;
			break;
		}

		SetBasic2DVtxdata(pDevice, &rival->poly);

		SetBasic2DPos(&rival->poly);

		SetBasic2DCol(&rival->poly, 1.0f, 1.0f, 1.0f, rival->alpha);
	}

}

//=============================================================================
// ライヴァルモードの初期化処理
void UninitRival(void)
{
	RIVAL *rival = &g_rival[0];
	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		SAFE_RELEASE(rival->poly.VtxBuff);

		SAFE_RELEASE(g_rivalTexture[i]);
	}
}

//=============================================================================
// ライヴァルモードの最新処理
void UpdateRival(void)
{
	RIVAL *rival = &g_rival[0];

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		//============================================
		// アルファの設定
		float talpha = rival->alpha;
		if (rival->use)	// 表示するか
		{
			if (rival->alpha < 1.0f)	// 透明度をなくす
			{
				rival->alpha += RIVAL_ALPHA_RATE;
			}
			else
				rival->alpha = 1.0f;


			//============================================
			// 表示位置設定
			D3DXVECTOR2 tcheck = rival->poly.Pos;	// 現在地保存

			//switch (rival->posid)
			//{
			//case RIGHT_POS_Idx:	// 画面の右側へ
			//	rival->poly.Pos = SCREEN_POS_RIGHT;
			//	break;
			//case LEFT_POS_Idx:	// 画面の左側へ
			//	rival->poly.Pos = SCREEN_POS_LEFT;
			//	break;
			//case MIDDLE_POS_Idx:		// 画面の真ん中へ
			//	rival->poly.Pos = SCREEN_POS_MIDDLE;
			//	break;
			//}
			if (tcheck != rival->poly.Pos)			// 保存した位置と比較
				SetBasic2DPos(&rival->poly);		// 中身が違えば位置変換

		}
		else if (rival->alpha > 0.0f)	// 表示しない、また透明度が0ではない
		{
			rival->alpha -= RIVAL_ALPHA_RATE;
		}
		if (rival->alpha != talpha)
			SetBasic2DCol(&rival->poly, 1.0f, 1.0f, 1.0f, rival->alpha);


		// temp
		if (GetKeyboardTrigger(DIK_9))
		{
			if (rival->use)
				rival->use = false;
			else
				rival->use = true;
		}

	}

}

//=============================================================================
// ライヴァルモードの描画処理
void DrawRival(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RIVAL *rival = &g_rival[0];

	for (int i = 0; i < RIVAL_MAX; i++, rival++)
	{
		DrawBasic2DObject(pDevice, &rival->poly.VtxBuff, &g_rivalTexture[rival->poly.TexId]);
	}
}

//=============================================================================
// ライヴァル取得関数
RIVAL *GetRival(int no)
{
	return &g_rival[no];
}