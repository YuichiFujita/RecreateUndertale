//============================================================
//
//	�����ݒ��ԏ��� [startStateOption.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateOption.h"
#include "startManager.h"

//************************************************************
//	�q�N���X [CStartStateOption] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateOption::CStartStateOption()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateOption::~CStartStateOption()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateOption::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateOption::Uninit(void)
{
	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateOption::Update(const float fDeltaTime)
{

}