//=============================================================================
//
// テキストボックスの処理 [text box.cpp]
// Author : 川井一生
//=============================================================================
#include "main.h"
#include "text box.h"

#include "input.h"

//=============================================================================
// マクロ定義
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// テキストボックスのテクスチャーパス
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// テキストボックスの位置
#define TEXT_BOX_POS_Y		((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/4))
#define TEXT_BOX_SIZE_X		(1205)				// テキストボックスの大きさ(ピクセル数の大きさ)
#define TEXT_BOX_SIZE_Y		(300)

#define TEXT_BOX_PRESS_SPACE_PATH	("data/texture/ui/press space.png")
#define TEXT_BOX_PRESS_ENTER_PATH	("data/texture/ui/press enter.png")
#define TEXT_BOX_PRESS_123_PATH		("data/texture/ui/press 123.png")

#define TEXT_BOX_PRESS_SIZE_X	(147)			// 大きさ(画僧のピクセルの大きさ)
#define TEXT_BOX_PRESS_SIZE_Y	(25)
#define TEXT_BOX_PRESS_POS_X	(TEXT_BOX_POS_X + (TEXT_BOX_SIZE_X / 2) - TEXT_BOX_PRESS_SIZE_X) // テキストボックスの右下の角に設置
#define TEXT_BOX_PRESS_POS_Y	(TEXT_BOX_POS_Y + (TEXT_BOX_SIZE_Y / 2) - TEXT_BOX_PRESS_SIZE_Y)

#define TEXT_BOX_ALPHA_RATE	(0.02)				// アルファの変換量・変換速度

//=============================================================================
// プロトタイプ宣言
void TextBoxAlphaSetting(void);
void PressAlphaSetting(void);

//=============================================================================
// グローバル変数
TEXTBOX					gTextBoxWk;				// 構造体
LPDIRECT3DTEXTURE9		gTextBoxTexture;		// テクスチャ

TEXTBOXPRESS			gTextBoxPressWk;		// 構造体
LPDIRECT3DTEXTURE9		gTextBoxPressTexture[TEX_BOX_PRESS_MAX];		// テクスチャ

//=============================================================================
// テキストモードの初期化処理
void InitTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_TEXTURE, &gTextBoxTexture);
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_PRESS_SPACE_PATH, &gTextBoxPressTexture[Idx_PRESS_SPACE]);
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_PRESS_ENTER_PATH, &gTextBoxPressTexture[Idx_PRESS_ENTER]);
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_PRESS_123_PATH, &gTextBoxPressTexture[Idx_PRESS_123]);

	texbox->use = true;
	texbox->display = true;
	texbox->poly.Pos = D3DXVECTOR2(TEXT_BOX_POS_X, TEXT_BOX_POS_Y);
	texbox->poly.Rot = 0.0f;
	texbox->poly.Size = D3DXVECTOR2(TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y);
	texbox->alpha = 0.0f;
	texbox->poly.TexId = 0;

	SetBasic2DVtxdata(pDevice, &texbox->poly);
	SetBasic2DPos(&texbox->poly);

	press->use = true;
	press->isfade = false;
	press->poly.Pos = D3DXVECTOR2(TEXT_BOX_PRESS_POS_X, TEXT_BOX_PRESS_POS_Y);
	press->poly.Rot = 0.0f;
	press->poly.Size = D3DXVECTOR2(TEXT_BOX_PRESS_SIZE_X, TEXT_BOX_PRESS_SIZE_Y);
	press->alpha = 0.0f;
	press->poly.TexId = Idx_PRESS_SPACE;

	SetBasic2DVtxdata(pDevice, &press->poly);
	SetBasic2DPos(&press->poly);
}

//=============================================================================
// 終了処理
void UninitTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// 座標データの解放
	SAFE_RELEASE(texbox->poly.VtxBuff);

	// テクスチャの解放
	SAFE_RELEASE(gTextBoxTexture);

	SAFE_RELEASE(press->poly.VtxBuff);

	for (int i = 0; i < TEX_BOX_PRESS_MAX; i++)
	{
		SAFE_RELEASE(gTextBoxPressTexture[i]);
	}
}

//=============================================================================
// 最新処理
void UpdateTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// 処理を飛ばすか
	if (!texbox->use)
		return;

	// 使わないなら透明にする
	if (!press->use)
		press->isfade = false;


	// キー入力で表示するか
	if (GetKeyboardTrigger(DIK_0))
	{
		if (texbox->display)
			texbox->display = false;
		else
			texbox->display = true;
	}

	// アルファの変換処理
	TextBoxAlphaSetting();
	PressAlphaSetting();
}

//=============================================================================
// 描画処理
void DrawTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	if (texbox->alpha > 0.0f)
		DrawBasic2DObject(pDevice,&texbox->poly.VtxBuff,&gTextBoxTexture);

	if (press->alpha > 0.0f)
		DrawBasic2DObject(pDevice, &press->poly.VtxBuff, &gTextBoxPressTexture[press->poly.TexId]);

}

//=============================================================================
// テキストボックスのアルファの処理
void TextBoxAlphaSetting(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	float alphacheck = texbox->alpha;

	// 透明度を下げる処理
	if (texbox->display)
		if (texbox->alpha < 1.0f)
			texbox->alpha += TEXT_BOX_ALPHA_RATE;

	// 透明度を下げる処理
	if (!texbox->display)
		if (texbox->alpha > 0.0f)
			texbox->alpha -= TEXT_BOX_ALPHA_RATE;

	// 色の変換
	if (alphacheck != texbox->alpha)	// データが一緒なら処理しない
		SetBasic2DCol(&texbox->poly, 1.0f, 1.0f, 1.0f, texbox->alpha);
}

//=============================================================================
// プレスボタンのアルファの処理
void PressAlphaSetting(void)
{
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	float alphacheck = press->alpha;

	// 透明度を下げる処理
	if (press->isfade)
	{
		if (press->alpha < 1.0f)
			press->alpha += TEXT_BOX_ALPHA_RATE;
		else
			press->isfade = false;
	}

	// 透明度を下げる処理
	if (!press->isfade)
	{
		if (press->alpha > 0.0f)
			press->alpha -= TEXT_BOX_ALPHA_RATE;
		else
			press->isfade = true;
	}

	// 色の変換
	if (alphacheck != press->alpha)	// データが一緒なら処理しない
		SetBasic2DCol(&press->poly, 1.0f, 1.0f, 1.0f, press->alpha);
}

void SetTextBoxPress(int no)
{
	TEXTBOXPRESS *press = &gTextBoxPressWk;
	press->poly.TexId = no;
}