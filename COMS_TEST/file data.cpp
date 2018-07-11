//=============================================================================
//
// ファイルデータの処理 [file data.cpp]
// Author : 川井
//
//=============================================================================
#include "main.h"
#include "file data.h"

#include "text.h"
#include "player.h"
//=============================================================================
// マクロ定義
#define EVENT_FILE_PATH		"data/text/event"
#define TXT_FILE_EXTENSION	".txt"
#define CSV_FILE_EXTENSION	".csv"

#define DAY_START			"##Daystart"
#define SEARCH_RIVAL		"##Rival"
#define RIVAL01				"##Rival1"
#define RIVAL02				"##Rival2"
#define RIVAL03				"##Rival3"

#define OPTION				"##option"

#define SEARCH_RESULT		"##op"
#define RESULT01			"##op1"
#define RESULT02			"##op2"
#define RESULT03			"##op3"

#define END_OF_SECTION		"##end"


#define END_OF_FILE			"##FileEnd"

//=============================================================================
// グローバル変数
char	FileData[MAX_PATH][MAX_PATH];		// ファイルの中身


//=============================================================================
// プロトタイプ宣言
void ClearTextData(void);

int SearchFromFileData(char search[]);

int ReflectScore(int adr);

int CopyFromFileData(int adr);

void CopyFromBuf(void);

//=============================================================================
// ファイルを開く処理
void OpenEventFile(int week)
{
	FILE *fp;
	char filename[MAX_PATH];				// ファイル名
	char file_num[4];						// ファイル番号

	// 中身のクリア
	for (int i = 0; i < MAX_PATH; i++)
	{
		memset(FileData, 0, sizeof((char*)MAX_PATH));
	}

	file_num[0] = NULL;
	file_num[1] = NULL;
	file_num[2] = NULL;
	file_num[3] = NULL;

	file_num[2] = week % 10 + '0';
	file_num[1] = week / 10 % 10 + '0';
	file_num[0] = week / 100 % 10 + '0';


	strcpy(filename, EVENT_FILE_PATH);		// パス

	strcat(filename, &file_num[0]);			// 番号

	strcat(filename, TXT_FILE_EXTENSION);	// 拡張子

	// ファイルを開く
	fp = fopen(filename, "r");
	if (fp == NULL)
		perror("Error opening file");

	// ファイルをファイルバファー配列へ
	for (int i = 0; i < MAX_PATH; i++)
	{
		fscanf(fp, "%s", &FileData[i][0]);
		if (strcmp(&FileData[i][0], END_OF_FILE) == 0)
			break;
	}
}

//=============================================================================
// ターゲットする女のテキストデータをバッファーに書き込む処理
void LoadDayStartText(void)
{
	TEXT *text = GetText();

	char search[20];

	strcpy(search, DAY_START);		// 検索対象を検索

	int row = 0;							// ファイルデータのデータの位置指定
	for (row = 0; row < MAX_PATH; row++)		// コピーする場所を検索
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
		{
			row++;
			break;
		}
	}

	ClearTextData();		// テキストの構造体の中身をクリア

	int j = 0;							// バッファーの位置指定

	while (true)						// 終わりまでコピー
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]); // テキストバッファーにコピー

		row++;
		j++;
	}
	text->rowmax = j;					// 読み取る行のマックスセット

	CopyFromBuf();
}

//=============================================================================
// ターゲットする女のテキストデータをバッファーに書き込む処理
void LoadTargetSelectText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL, NULL };
	char search[10];

	// searchの設定
	buf[0] = Idx + '0';					// インデックスの数字を文字に変換
	strcpy(search, SEARCH_RIVAL);		// 検索対象を検索
	strcat(search, &buf[0]);

	// データの位置をゲット
	int adr = SearchFromFileData(&search[0]);
	if (adr == -1)
	{
		perror("data not found");
		return;
	}


	// 中身クリア
	ClearTextData();

	// ファイルデータからバファーに
	// 読み込んだ行数をリターン
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// バファー配列から表示配列へ
	CopyFromBuf();

}

//=============================================================================
// オプションのテキストをバッファーに書き込む処理
void LoadOptionText()
{
	TEXT *text = GetText();

	// データの位置をゲット
	int adr = SearchFromFileData(OPTION);							// ファイルデータのデータの位置指定
	if (adr == -1)
	{
		perror("data not found");
		return;
	}

	// 中身クリア
	ClearTextData();

	// ファイルデータからバファーに
	// 読み込んだ行数をリターン
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// バファー配列から表示配列へ
	CopyFromBuf();

}

//=============================================================================
// リザルトのテキストをバッファーに書き込む処理
void LoadResultText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL , NULL};
	char search[10];

	// searchの設定
	buf[0] = Idx + '0';					// インデックスの数字を文字に変換
	strcpy(search, SEARCH_RESULT);		// 検索対象を検索
	strcat(search, buf);

	// データの位置をゲット
	int adr = SearchFromFileData(&search[0]);
	if (adr == -1)
	{
		perror("data not found");
		return;
	}

	adr = ReflectScore(adr);

	// 中身クリア
	ClearTextData();

	// ファイルデータからバファーに
	// 読み込んだ行数をリターン
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// バファー配列から表示配列へ
	CopyFromBuf();
}


//=============================================================================
// テキストデータ配列の中身の初期化
void ClearTextData(void)
{
	TEXT *text = GetText();

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// バッファーをクリア
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// 表示データをクリア
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// 表示カウントをゼロに
		text->drawcnt[i] = 0;
}


//=============================================================================
// ファイルデータをから検索
// search : ファイルデータから見つけたい文字列
// return : ファイルデータ内のデータの位置
//=============================================================================
int SearchFromFileData(char search[])
{
	int tOut = 0;
	for (tOut = 0; tOut < MAX_PATH; tOut++)		// コピーする場所を検索
	{
		if (strcmp(&FileData[tOut][0], &search[0]) == 0)
		{
			tOut++;
			return tOut;
		}
	}

	return -1;
}

//=============================================================================
// リザルトの点数反映
//    adr : データ読み込みを始める位置
// return : 読み込んだ後のアドレス
//=============================================================================
int ReflectScore(int adr)
{
	PLAYER *player = GetPlayer();
	int tOut = adr;
	char temp[4] = { NULL,NULL,NULL,NULL };

	strcpy(&temp[0], &FileData[tOut][0]);

	tOut++;

	int num = atoi(&temp[0]);

	player->attraction += num;

	return tOut;
}

//=============================================================================
// ファイルデータ配列からバファー配列へデータのコピー
//    adr : データ読み込みを始める位置
// return : 読み込んだ行数
//=============================================================================
int CopyFromFileData(int adr)
{
	TEXT *text = GetText();
	int tOut = 0;

	while (true)
	{
		if (strcmp(&FileData[adr][0], END_OF_SECTION) == 0)
			return tOut;
		else if (strcmp(&FileData[adr][0], END_OF_FILE) == 0)
			return -1;
		strcpy(&text->textbuf[tOut][0], &FileData[adr][0]);

		adr++;
		tOut++;
	}
}

//=============================================================================
// バファー配列から表示配列に
void CopyFromBuf(void)
{
	TEXT *text = GetText();

	text->currbufrow = 0;
	for (int i = 0; i < TEXT_ROW_MAX && i < text->rowmax; i++, text->currbufrow++)
	{
		strcpy(&text->textdis[i][0], &text->textbuf[text->currbufrow][0]);
		text->drawcnt[i] = 0;
	}
	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		text->drawcntmax[i] = strlen(text->textdis[i]);
	}
}
