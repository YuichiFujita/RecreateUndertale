//============================================================
//
//	�J�ڃ^�C���w�b�_�[ [tileTrans.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TILE_TRANS_H_
#define _TILE_TRANS_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �J�ڃ^�C���N���X
class CTileTrans : public CObject3D
{
public:
	// �R���X�g���N�^
	explicit CTileTrans(const char *pNextPass);

	// �f�X�g���N�^
	~CTileTrans();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTileTrans *Create(const char *pNextPass, const D3DXVECTOR3& rPos);	// ����
	static CListManager<CTileTrans> *GetList(void);	// ���X�g�擾

private:
	// �ÓI�����o�ϐ�
	static CListManager<CTileTrans> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CTileTrans>::AIterator m_iterator;	// �C�e���[�^�[
	const char *m_pNextStagePass;	// �J�ڐ�X�e�[�W�p�X
};

#endif	// _TILE_TRANS_H_
