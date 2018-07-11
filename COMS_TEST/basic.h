#pragma once
//=============================================================================
//
// ����֗����� [basic.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _BASIC_H_
#define _BASIC_H_

#include "main.h"



//=============================================================================
//�\���̐錾

// �|���S���̍\����
typedef struct
{
	D3DXVECTOR2				Pos;					// �ʒu
	float					Rot;					// ����(��])
	D3DXVECTOR2				Size;					// �傫��

	LPDIRECT3DVERTEXBUFFER9	VtxBuff;				// ���_���̃f�[�^

	int						TexId;					// �ǂ̃e�N�X�`���[���g����
}POLY;


// ���b�V���̍\����
typedef struct
{
	// �}�b�v��̈ʒu�Ȃ�
	D3DXVECTOR3				Pos;					// �ʒu
	D3DXVECTOR3				Rot;					// ����(��])
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)

	// �e�N�X�`���[�E���f��
	LPDIRECT3DVERTEXBUFFER9	VtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				*VtxPos;				// ���_�̏��
	WORD					*IdxBuff;				// �C���f�b�N�X�̐�

	LPD3DXMESH				Mesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			BuffMat;				// �}�e���A�����ւ̃|�C���^
	DWORD					NumMat;					// �}�e���A�����̐�

	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X
	int						TexId;					// �ǂ̃e�N�X�`���[���g����
}MESH;


// �r���{�[�h�̍\����
typedef struct
{
	// �}�b�v��̈ʒu�Ȃ�
	D3DXVECTOR3				Pos;					// �ʒu
	D3DXVECTOR3				Rot;					// ����(��])
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)
	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X

	// �e�N�X�`���[
	int						TexId;					// �e�N�X�`���[�ԍ�		texture id

}BILL;


// �e�̍\����
typedef struct
{
	//	�e
	int						nIdxShadow;				// �eID
	float					fSizeShadow;			// �e�̃T�C�Y
	D3DXCOLOR				colShadow;				// �e�̐F

}SHAD;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT SetBasic2DVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly);
void SetBasic2DPos(POLY *poly);
void SetBasic2DCol(POLY *poly, float r, float g, float b, float a);
void DrawBasic2DObject(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 *vtxbuff, LPDIRECT3DTEXTURE9 *tex);


void DrawBasic3DObject(MESH *mesh, LPDIRECT3DTEXTURE9 tex);

#endif
