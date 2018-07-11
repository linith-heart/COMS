//=============================================================================
//
// ����֗��֐� [basic.cpp]
// Author : ���ꐶ
/*
�悭�g����`��Ȃǂ̃R�[�h���֐����������̃��C�u����


libary for code that is used farly commonly
*/
//=============================================================================
#include "main.h"
#include "basic.h"

//=============================================================================
// �O���[�o���ϐ�
POLY			polyWK;
BILL			billWk;
MESH			meshWk;

//=============================================================================
// 2�����̃I�u�W�F�N�g�̈ʒu�ϊ�
void SetBasic2DPos(POLY *poly)
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���ˌ��̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);

	// ���_�f�[�^���A�����b�N����
	poly->VtxBuff->Unlock();

}

//=============================================================================
// 2�����̂�b�W�F�N�g�̐F�̕ϊ�����
void SetBasic2DCol(POLY *poly, float r, float g, float b, float a)
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

	// ���_�f�[�^���A�����b�N����
	poly->VtxBuff->Unlock();
}

//=============================================================================
// 2�����̃I�u�W�F�N�g�̕`��֐�
void DrawBasic2DObject(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 *vtxbuff, LPDIRECT3DTEXTURE9 *tex)
{
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, *vtxbuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, *tex);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// ���b�V���̃I�u�W�F�N�g�̕`��֐�
void DrawBasic3DObject(MESH *mesh, LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���N�X������
	D3DXMatrixIdentity(&mesh->mtxWorld);

	// �X�P�[���𔽉f	(S)
	D3DXMatrixScaling(&mtxScl, mesh->Scl.x, mesh->Scl.y, mesh->Scl.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxScl); 	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxScl
																						// ��]�𔽉f		(R)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->Rot.y, mesh->Rot.x, mesh->Rot.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxRot
																						// ���s�ړ��𔽉f	(T)
	D3DXMatrixTranslation(&mtxTranslate, mesh->Pos.x, mesh->Pos.y, mesh->Pos.z);
	D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

	// ���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ւ̃|�C���^��
	pD3DXMat = (D3DXMATERIAL*)mesh->BuffMat->GetBufferPointer();

	int i;
	for (i = 0; i < (int)mesh->NumMat; i++)
	{
		
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	// �}�e���A���̐ݒ�

		pDevice->SetTexture(0, tex);	// �e�N�X�`���̐ݒ�
		mesh->Mesh->DrawSubset(i);
	}

	// �}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);
}


HRESULT SetBasic2DVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&poly->VtxBuff,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y + poly->Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y + poly->Size.y, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		poly->VtxBuff->Unlock();
	}
}