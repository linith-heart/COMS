#pragma once
//=============================================================================
//
// 自作便利処理 [basic.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _BASIC_H_
#define _BASIC_H_

#include "main.h"



//=============================================================================
//構造体宣言

// ポリゴンの構造体
typedef struct
{
	D3DXVECTOR2				Pos;					// 位置
	float					Rot;					// 向き(回転)
	D3DXVECTOR2				Size;					// 大きさ

	LPDIRECT3DVERTEXBUFFER9	VtxBuff;				// 頂点情報のデータ

	int						TexId;					// どのテクスチャーを使うか
}POLY;


// メッシュの構造体
typedef struct
{
	// マップ上の位置など
	D3DXVECTOR3				Pos;					// 位置
	D3DXVECTOR3				Rot;					// 向き(回転)
	D3DXVECTOR3				Scl;					// 大きさ(スケール)

	// テクスチャー・モデル
	LPDIRECT3DVERTEXBUFFER9	VtxBuff = NULL;			// 頂点バッファへのポインタ
	D3DXVECTOR3				*VtxPos;				// 頂点の情報
	WORD					*IdxBuff;				// インデックスの数

	LPD3DXMESH				Mesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER			BuffMat;				// マテリアル情報へのポインタ
	DWORD					NumMat;					// マテリアル情報の数

	D3DXMATRIX				mtxWorld;				// ワールドマトリックス
	int						TexId;					// どのテクスチャーを使うか
}MESH;


// ビルボードの構造体
typedef struct
{
	// マップ上の位置など
	D3DXVECTOR3				Pos;					// 位置
	D3DXVECTOR3				Rot;					// 向き(回転)
	D3DXVECTOR3				Scl;					// 大きさ(スケール)
	D3DXMATRIX				mtxWorld;				// ワールドマトリックス

	// テクスチャー
	int						TexId;					// テクスチャー番号		texture id

}BILL;


// 影の構造体
typedef struct
{
	//	影
	int						nIdxShadow;				// 影ID
	float					fSizeShadow;			// 影のサイズ
	D3DXCOLOR				colShadow;				// 影の色

}SHAD;



//=============================================================================
// プロトタイプ宣言
HRESULT SetBasic2DVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly);
void SetBasic2DPos(POLY *poly);
void SetBasic2DCol(POLY *poly, float r, float g, float b, float a);
void DrawBasic2DObject(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 *vtxbuff, LPDIRECT3DTEXTURE9 *tex);


void DrawBasic3DObject(MESH *mesh, LPDIRECT3DTEXTURE9 tex);

#endif
