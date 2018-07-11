//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���ꐶ
// ���ώ� : �����b
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "title BG.h"

#include "input.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_TITLE_LOGO		"data/texture/title/TitleLogo.png"		// �Q�[���^�C�g���e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_ALFA		"data/texture/title/Alfa.png"			// �A���t�@�p�e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_START		"data/texture/title/�͂��߂�.png"		// �X�^�[�g�e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_EXIT		"data/texture/title/�����.png"			// �I���e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_SHORT		"data/texture/title/�V���[�g.png"		// �I���e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_MIDDLE	"data/texture/title/�~�h��.png"			// �I���e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LONG		"data/texture/title/�����O.png"			// �I���e�N�X�`���t�@�C����
#define	TEXTURE_TITLE_BACK		"data/texture/title/���ǂ�.png"			// �I���e�N�X�`���t�@�C����

#define	TITLE_LOGO_SIZE_X		(SCREEN_WIDTH*2/3)		// ���S�̕�
#define	TITLE_LOGO_SIZE_Y		(SCREEN_HEIGHT)			// ���S�̍���

#define	TITLE_ALFA_SIZE_X		(SCREEN_WIDTH/2)		// �A���t�@�p�摜�̕�
#define	TITLE_ALFA_SIZE_Y		(SCREEN_HEIGHT)			// �A���t�@�p�摜�̍���

#define	TITLE_START_SIZE_X		(500)		// �X�^�[�g�e�L�X�g�̕�
#define	TITLE_START_SIZE_Y		(100)		// �X�^�[�g�e�L�X�g�̍���

#define	TITLE_EXIT_SIZE_X		(500)		// �I���e�L�X�g�̕�
#define	TITLE_EXIT_SIZE_Y		(100)		// �I���e�L�X�g�̍���

#define	TITLE_SHORT_SIZE_X		(800)		// �V���[�g�e�L�X�g�̕�
#define	TITLE_SHORT_SIZE_Y		(100)		// �V���[�g�e�L�X�g�̍���

#define	TITLE_MIDDLE_SIZE_X		(800)		// �~�h���e�L�X�g�̕�
#define	TITLE_MIDDLE_SIZE_Y		(100)		// �~�h���e�L�X�g�̍���

#define	TITLE_LONG_SIZE_X		(800)		// �����O�e�L�X�g�̕�
#define	TITLE_LONG_SIZE_Y		(100)		// �����O�e�L�X�g�̍���

#define	TITLE_BACK_SIZE_X		(500)		// �߂�e�L�X�g�̕�
#define	TITLE_BACK_SIZE_Y		(100)		// �߂�e�L�X�g�̍���

#define	COMMAND_CHANGE_MAX		(10)					// �R�}���h�e�L�X�g�ύX����l
#define	COMMAND_SPEED			(5)						// �R�}���h�e�L�X�g�ύX�X�s�[�h
//=============================================================================
// �\���̐錾
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
// �v���g�^�C�v�錾
//=============================================================================
HRESULT MakeVertexTitle(void);
void TitleOperation(void);
void CommandMove(void);
void SetVertexTitle(void);
void TitlePosReset(void);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureAlfa = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureExit = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureShort = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureMiddle = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureLong = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureBack = NULL;			// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_vertexWkAlfa[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkStart[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkExit[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkShort[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkMiddle[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkLong[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkBack[NUM_VERTEX];			// ���_���i�[���[�N

int CommandFlag;		//�R�}���h�I�����̃t���O�Ǘ�
int MoveCount;			//���[�u�l�J�E���^
bool MoveFlag;			//���[�u�t���O
TITLEMODE TitleMode;	//�^�C�g�����[�h�Ǘ�

D3DXVECTOR3 pos_Logo;
D3DXVECTOR3 pos_Alfa;
D3DXVECTOR3 pos_Start;
D3DXVECTOR3 pos_Exit;
D3DXVECTOR3 pos_Short;
D3DXVECTOR3 pos_Middle;
D3DXVECTOR3 pos_Long;
D3DXVECTOR3 pos_Back;
//=============================================================================
// ����������
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

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_LOGO,					// �t�@�C���̖��O
		&g_pD3DTextureTitleLogo);			// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_ALFA,					// �t�@�C���̖��O
		&g_pD3DTextureAlfa);			// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_START,				// �t�@�C���̖��O
		&g_pD3DTextureStart);				// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_EXIT,					// �t�@�C���̖��O
		&g_pD3DTextureExit);				// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_SHORT,					// �t�@�C���̖��O
		&g_pD3DTextureShort);				// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_MIDDLE,					// �t�@�C���̖��O
		&g_pD3DTextureMiddle);				// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_LONG,					// �t�@�C���̖��O
		&g_pD3DTextureLong);				// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_BACK,					// �t�@�C���̖��O
		&g_pD3DTextureBack);				// �ǂݍ��ރ������[

	TitleMode = TITLE_START;		//���[�h�̏�����
	CommandFlag = COMMAND_START;	//�R�}���h�t���O������
	MoveCount = 0;					//�ړ��J�E���g������
	MoveFlag = false;				//�ړ��t���O������
	InitTitleBG();					//�w�i������
	MakeVertexTitle();

}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{

	if (g_pD3DTextureTitleLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DTextureAlfa != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureAlfa->Release();
		g_pD3DTextureAlfa = NULL;
	}

	if (g_pD3DTextureStart != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureStart->Release();
		g_pD3DTextureStart = NULL;
	}

	if (g_pD3DTextureExit != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureExit->Release();
		g_pD3DTextureExit = NULL;
	}

	if (g_pD3DTextureShort != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureShort->Release();
		g_pD3DTextureShort = NULL;
	}

	if (g_pD3DTextureMiddle != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureMiddle->Release();
		g_pD3DTextureMiddle = NULL;
	}

	if (g_pD3DTextureLong != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLong->Release();
		g_pD3DTextureLong = NULL;
	}

	if (g_pD3DTextureBack != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBack->Release();
		g_pD3DTextureBack = NULL;
	}

	UninitTitleBG();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	/*�����ł͂ق��ŏ������A�b�v�f�[�g���Ă�*/
	/*����������Ȋ���*/
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
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	/*�����ł͂ق��ŏ������h���[���Ă�*/
	/*����������Ȋ���*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawTitleBG();

	/*================ �^�C�g�����S�`�� ================*/
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));

	/*================ �A���t�@�p�`�� ================*/
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureAlfa);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkAlfa, sizeof(VERTEX_2D));

	switch (TitleMode)
	{
	case TITLE_START:


		/*================ Start�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureStart);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkStart, sizeof(VERTEX_2D));

		/*================ EXIT�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureExit);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkExit, sizeof(VERTEX_2D));

		break;

	case TITLE_SELECT:

		/*================ Short�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureShort);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkShort, sizeof(VERTEX_2D));

		/*================ Middle�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureMiddle);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkMiddle, sizeof(VERTEX_2D));

		/*================ Long�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureLong);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLong, sizeof(VERTEX_2D));

		/*================ Back�`�� ================*/
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBack);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBack, sizeof(VERTEX_2D));

		break;

	}
}

//=============================================================================
// �^�C�g������֐�
//=============================================================================
void TitleOperation(void)
{//�e���[�h���Ɍ���{�^���������̏���������
	switch (TitleMode)
	{
	case TITLE_START:	//�^�C�g�����[�h���X�^�[�g���
		if (GetKeyboardTrigger(DIK_RETURN))
		{//����{�^��������
			if (CommandFlag == COMMAND_START)
			{//�R�}���h�t���O���X�^�[�g�̎�
			 //�^�C�g���̃��[�h��1�i�߂�
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
				//�R�}���h�t���O���R�}���h�V���[�g�Ɉڍs������
				CommandFlag = COMMAND_SHORT;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
				//pos�l�����Z�b�g����
				TitlePosReset();

			}
			else if (CommandFlag == COMMAND_EXIT)
			{//�R�}���h�t���O���I���̎�
			 //�Q�[���̏I���������s��
				exit(0);
			}
		}
		break;

	case TITLE_SELECT:	//�^�C�g�����[�h�����[�h�I�����
		switch (CommandFlag)
		{//�e�R�}���h�t���O�ɂ���Đ����ύX����
		case COMMAND_SHORT:		//�V���[�g���[�h�I��
			if (GetKeyboardTrigger(DIK_RETURN))
			{//����{�^��������
			 //�Q�[���ֈڍs�B�V�i���I�̓V���[�g���[�h

				//�Q�[���̃��[�v��
				//SetWeekLoopCnt(2);

			 //�Q�[�������[�h���^�C�g������Q�[���ֈڍs
				SetFade(FADE_OUT, MODE_GAME);

			 //�e�X�g�p
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_MIDDLE:	//�~�h�����[�h�I��
			if (GetKeyboardTrigger(DIK_RETURN))
			{//����{�^��������
			 //�Q�[���ֈڍs�B�V�i���I�̓~�h�����[�h

			 //�Q�[�������[�h���^�C�g������Q�[���ֈڍs
				SetFade(FADE_OUT, MODE_GAME);

			 //�e�X�g�p
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_LONG:		//�����O���[�h�I��
			if (GetKeyboardTrigger(DIK_RETURN))
			{//����{�^��������
			 //�Q�[���ֈڍs�B�V�i���I�̓����O���[�h

			 //�Q�[�������[�h���^�C�g������Q�[���ֈڍs
				SetFade(FADE_OUT, MODE_GAME);

			 //�e�X�g�p
				//TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
			}
			break;

		case COMMAND_BACK:		//�߂郂�[�h�I��
			if (GetKeyboardTrigger(DIK_RETURN))
			{//����{�^��������
			 //�^�C�g�����[�h���P�O�ɖ߂�
				TitleMode = (TITLEMODE)((TitleMode - 1) % TITLE_MODE_MAX);
				//�R�}���h�t���O���R�}���h�X�^�[�g�Ɉڍs������
				CommandFlag = COMMAND_START;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
				//pos�l�����Z�b�g����
				TitlePosReset();

			}
			break;
		}
		break;
	}
}

//=============================================================================
// �R�}���h�ړ��֐�
//=============================================================================
void CommandMove(void)
{
	switch (TitleMode)
	{
	case TITLE_START:	//�^�C�g�����[�h���X�^�[�g���
						//�J�E���g�����܂�܂ł̊ԂŃe�N�X�`���𓮂���
		if (CommandFlag == COMMAND_START)
		{//�R�}���h�t���O�ʂɏ������s��
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Exit.x = pos_Start.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�X�^�[�g�e�L�X�g�𓮂���
				pos_Start.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_EXIT;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_EXIT;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
		}
		else if (CommandFlag == COMMAND_EXIT)
		{
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Start.x = pos_Exit.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�I���e�L�X�g�𓮂���
				pos_Exit.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���X�^�[�g�R�}���h�Ɉڍs������
				CommandFlag = COMMAND_START;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���X�^�[�g�R�}���h�Ɉڍs������
				CommandFlag = COMMAND_START;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
		}

		break;

	case TITLE_SELECT:	//�^�C�g�����[�h�����[�h�I�����
		switch (CommandFlag)
		{//�e�R�}���h�t���O�ɂ���Đ����ύX����
		case COMMAND_SHORT:		//�V���[�g���[�h�I��
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Middle.x = pos_Short.x;
				 pos_Back.x = pos_Short.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�X�^�[�g�e�L�X�g�𓮂���
				pos_Short.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_BACK;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_MIDDLE;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}

			break;

		case COMMAND_MIDDLE:	//�~�h�����[�h�I��
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Short.x = pos_Middle.x;
				 pos_Long.x = pos_Middle.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�X�^�[�g�e�L�X�g�𓮂���
				pos_Middle.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_SHORT;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_LONG;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			break;

		case COMMAND_LONG:		//�����O���[�h�I��
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Middle.x = pos_Long.x;
				 pos_Back.x = pos_Long.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�X�^�[�g�e�L�X�g�𓮂���
				pos_Long.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_MIDDLE;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_BACK;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			break;

		case COMMAND_BACK:		//�߂郂�[�h�I��
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//���[�u�J�E���g���K�莞�Ԗ����B��
				if (MoveFlag == false)
				{//�ړ��t���O�������ĂȂ��Ƃ�
				 //���̈ʒu�ɑS�Ă�߂�
				 pos_Long.x = pos_Back.x;
				 pos_Short.x = pos_Back.x;
				 //�ړ��t���O�𗧂Ă�
					MoveFlag = true;
				}
				//�X�^�[�g�e�L�X�g�𓮂���
				pos_Back.x -= COMMAND_SPEED;
				//�ړ��J�E���g�����Z����
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//��{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_LONG;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//���{�^��������
			 //�R�}���h�t���O���I���R�}���h�Ɉڍs������
				CommandFlag = COMMAND_SHORT;
				//�ړ��t���O��false�ɖ߂�
				MoveFlag = false;
				//�ړ��J�E���g�����Z�b�g����
				MoveCount = 0;
			}

			break;
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	/*================ �^�C�g�����S�̒��_�쐬================*/
	// ���_���W�̐ݒ�
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(pos_Logo.x - (TITLE_LOGO_SIZE_X / 2), pos_Logo.y - (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(pos_Logo.x + (TITLE_LOGO_SIZE_X / 2), pos_Logo.y - (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(pos_Logo.x - (TITLE_LOGO_SIZE_X / 2), pos_Logo.y + (TITLE_LOGO_SIZE_Y / 2), 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(pos_Logo.x + (TITLE_LOGO_SIZE_X / 2), pos_Logo.y + (TITLE_LOGO_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleLogo[0].rhw =
		g_vertexWkTitleLogo[1].rhw =
		g_vertexWkTitleLogo[2].rhw =
		g_vertexWkTitleLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleLogo[0].diffuse =
		g_vertexWkTitleLogo[1].diffuse =
		g_vertexWkTitleLogo[2].diffuse =
		g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ �A���t�@�p�̒��_�쐬================*/
	// ���_���W�̐ݒ�
	g_vertexWkAlfa[0].vtx = D3DXVECTOR3(pos_Alfa.x - (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y - (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[1].vtx = D3DXVECTOR3(pos_Alfa.x + (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y - (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[2].vtx = D3DXVECTOR3(pos_Alfa.x - (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y + (TITLE_ALFA_SIZE_Y / 2), 0.0f);
	g_vertexWkAlfa[3].vtx = D3DXVECTOR3(pos_Alfa.x + (TITLE_ALFA_SIZE_X / 2), pos_Alfa.y + (TITLE_ALFA_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkAlfa[0].rhw =
		g_vertexWkAlfa[1].rhw =
		g_vertexWkAlfa[2].rhw =
		g_vertexWkAlfa[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkAlfa[0].diffuse =
		g_vertexWkAlfa[1].diffuse =
		g_vertexWkAlfa[2].diffuse =
		g_vertexWkAlfa[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 180);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkAlfa[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkAlfa[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkAlfa[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkAlfa[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ Strat�e�L�X�g�̒��_�쐬================*/
	// ���_���W�̐ݒ�
	g_vertexWkStart[0].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[1].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[2].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[3].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkStart[0].rhw =
		g_vertexWkStart[1].rhw =
		g_vertexWkStart[2].rhw =
		g_vertexWkStart[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkStart[0].diffuse =
		g_vertexWkStart[1].diffuse =
		g_vertexWkStart[2].diffuse =
		g_vertexWkStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*================ EXIT�̒��_�쐬================*/
	// ���_���W�̐ݒ�
	g_vertexWkExit[3].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[0].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[1].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[2].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkExit[0].rhw =
		g_vertexWkExit[1].rhw =
		g_vertexWkExit[2].rhw =
		g_vertexWkExit[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkExit[0].diffuse =
		g_vertexWkExit[1].diffuse =
		g_vertexWkExit[2].diffuse =
		g_vertexWkExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkExit[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkExit[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkExit[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkExit[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= �V���[�g�e�L�X�g�̒��_�쐬==============================*/
	g_vertexWkShort[0].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[1].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[2].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[3].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkShort[0].rhw =
		g_vertexWkShort[1].rhw =
		g_vertexWkShort[2].rhw =
		g_vertexWkShort[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkShort[0].diffuse =
		g_vertexWkShort[1].diffuse =
		g_vertexWkShort[2].diffuse =
		g_vertexWkShort[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkShort[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkShort[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkShort[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkShort[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= �~�h���e�L�X�g�̒��_�쐬==============================*/
	g_vertexWkMiddle[0].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[1].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[2].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[3].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkMiddle[0].rhw =
		g_vertexWkMiddle[1].rhw =
		g_vertexWkMiddle[2].rhw =
		g_vertexWkMiddle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkMiddle[0].diffuse =
		g_vertexWkMiddle[1].diffuse =
		g_vertexWkMiddle[2].diffuse =
		g_vertexWkMiddle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkMiddle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkMiddle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkMiddle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkMiddle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= �����O�e�L�X�g�̒��_�쐬==============================*/
	g_vertexWkLong[0].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[1].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[2].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[3].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkLong[0].rhw =
		g_vertexWkLong[1].rhw =
		g_vertexWkLong[2].rhw =
		g_vertexWkLong[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkLong[0].diffuse =
		g_vertexWkLong[1].diffuse =
		g_vertexWkLong[2].diffuse =
		g_vertexWkLong[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLong[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLong[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLong[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLong[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/*============================= �߂�e�L�X�g�̒��_�쐬==============================*/
	g_vertexWkBack[0].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[1].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[2].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[3].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkBack[0].rhw =
		g_vertexWkBack[1].rhw =
		g_vertexWkBack[2].rhw =
		g_vertexWkBack[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkBack[0].diffuse =
		g_vertexWkBack[1].diffuse =
		g_vertexWkBack[2].diffuse =
		g_vertexWkBack[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBack[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBack[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBack[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBack[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexTitle(void)
{
	// =====================================�X�^�[�g���_���W�̐ݒ�
	g_vertexWkStart[0].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[1].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y - (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[2].vtx = D3DXVECTOR3(pos_Start.x - (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);
	g_vertexWkStart[3].vtx = D3DXVECTOR3(pos_Start.x + (TITLE_START_SIZE_X / 2), pos_Start.y + (TITLE_START_SIZE_Y / 2), 0.0f);

	// =====================================�I�����_���W�̐ݒ�
	g_vertexWkExit[3].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[0].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[1].vtx = D3DXVECTOR3(pos_Exit.x + (TITLE_EXIT_SIZE_X / 2), pos_Exit.y - (TITLE_EXIT_SIZE_Y / 2), 0.0f);
	g_vertexWkExit[2].vtx = D3DXVECTOR3(pos_Exit.x - (TITLE_EXIT_SIZE_X / 2), pos_Exit.y + (TITLE_EXIT_SIZE_Y / 2), 0.0f);

	// =====================================�V���[�g���_���W�̐ݒ�
	g_vertexWkShort[0].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[1].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y - (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[2].vtx = D3DXVECTOR3(pos_Short.x - (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);
	g_vertexWkShort[3].vtx = D3DXVECTOR3(pos_Short.x + (TITLE_SHORT_SIZE_X / 2), pos_Short.y + (TITLE_SHORT_SIZE_Y / 2), 0.0f);

	// =====================================�~�h�����_���W�̐ݒ�
	g_vertexWkMiddle[0].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[1].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y - (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[2].vtx = D3DXVECTOR3(pos_Middle.x - (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);
	g_vertexWkMiddle[3].vtx = D3DXVECTOR3(pos_Middle.x + (TITLE_MIDDLE_SIZE_X / 2), pos_Middle.y + (TITLE_MIDDLE_SIZE_Y / 2), 0.0f);

	// =====================================�����O���_���W�̐ݒ�
	g_vertexWkLong[0].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[1].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y - (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[2].vtx = D3DXVECTOR3(pos_Long.x - (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);
	g_vertexWkLong[3].vtx = D3DXVECTOR3(pos_Long.x + (TITLE_LONG_SIZE_X / 2), pos_Long.y + (TITLE_LONG_SIZE_Y / 2), 0.0f);

	// =====================================�߂钸�_���W�̐ݒ�
	g_vertexWkBack[0].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[1].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y - (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[2].vtx = D3DXVECTOR3(pos_Back.x - (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);
	g_vertexWkBack[3].vtx = D3DXVECTOR3(pos_Back.x + (TITLE_BACK_SIZE_X / 2), pos_Back.y + (TITLE_BACK_SIZE_Y / 2), 0.0f);

}

//=============================================================================
// �R�}���h�ړ��֐�
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