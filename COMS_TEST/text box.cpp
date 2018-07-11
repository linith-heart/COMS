//=============================================================================
//
// �e�L�X�g�{�b�N�X�̏��� [text box.cpp]
// Author : ���ꐶ
//=============================================================================
#include "main.h"
#include "text box.h"

#include "input.h"

//=============================================================================
// �}�N����`
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// �e�L�X�g�{�b�N�X�̃e�N�X�`���[�p�X
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// �e�L�X�g�{�b�N�X�̈ʒu
#define TEXT_BOX_POS_Y		((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/4))
#define TEXT_BOX_SIZE_X		(1205)				// �e�L�X�g�{�b�N�X�̑傫��(�s�N�Z�����̑傫��)
#define TEXT_BOX_SIZE_Y		(300)

#define TEXT_BOX_PRESS_SPACE_PATH	("data/texture/ui/press space.png")
#define TEXT_BOX_PRESS_ENTER_PATH	("data/texture/ui/press enter.png")
#define TEXT_BOX_PRESS_123_PATH		("data/texture/ui/press 123.png")

#define TEXT_BOX_PRESS_SIZE_X	(147)			// �傫��(��m�̃s�N�Z���̑傫��)
#define TEXT_BOX_PRESS_SIZE_Y	(25)
#define TEXT_BOX_PRESS_POS_X	(TEXT_BOX_POS_X + (TEXT_BOX_SIZE_X / 2) - TEXT_BOX_PRESS_SIZE_X) // �e�L�X�g�{�b�N�X�̉E���̊p�ɐݒu
#define TEXT_BOX_PRESS_POS_Y	(TEXT_BOX_POS_Y + (TEXT_BOX_SIZE_Y / 2) - TEXT_BOX_PRESS_SIZE_Y)

#define TEXT_BOX_ALPHA_RATE	(0.02)				// �A���t�@�̕ϊ��ʁE�ϊ����x

//=============================================================================
// �v���g�^�C�v�錾
void TextBoxAlphaSetting(void);
void PressAlphaSetting(void);

//=============================================================================
// �O���[�o���ϐ�
TEXTBOX					gTextBoxWk;				// �\����
LPDIRECT3DTEXTURE9		gTextBoxTexture;		// �e�N�X�`��

TEXTBOXPRESS			gTextBoxPressWk;		// �\����
LPDIRECT3DTEXTURE9		gTextBoxPressTexture[TEX_BOX_PRESS_MAX];		// �e�N�X�`��

//=============================================================================
// �e�L�X�g���[�h�̏���������
void InitTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// �e�N�X�`���̓ǂݍ��� 
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
// �I������
void UninitTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// ���W�f�[�^�̉��
	SAFE_RELEASE(texbox->poly.VtxBuff);

	// �e�N�X�`���̉��
	SAFE_RELEASE(gTextBoxTexture);

	SAFE_RELEASE(press->poly.VtxBuff);

	for (int i = 0; i < TEX_BOX_PRESS_MAX; i++)
	{
		SAFE_RELEASE(gTextBoxPressTexture[i]);
	}
}

//=============================================================================
// �ŐV����
void UpdateTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	// �������΂���
	if (!texbox->use)
		return;

	// �g��Ȃ��Ȃ瓧���ɂ���
	if (!press->use)
		press->isfade = false;


	// �L�[���͂ŕ\�����邩
	if (GetKeyboardTrigger(DIK_0))
	{
		if (texbox->display)
			texbox->display = false;
		else
			texbox->display = true;
	}

	// �A���t�@�̕ϊ�����
	TextBoxAlphaSetting();
	PressAlphaSetting();
}

//=============================================================================
// �`�揈��
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
// �e�L�X�g�{�b�N�X�̃A���t�@�̏���
void TextBoxAlphaSetting(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	float alphacheck = texbox->alpha;

	// �����x�������鏈��
	if (texbox->display)
		if (texbox->alpha < 1.0f)
			texbox->alpha += TEXT_BOX_ALPHA_RATE;

	// �����x�������鏈��
	if (!texbox->display)
		if (texbox->alpha > 0.0f)
			texbox->alpha -= TEXT_BOX_ALPHA_RATE;

	// �F�̕ϊ�
	if (alphacheck != texbox->alpha)	// �f�[�^���ꏏ�Ȃ珈�����Ȃ�
		SetBasic2DCol(&texbox->poly, 1.0f, 1.0f, 1.0f, texbox->alpha);
}

//=============================================================================
// �v���X�{�^���̃A���t�@�̏���
void PressAlphaSetting(void)
{
	TEXTBOXPRESS *press = &gTextBoxPressWk;

	float alphacheck = press->alpha;

	// �����x�������鏈��
	if (press->isfade)
	{
		if (press->alpha < 1.0f)
			press->alpha += TEXT_BOX_ALPHA_RATE;
		else
			press->isfade = false;
	}

	// �����x�������鏈��
	if (!press->isfade)
	{
		if (press->alpha > 0.0f)
			press->alpha -= TEXT_BOX_ALPHA_RATE;
		else
			press->isfade = true;
	}

	// �F�̕ϊ�
	if (alphacheck != press->alpha)	// �f�[�^���ꏏ�Ȃ珈�����Ȃ�
		SetBasic2DCol(&press->poly, 1.0f, 1.0f, 1.0f, press->alpha);
}

void SetTextBoxPress(int no)
{
	TEXTBOXPRESS *press = &gTextBoxPressWk;
	press->poly.TexId = no;
}