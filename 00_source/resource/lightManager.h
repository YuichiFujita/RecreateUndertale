//============================================================
//
//	���C�g�}�l�[�W���[�w�b�_�[ [lightManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "lightDir.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���C�g�}�l�[�W���[�N���X
class CLightManager
{
public:
	// �萔
	static constexpr int MAX_NUM = 4;	// �g�p���C�g��

	// �R���X�g���N�^
	CLightManager();

	// �f�X�g���N�^
	~CLightManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V
	inline D3DLIGHT9 GetLight(const int nIdx) { return m_apLight[nIdx]->GetLight(); }	// ���C�g�擾

	// �ÓI�����o�֐�
	static CLightManager* Create();	// ����
	static void Release(CLightManager*& prLightManager);	// �j��

private:
	// �����o�ϐ�
	CLightDir* m_apLight[MAX_NUM];	// ���C�g���
};

#endif	// _LIGHT_MANAGER_H_
