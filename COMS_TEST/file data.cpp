//=============================================================================
//
// �t�@�C���f�[�^�̏��� [file data.cpp]
// Author : ���
//
//=============================================================================
#include "main.h"
#include "file data.h"

#include "text.h"
#include "player.h"
//=============================================================================
// �}�N����`
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
// �O���[�o���ϐ�
char	FileData[MAX_PATH][MAX_PATH];		// �t�@�C���̒��g


//=============================================================================
// �v���g�^�C�v�錾
void ClearTextData(void);

int SearchFromFileData(char search[]);

int ReflectScore(int adr);

int CopyFromFileData(int adr);

void CopyFromBuf(void);

//=============================================================================
// �t�@�C�����J������
void OpenEventFile(int week)
{
	FILE *fp;
	char filename[MAX_PATH];				// �t�@�C����
	char file_num[4];						// �t�@�C���ԍ�

	// ���g�̃N���A
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


	strcpy(filename, EVENT_FILE_PATH);		// �p�X

	strcat(filename, &file_num[0]);			// �ԍ�

	strcat(filename, TXT_FILE_EXTENSION);	// �g���q

	// �t�@�C�����J��
	fp = fopen(filename, "r");
	if (fp == NULL)
		perror("Error opening file");

	// �t�@�C�����t�@�C���o�t�@�[�z���
	for (int i = 0; i < MAX_PATH; i++)
	{
		fscanf(fp, "%s", &FileData[i][0]);
		if (strcmp(&FileData[i][0], END_OF_FILE) == 0)
			break;
	}
}

//=============================================================================
// �^�[�Q�b�g���鏗�̃e�L�X�g�f�[�^���o�b�t�@�[�ɏ������ޏ���
void LoadDayStartText(void)
{
	TEXT *text = GetText();

	char search[20];

	strcpy(search, DAY_START);		// �����Ώۂ�����

	int row = 0;							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	for (row = 0; row < MAX_PATH; row++)		// �R�s�[����ꏊ������
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
		{
			row++;
			break;
		}
	}

	ClearTextData();		// �e�L�X�g�̍\���̂̒��g���N���A

	int j = 0;							// �o�b�t�@�[�̈ʒu�w��

	while (true)						// �I���܂ŃR�s�[
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]); // �e�L�X�g�o�b�t�@�[�ɃR�s�[

		row++;
		j++;
	}
	text->rowmax = j;					// �ǂݎ��s�̃}�b�N�X�Z�b�g

	CopyFromBuf();
}

//=============================================================================
// �^�[�Q�b�g���鏗�̃e�L�X�g�f�[�^���o�b�t�@�[�ɏ������ޏ���
void LoadTargetSelectText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL, NULL };
	char search[10];

	// search�̐ݒ�
	buf[0] = Idx + '0';					// �C���f�b�N�X�̐����𕶎��ɕϊ�
	strcpy(search, SEARCH_RIVAL);		// �����Ώۂ�����
	strcat(search, &buf[0]);

	// �f�[�^�̈ʒu���Q�b�g
	int adr = SearchFromFileData(&search[0]);
	if (adr == -1)
	{
		perror("data not found");
		return;
	}


	// ���g�N���A
	ClearTextData();

	// �t�@�C���f�[�^����o�t�@�[��
	// �ǂݍ��񂾍s�������^�[��
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// �o�t�@�[�z�񂩂�\���z���
	CopyFromBuf();

}

//=============================================================================
// �I�v�V�����̃e�L�X�g���o�b�t�@�[�ɏ������ޏ���
void LoadOptionText()
{
	TEXT *text = GetText();

	// �f�[�^�̈ʒu���Q�b�g
	int adr = SearchFromFileData(OPTION);							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	if (adr == -1)
	{
		perror("data not found");
		return;
	}

	// ���g�N���A
	ClearTextData();

	// �t�@�C���f�[�^����o�t�@�[��
	// �ǂݍ��񂾍s�������^�[��
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// �o�t�@�[�z�񂩂�\���z���
	CopyFromBuf();

}

//=============================================================================
// ���U���g�̃e�L�X�g���o�b�t�@�[�ɏ������ޏ���
void LoadResultText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL , NULL};
	char search[10];

	// search�̐ݒ�
	buf[0] = Idx + '0';					// �C���f�b�N�X�̐����𕶎��ɕϊ�
	strcpy(search, SEARCH_RESULT);		// �����Ώۂ�����
	strcat(search, buf);

	// �f�[�^�̈ʒu���Q�b�g
	int adr = SearchFromFileData(&search[0]);
	if (adr == -1)
	{
		perror("data not found");
		return;
	}

	adr = ReflectScore(adr);

	// ���g�N���A
	ClearTextData();

	// �t�@�C���f�[�^����o�t�@�[��
	// �ǂݍ��񂾍s�������^�[��
	text->rowmax = CopyFromFileData(adr);
	if (text->rowmax == -1)
	{
		perror("data not found");
		return;
	}

	// �o�t�@�[�z�񂩂�\���z���
	CopyFromBuf();
}


//=============================================================================
// �e�L�X�g�f�[�^�z��̒��g�̏�����
void ClearTextData(void)
{
	TEXT *text = GetText();

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// �o�b�t�@�[���N���A
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���f�[�^���N���A
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���J�E���g���[����
		text->drawcnt[i] = 0;
}


//=============================================================================
// �t�@�C���f�[�^�����猟��
// search : �t�@�C���f�[�^���猩������������
// return : �t�@�C���f�[�^���̃f�[�^�̈ʒu
//=============================================================================
int SearchFromFileData(char search[])
{
	int tOut = 0;
	for (tOut = 0; tOut < MAX_PATH; tOut++)		// �R�s�[����ꏊ������
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
// ���U���g�̓_�����f
//    adr : �f�[�^�ǂݍ��݂��n�߂�ʒu
// return : �ǂݍ��񂾌�̃A�h���X
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
// �t�@�C���f�[�^�z�񂩂�o�t�@�[�z��փf�[�^�̃R�s�[
//    adr : �f�[�^�ǂݍ��݂��n�߂�ʒu
// return : �ǂݍ��񂾍s��
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
// �o�t�@�[�z�񂩂�\���z���
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
