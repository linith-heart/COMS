#pragma once
//=============================================================================
//
// ゲームの背景処理 [game BG.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _GAME_BG_H_
#define _GAME_BG_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
HRESULT InitGameBG(void);
void UninitGameBG(void);
void UpdateGameBG(void);
void DrawGameBG(void);

#endif
