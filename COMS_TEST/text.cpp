//=============================================================================
//
// �e�L�X�g�̏��� [text.cpp]
// Author : ���c����
// ���ώ� : ���
//
//=============================================================================
#include "main.h"
#include "text.h"
#include "event.h"
#include "oneweek.h"
#include "input.h"

#include "text box.h"
//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
TEXT		g_text;
LPD3DXFONT	TextFont = NULL;		// �e�L�X�g�p�̃t�H���g

//=============================================================================
// �e�L�X�g�̏���������
void InitText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXT *text = &g_text;

	D3DXCreateFont(pDevice, FONT_SIZE, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r ����", &TextFont);

	ClearText(&text->textdis[0][0]);
	ClearText(&text->textbuf[0][0]);
	text->order = 0;
	text->currbufrow = 0;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		text->rectPos[i] = { TEXT_POS_X, TEXT_POS_Y + (i * TEXT_ROW_HEIGHT), SCREEN_WIDTH, SCREEN_HEIGHT };
		text->drawcnt[i] = 0;
	}
}

//=============================================================================
// �e�L�X�g�̃[���N���A����
void ClearText(char *text)
{
	memset(text, 0, sizeof(text));
}

//=============================================================================
// �e�L�X�g�̍ŐV����
void UpdateText(void)
{
	TEXT* text = GetText();
	WEEKLOOP* weekloop = GetWeeekloop();
	
	// �`�摬�x�̏���
	if (text->wait > TEST_SPEED)
		text->wait = 0;
	text->wait++;

	// �`�悷�镶�����𑝂₷
	if (text->wait >= TEST_SPEED)
	{
		for (int i = 0; i < TEXT_ROW_MAX; i++)
		{	// �O�̍s���I����ĂāE�`�F�b�N���Ă���s���}�b�N�X�Ɏ����Ă��Ȃ�
			// �܂��́@�ŏ��̍s�ŁE�}�b�N�X�Ɏ����Ă��Ȃ�
			if (text->drawcnt[i - 1] == TEXT_COLUMN_MAX && text->drawcnt[i] != TEXT_COLUMN_MAX 
				|| i == 0 && text->drawcnt[i] < TEXT_COLUMN_MAX)
			{
				text->drawcnt[i]++;
				// �����c�肪�󔒂�������
				if (text->drawcnt[i] > text->drawcntmax[i])
				{
					text->drawcnt[i] = TEXT_COLUMN_MAX;

					// �S���\���ł��Ă�����v���X�{�^������ύX
					if (i == TEXT_ROW_MAX -1 && text->currbufrow == text->rowmax)
					{
						switch (weekloop->status)
						{
						case WEEKLOOP_DAY_START:
							SetTextBoxPress(Idx_PRESS_ENTER);
							break;
						case WEEKLOOP_EVENT:
							SetTextBoxPress(Idx_PRESS_123);
							break;
						case WEEKLOOP_RESULT:
							SetTextBoxPress(Idx_PRESS_ENTER);
							break;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �e�L�X�g�`��֐�
void DrawTextData(void) // DrawText�̓��C�u�����[�̃f�t�@�C���ł��邩��DrawTextData
{
	TEXT *text = &g_text;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		TextFont->DrawText(NULL, &text->textdis[i][0], text->drawcnt[i], &text->rectPos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
	}
}

//=============================================================================
// �e�L�X�g�X�V����
void AdvanceText(void)
{
	TEXT *text = &g_text;

	//===========================================
	// �e�L�X�g�̑�����
	int j = 0;
	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		if (text->drawcnt[i] != TEXT_COLUMN_MAX)
		{
			text->drawcnt[i] = TEXT_COLUMN_MAX;
			break;
		}
		else
			j++;
	}

	//===========================================
	// �S�Ă����܂��Ă���ꍇ�@�V��������ǂݍ���
	if (j == TEXT_ROW_MAX)
	{
		if (text->currbufrow < text->rowmax)
		{
			for (int i = 0; i < TEXT_ROW_MAX; i++)
			{	// ���g�N���A
				memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));
				text->drawcnt[i] = 0;
			}
			for (int i = 0; i < TEXT_ROW_MAX; i++, text->currbufrow++)
			{	// �o�t�@�[����ǂݍ���
				if (text->currbufrow >= text->rowmax)
					break;
				strcpy(&text->textdis[i][0], &text->textbuf[text->currbufrow][0]);
				text->drawcnt[i] = 0;
			}
			for (int i = 0; i < TEXT_ROW_MAX; i++)
			{	// �\�����镶�������Q�b�g
				text->drawcntmax[i] = strlen(text->textdis[i]);
			}
		}
	}
}
//=============================================================================
// �e�L�X�g�擾�֐�
TEXT *GetText(void)
{
	return &g_text;
}