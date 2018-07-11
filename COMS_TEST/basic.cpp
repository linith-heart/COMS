//=============================================================================
//
// 自作便利関数 [basic.cpp]
// Author : 川井一生
/*
よく使われる描画などのコードを関数化した物のライブラリ


libary for code that is used farly commonly
*/
//=============================================================================
#include "main.h"
#include "basic.h"

//=============================================================================
// グローバル変数
POLY			polyWK;
BILL			billWk;
MESH			meshWk;

//=============================================================================
// 2次元のオブジェクトの位置変換
void SetBasic2DPos(POLY *poly)
{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 反射光の設定
	pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);

	// 頂点データをアンロックする
	poly->VtxBuff->Unlock();

}

//=============================================================================
// 2次元のおbジェクトの色の変換処理
void SetBasic2DCol(POLY *poly, float r, float g, float b, float a)
{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 反射光の設定
	pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

	// 頂点データをアンロックする
	poly->VtxBuff->Unlock();
}

//=============================================================================
// 2次元のオブジェクトの描画関数
void DrawBasic2DObject(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 *vtxbuff, LPDIRECT3DTEXTURE9 *tex)
{
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, *vtxbuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, *tex);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// メッシュのオブジェクトの描画関数
void DrawBasic3DObject(MESH *mesh, LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ワールドマトリクス初期化
	D3DXMatrixIdentity(&mesh->mtxWorld);

	// スケールを反映	(S)
	D3DXMatrixScaling(&mtxScl, mesh->Scl.x, mesh->Scl.y, mesh->Scl.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxScl); 	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxScl
																						// 回転を反映		(R)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->Rot.y, mesh->Rot.x, mesh->Rot.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxRot
																						// 平行移動を反映	(T)
	D3DXMatrixTranslation(&mtxTranslate, mesh->Pos.x, mesh->Pos.y, mesh->Pos.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

	// ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

	// 現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	// マテリアル情報へのポインタを
	pD3DXMat = (D3DXMATERIAL*)mesh->BuffMat->GetBufferPointer();

	int i;
	for (i = 0; i < (int)mesh->NumMat; i++)
	{
		
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	// マテリアルの設定

		pDevice->SetTexture(0, tex);	// テクスチャの設定
		mesh->Mesh->DrawSubset(i);
	}

	// マテリアルに戻す
	pDevice->SetMaterial(&matDef);
}


HRESULT SetBasic2DVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&poly->VtxBuff,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y + poly->Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y + poly->Size.y, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		poly->VtxBuff->Unlock();
	}
}