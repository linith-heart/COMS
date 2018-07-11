//=============================================================================
//
// バックグラウンドの処理 [bg.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "bg.h"

#include "basic.h"
//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数	
BG						g_bg;						// 構造体
LPDIRECT3DTEXTURE9		g_BgTexture[BG_IDX_MAX];	// テクスチャ

//=============================================================================
// バックグラウンドモードの初期化処理
void InitBg(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bgの先頭アドレス取得
	BG *bg = &g_bg;

	// テクスチャー読み込み
	D3DXCreateTextureFromFile(pDevice, BG_00_FILE_PATH, &g_BgTexture[BG_IDX_CLASS_ROOM]);
	D3DXCreateTextureFromFile(pDevice, BG_01_FILE_PATH, &g_BgTexture[BG_IDX_OUTSIDE]);
	D3DXCreateTextureFromFile(pDevice, BG_02_FILE_PATH, &g_BgTexture[BG_IDX_DARK_ROOM]);

	bg->use = true;
	// 位置
	bg->poly.Pos.x = BG_POS_X;
	bg->poly.Pos.y = BG_POS_Y;

	// 大きさ
	bg->poly.Size.x = BG_SIZE_X;
	bg->poly.Size.y = BG_SIZE_Y;

	// 回転
	bg->poly.Rot = 0.0f;
	
	// テクスチャーのインデックス番号
	bg->poly.TexId = BG_IDX_CLASS_ROOM;

	// ヴァーテックスバッファの設定
	SetBasic2DVtxdata(pDevice, &bg->poly);

	// 位置設定
	SetBasic2DPos(&bg->poly);

	// 色の設定
	SetBasic2DCol(&bg->poly, 1.0f, 1.0f, 1.0f, 1.0f);

	return;
}

//=============================================================================
// バックグラウンドモードの初期化処理
void UninitBg(void)
{
	BG *bg = &g_bg;

	SAFE_RELEASE(bg->poly.VtxBuff);

	for (int i = 0; i < BG_IDX_MAX; i++)
	{	// テクスチャーのリリース
		SAFE_RELEASE(g_BgTexture[i])
	}
}

//=============================================================================
// バックグラウンドモードの描画処理
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG* bg = &g_bg;
	//更新ループ
	if (bg->use == true)
	{	// テクスチャーの描画
		DrawBasic2DObject(pDevice, &bg->poly.VtxBuff,&g_BgTexture[bg->poly.TexId]);
	}
}

//=============================================================================
// テクスチャー変更処理
void SetBgTextureIdx(int no)
{
	BG* bg = &g_bg;
	bg->poly.TexId = no;
}

//=============================================================================
// BGゲット関数
BG* GetBg(void)
{
	return &g_bg;
}