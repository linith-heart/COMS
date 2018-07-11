//=============================================================================
//
// リザルトの背景処理 [result BG.cpp]
// Author : 川井一生
//
//=============================================================================
#include "main.h"
#include "result BG.h"
#include "result.h"

//=============================================================================
// マクロ定義
#define RESULT_BG_TEX		"data/texture/BG/result_sample1.jpg"
#define RESULT_BG_BADTEX	"data/texture/BG/result_sample4.jpg"
#define RESULT_BG_TEX2	"data/texture/BG/result_sample2.jpg"


//=============================================================================
// プロトタイプ宣言
HRESULT MakeVertexResultBG(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体宣言
typedef struct
{
	bool		use;	// 使用しているか

	float		Hight;	// 高さ
	float		Width;	// 幅

	D3DXVECTOR2	Pos;	// 位置

}RESULT_BG;
//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DResultBGTex = { NULL };		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		D3DResultBGTexBad = { NULL };		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DResultBGVtxBuf = NULL;				// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		D3DResultBGTex2 = { NULL };		// テクスチャへのポインタ


int NumBG = 0;
//=============================================================================
// 初期化処理
HRESULT InitResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT_BG resultBG;

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, RESULT_BG_TEX, &D3DResultBGTex);
	D3DXCreateTextureFromFile(pDevice, RESULT_BG_BADTEX, &D3DResultBGTexBad);
	D3DXCreateTextureFromFile(pDevice, RESULT_BG_TEX2, &D3DResultBGTex2);


	MakeVertexResultBG(pDevice);

	resultBG.use = true;

	resultBG.Hight = SCREEN_HEIGHT;
	resultBG.Width = SCREEN_WIDTH;

	resultBG.Pos = { 0.0,0.0 };

	return S_OK;
}

//=============================================================================
// 終了処理
void UninitResultBG(void)
{
	SAFE_RELEASE(D3DResultBGTex);
	SAFE_RELEASE(D3DResultBGTexBad);
	SAFE_RELEASE(D3DResultBGTex2);

	SAFE_RELEASE(D3DResultBGVtxBuf);
}

//=============================================================================
// 更新処理
void UpdateResultBG(void)
{
	NumBG = GetChangeResultBG();

}

//=============================================================================
// 描画処理
void DrawResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DResultBGVtxBuf, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (NumBG)
	{
	case HAPPYEND:
		// テクスチャの設定
		pDevice->SetTexture(0, D3DResultBGTex);
		break;

	case NORMALEND:
		// テクスチャの設定
		pDevice->SetTexture(0, D3DResultBGTex2);
		break;

	case BADEND:
		// テクスチャの設定
		pDevice->SetTexture(0, D3DResultBGTexBad);

		break;

	}
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}


//=============================================================================
// 頂点の作成
HRESULT MakeVertexResultBG(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DResultBGVtxBuf,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DResultBGVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DResultBGVtxBuf->Unlock();
	}
}