//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 川井一生
// 改変者 : 塩沼恵
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "title BG.h"

#include "input.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_TITLE_LOGO		"data/texture/title/TitleLogo.png"		// ゲームタイトルテクスチャファイル名
#define	TEXTURE_TITLE_ALFA		"data/texture/title/Alfa.png"			// アルファ用テクスチャファイル名
#define	TEXTURE_TITLE_START		"data/texture/title/はじめる.png"		// スタートテクスチャファイル名
#define	TEXTURE_TITLE_EXIT		"data/texture/title/おわる.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_SHORT		"data/texture/title/ショート.png"		// 終了テクスチャファイル名
#define	TEXTURE_TITLE_MIDDLE	"data/texture/title/ミドル.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_LONG		"data/texture/title/ロング.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_BACK		"data/texture/title/もどる.png"			// 終了テクスチャファイル名

#define	TITLE_LOGO_SIZE_X		(SCREEN_WIDTH*2/3)		// ロゴの幅
#define	TITLE_LOGO_SIZE_Y		(SCREEN_HEIGHT)			// ロゴの高さ

#define	TITLE_ALFA_SIZE_X		(SCREEN_WIDTH/2)		// アルファ用画像の幅
#define	TITLE_ALFA_SIZE_Y		(SCREEN_HEIGHT)			// アルファ用画像の高さ

#define	TITLE_START_SIZE_X		(500)		// スタートテキストの幅
#define	TITLE_START_SIZE_Y		(100)		// スタートテキストの高さ

#define	TITLE_EXIT_SIZE_X		(500)		// 終了テキストの幅
#define	TITLE_EXIT_SIZE_Y		(100)		// 終了テキストの高さ

#define	TITLE_SHORT_SIZE_X		(800)		// ショートテキストの幅
#define	TITLE_SHORT_SIZE_Y		(100)		// ショートテキストの高さ

#define	TITLE_MIDDLE_SIZE_X		(800)		// ミドルテキストの幅
#define	TITLE_MIDDLE_SIZE_Y		(100)		// ミドルテキストの高さ

#define	TITLE_LONG_SIZE_X		(800)		// ロングテキストの幅
#define	TITLE_LONG_SIZE_Y		(100)		// ロングテキストの高さ

#define	TITLE_BACK_SIZE_X		(500)		// 戻るテキストの幅
#define	TITLE_BACK_SIZE_Y		(100)		// 戻るテキストの高さ

#define	COMMAND_CHANGE_MAX		(10)					// コマンドテキスト変更上限値
#define	COMMAND_SPEED			(5)						// コマンドテキスト変更スピード
//=============================================================================
// 構造体宣言
//=============================================================================
typedef enum
{
	TITLE_START,
	TITLE_SELECT,
	//	TTITLE_END,
	TITLE_MODE_MAX
}TITLEMODE;

enum
{

	COMMAND_START = 0,
	COMMAND_EXIT,
	COMMAND_MAX,

	COMMAND_SHORT = 0,
	COMMAND_MIDDLE,
	COMMAND_LONG,
	COMMAND_BACK,
	COMMANDMAX

};

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexTitle(void);
void TitleOperation(void);
void CommandMove(void);
void SetVertexTitle(void);
void TitlePosReset(void);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureAlfa = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureExit = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureShort = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureMiddle = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureLong = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureBack = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkAlfa[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkStart[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkExit[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkShort[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkMiddle[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkLong[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkBack[NUM_VERTEX];			// 頂点情報格納ワーク

int CommandFlag;		//コマンド選択時のフラグ管理
int MoveCount;			//ムーブ値カウンタ
bool MoveFlag;			//ムーブフラグ
TITLEMODE TitleMode;	//タイトルモード管理

D3DXVECTOR3 pos_Logo;
D3DXVECTOR3 pos_Alfa;
D3DXVECTOR3 pos_Start;
D3DXVECTOR3 pos_Exit;
D3DXVECTOR3 pos_Short;
D3DXVECTOR3 pos_Middle;
D3DXVECTOR3 pos_Long;
D3DXVECTOR3 pos_Back;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pos_Logo = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Alfa = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Start = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_START_SIZE_X / 2) + 50, SCREEN_HEIGHT * 3 / 10, 0.0f);
	pos_Exit = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_EXIT_SIZE_X / 2) + 50, SCREEN_HEIGHT * 7 / 10, 0.0f);
	pos_Short = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_SHORT_SIZE_X / 2) + 50, SCREEN_HEIGHT / 5, 0.0f);
	pos_Middle = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_MIDDLE_SIZE_X / 2) + 50, SCREEN_HEIGHT * 2 / 5, 0.0f);
	pos_Long = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_LONG_SIZE_X / 2) + 50, SCREEN_HEIGHT * 3 / 5, 0.0f);
	pos_Back = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_BACK_SIZE_X / 2) + 50, SCREEN_HEIGHT * 4 / 5, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_LOGO,					// ファイルの名前
		&g_pD3DTextureTitleLogo);			// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_ALFA,					// ファイルの名前
		&g_pD3DTextureAlfa);			// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_START,				// ファイルの名前
		&g_pD3DTextureStart);				// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_EXIT,					// ファイルの名前
		&g_pD3DTextureExit);				// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_SHORT,					// ファイルの名前
		&g_pD3DTextureShort);				// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_MIDDLE,					// ファイルの名前
		&g_pD3DTextureMiddle);				// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_LONG,					// ファイルの名前
		&g_pD3DTextureLong);				// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_TITLE_BACK,					// ファイルの名前
		&g_pD3DTextureBack);				// 読み込むメモリー

	TitleMode = TITLE_START;		//モードの初期化
	CommandFlag = COMMAND_START;	//コマンドフラグ初期化
	MoveCount = 0;					//移動カウント初期化
	MoveFlag = false;				//移動フラグ初期化
	InitTitleBG();					//背景初期化
	MakeVertexTitle();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{

	if (g_pD3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DTextureAlfa != NULL)
	{// テクスチャの開放
		g_pD3DTextureAlfa->Release();
		g_pD3DTextureAlfa = NULL;
	}

	if (g_pD3DTextureStart != NULL)
	{// テクスチャの開放
		g_pD3DTextureStart->Release();
		g_pD3DTextureStart = NULL;
	}

	if (g_pD3DTextureExit != NULL)
	{// テクスチャの開放
		g_pD3DTextureExit->Release();
		g_pD3DTextureExit = NULL;
	}

	if (g_pD3DTextureShort != NULL)
	{// テクスチャの開放
		g_pD3DTextureShort->Release();
		g_pD3DTextureShort = NULL;
	}

	if (g_pD3DTextureMiddle != NULL)
	{// テクスチャの開放
		g_pD3DTextureMiddle->Release();
		g_pD3DTextureMiddle = NULL;
	}

	if (g_pD3DTextureLong != NULL)
	{// テクスチャの開放
		g_pD3DTextureLong->Release();
		g_pD3DTextureLong = NULL;
	}

	if (g_pD3DTextureBack != NULL)
	{// テクスチャの開放
		g_pD3DTextureBack->Release();
		g_pD3DTextureBack = NULL;
	}

	UninitTitleBG();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	/*ここではほかで書いたアップデートを呼ぶ*/
	/*↓↓↓こんな感じ*/
	TitleOperation();
	CommandMove();
	UpdateTitleBG();
	SetVertexTitle();

	//if (GetKeyboardTrigger(DIK_NUMPAD0))
	//{
	//	SetFade(FADE_OUT, MODE_GAME);
	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	/*ここではほかで書いたドローを呼ぶ*/
	/*↓↓↓こんな感じ*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawTitleBG();

	/*================ タイトルロゴ描画 ================*/
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));

	/*================ アルファ用描画 ================*/
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureAlfa);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkAlfa, sizeof(VERTEX_2D));

	switch (TitleMode)
	{
	case TITLE_START:


		/*================ Start描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureStart);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkStart, sizeof(VERTEX_2D));

		/*================ EXIT描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureExit);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkExit, sizeof(VERTEX_2D));

		break;

	case TITLE_SELECT:

		/*================ Short描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureShort);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkShort, sizeof(VERTEX_2D));

		/*================ Middle描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureMiddle);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkMiddle, sizeof(VERTEX_2D));

		/*================ Long描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureLong);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLong, sizeof(VERTEX_2D));

		/*================ Back描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBack);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBack, sizeof(VERTEX_2D));

		break;

	}
}

//=============================================================================
// タイトル制御関数
//=============================================================================
void TitleOperation(void)
{//各モード時に決定ボタン押下時の処理を決定
	switch (TitleMode)
	{
	case TITLE_START:	//タイトルモードがスタート状態
		if (GetKeyboardTrigger(DIK_RETURN))
		{//決定ボタン押下時
			if (CommandFlag == COMMAND_START)
			{//コマンドフラグがスタートの時
			 //タイトルのモードを1つ進める
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
				//コマンドフラグをコマンドショートに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
				//pos値をリセットする
				TitlePosReset();

			}
			else if (CommandFlag == COMMAND_EXIT)
			{//コマンドフラグが終了の時
			 //ゲームの終了処理を行う
				exit(0);
			}
		}
		break;

	case TITLE_SELECT:	//タイトルモードがモード選択状態
		switch (CommandFlag)
		{//各コマンドフラグによって制御を変更する
		case COMMAND_SHORT:		//ショートモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはショートモード

				//ゲームのループ回数
				//SetWeekLoopCnt(2);

			 //ゲーム内モードをタイトルからゲームへ移行
				SetFade(FADE_OUT, MODE_GAME);

			 //テスト用
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_MIDDLE:	//ミドルモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはミドルモード

			 //ゲーム内モードをタイトルからゲームへ移行
				SetFade(FADE_OUT, MODE_GAME);

			 //テスト用
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_LONG:		//ロングモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはロングモード

			 //ゲーム内モードをタイトルからゲームへ移行
				SetFade(FADE_OUT, MODE_GAME);

			 //テスト用
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
			}
			break;

		case COMMAND_BACK:		//戻るモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //タイトルモードを１つ前に戻す
				TitleMode = (TITLEMODE)((TitleMode - 1) % TITLE_MODE_MAX);
				//コマンドフラグをコマンドスタートに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
				//pos値をリセットする
				TitlePosReset();

			}
			break;
		}
		break;
	}
}

//=============================================================================
// コマンド移動関数
//=============================================================================
void CommandMove(void)
{
	switch (TitleMode)
	{
	case TITLE_START:	//タイトルモードがスタート状態
						//カウントが溜まるまでの間でテクスチャを動かす
		if (CommandFlag == COMMAND_START)
		{//コマンドフラグ別に処理を行う
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Exit.x = pos_Start.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Start.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_EXIT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_EXIT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
		}
		else if (CommandFlag == COMMAND_EXIT)
		{
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Start.x = pos_Exit.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//終了テキストを動かす
				pos_Exit.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグをスタートコマンドに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグをスタートコマンドに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
		}

		break;

	case TITLE_SELECT:	//タイトルモードがモード選択状態
		switch (CommandFlag)
		{//各コマンドフラグによって制御を変更する
		case COMMAND_SHORT:		//ショートモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Middle.x = pos_Short.x;
				 pos_Back.x = pos_Short.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Short.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_BACK;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_MIDDLE;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}

			break;

		case COMMAND_MIDDLE:	//ミドルモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Short.x = pos_Middle.x;
				 pos_Long.x = pos_Middle.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Middle.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_LONG;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			break;

		case COMMAND_LONG:		//ロングモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Middle.x = pos_Long.x;
				 pos_Back.x = pos_Long.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Long.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_MIDDLE;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_BACK;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			break;

		case COMMAND_BACK:		//戻るモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Long.x = pos_Back.x;
				 pos_Short.x = pos_Back.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Back.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_LONG;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}

			break;
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	/*================ タイトルロゴの頂点作成================*/
	// 頂点座標の設定
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(pos_Logo.x - (TITLE_LOGO_SIZE_X / 2), pos_Logo.y - (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(pos_Logo.x + (TITLE_LOGO_SIZE_X / 2), pos_Logo.y - (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(pos_Logo.x - (TITLE_LOGO_SIZE_X / 2), pos_Logo.y + (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(pos_Logo.x + (TITLE_LOGO_SIZE_X / 2), pos_Logo.y + (TITLE_LOGO_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleLogo[0].rhw =
		g_vertexWkTitleLogo[1].rhw =
		g_vertexWkTitleLogo[2].rhw =
		g_vertexWkTitleLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleLogo[0].diffuse =
		g_vertexWkTitleLogo[1].diffuse =
		g_vertexWkTitleLogo[2].diffuse =
		g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ アルファ用の頂点作成================*/
	// 頂点座標の設定
	g_vertexWkAlfa[0].vtx = D3DXVECTOR3(pos_Alfa.x - (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y - (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[1].vtx = D3DXVECTOR3(pos_Alfa.x + (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y - (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[2].vtx = D3DXVECTOR3(pos_Alfa.x - (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y + (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[3].vtx = D3DXVECTOR3(pos_Alfa.x + (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y + (TITLE_ALFA_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkAlfa[0].rhw =
		g_vertexWkAlfa[1].rhw =
		g_vertexWkAlfa[2].rhw =
		g_vertexWkAlfa[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkAlfa[0].diffuse =
		g_vertexWkAlfa[1].diffuse =
		g_vertexWkAlfa[2].diffuse =
		g_vertexWkAlfa[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 180);

	// テクスチャ座標の設定
	g_vertexWkAlfa[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkAlfa[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkAlfa[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkAlfa[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ Stratテキストの頂点作成================*/
	// 頂点座標の設定
	g_vertexWkStart[0].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[1].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[2].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[3].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkStart[0].rhw =
		g_vertexWkStart[1].rhw =
		g_vertexWkStart[2].rhw =
		g_vertexWkStart[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkStart[0].diffuse =
		g_vertexWkStart[1].diffuse =
		g_vertexWkStart[2].diffuse =
		g_vertexWkStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ EXITの頂点作成================*/
	// 頂点座標の設定
	g_vertexWkExit[3].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[0].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[1].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[2].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkExit[0].rhw =
		g_vertexWkExit[1].rhw =
		g_vertexWkExit[2].rhw =
		g_vertexWkExit[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkExit[0].diffuse =
		g_vertexWkExit[1].diffuse =
		g_vertexWkExit[2].diffuse =
		g_vertexWkExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkExit[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkExit[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkExit[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkExit[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= ショートテキストの頂点作成==============================*/
	g_vertexWkShort[0].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[1].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[2].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[3].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkShort[0].rhw =
		g_vertexWkShort[1].rhw =
		g_vertexWkShort[2].rhw =
		g_vertexWkShort[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkShort[0].diffuse =
		g_vertexWkShort[1].diffuse =
		g_vertexWkShort[2].diffuse =
		g_vertexWkShort[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkShort[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkShort[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkShort[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkShort[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= ミドルテキストの頂点作成==============================*/
	g_vertexWkMiddle[0].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[1].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[2].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[3].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkMiddle[0].rhw =
		g_vertexWkMiddle[1].rhw =
		g_vertexWkMiddle[2].rhw =
		g_vertexWkMiddle[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkMiddle[0].diffuse =
		g_vertexWkMiddle[1].diffuse =
		g_vertexWkMiddle[2].diffuse =
		g_vertexWkMiddle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkMiddle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkMiddle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkMiddle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkMiddle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= ロングテキストの頂点作成==============================*/
	g_vertexWkLong[0].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[1].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[2].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[3].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);


	// テクスチャのパースペクティブコレクト用
	g_vertexWkLong[0].rhw =
		g_vertexWkLong[1].rhw =
		g_vertexWkLong[2].rhw =
		g_vertexWkLong[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkLong[0].diffuse =
		g_vertexWkLong[1].diffuse =
		g_vertexWkLong[2].diffuse =
		g_vertexWkLong[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkLong[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLong[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLong[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLong[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= 戻るテキストの頂点作成==============================*/
	g_vertexWkBack[0].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[1].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[2].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[3].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkBack[0].rhw =
		g_vertexWkBack[1].rhw =
		g_vertexWkBack[2].rhw =
		g_vertexWkBack[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkBack[0].diffuse =
		g_vertexWkBack[1].diffuse =
		g_vertexWkBack[2].diffuse =
		g_vertexWkBack[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkBack[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBack[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBack[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBack[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVertexTitle(void)
{
	// =====================================スタート頂点座標の設定
	g_vertexWkStart[0].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[1].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[2].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[3].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);

	// =====================================終了頂点座標の設定
	g_vertexWkExit[3].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[0].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[1].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[2].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);

	// =====================================ショート頂点座標の設定
	g_vertexWkShort[0].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[1].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[2].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[3].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);

	// =====================================ミドル頂点座標の設定
	g_vertexWkMiddle[0].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[1].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[2].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[3].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);

	// =====================================ロング頂点座標の設定
	g_vertexWkLong[0].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[1].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[2].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[3].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);

	// =====================================戻る頂点座標の設定
	g_vertexWkBack[0].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[1].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[2].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[3].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);

}

//=============================================================================
// コマンド移動関数
//=============================================================================
void TitlePosReset(void)
{
	pos_Logo = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Alfa = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Start = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_START_SIZE_X / 2) + 50, SCREEN_HEIGHT * 3 / 10, 0.0f);
	pos_Exit = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_EXIT_SIZE_X / 2) + 50, SCREEN_HEIGHT * 7 / 10, 0.0f);
	pos_Short = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_SHORT_SIZE_X / 2) + 50, SCREEN_HEIGHT / 5, 0.0f);
	pos_Middle = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_MIDDLE_SIZE_X / 2) + 50, SCREEN_HEIGHT * 2 / 5, 0.0f);
	pos_Long = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_LONG_SIZE_X / 2) + 50, SCREEN_HEIGHT * 3 / 5, 0.0f);
	pos_Back = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_BACK_SIZE_X / 2) + 50, SCREEN_HEIGHT * 4 / 5, 0.0f);

}