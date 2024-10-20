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
//	�O���錾
//************************************************************
class CObjectChara2D;	// �I�u�W�F�N�g�L�����N�^�[2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �J�ڃ^�C���N���X
class CTileTrans : public CObject3D
{
public:
	// �R���X�g���N�^
	explicit CTileTrans(const char* pNextPath);

	// �f�X�g���N�^
	~CTileTrans();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTileTrans* Create(const char* pNextPath, const VECTOR3& rPos);	// ����
	static CListManager<CTileTrans>* GetList(void);	// ���X�g�擾

	static void CollisionTile	// �J�ڃ^�C���Ƃ̓����蔻��
	( // ����
		const VECTOR3& rPos,			// �ʒu
		const VECTOR3& rRot,			// ����
		const CObjectChara2D* pChara2D	// �L�����N�^�[2D���
	);
	static void CollisionTile	// �J�ڃ^�C���Ƃ̓����蔻��
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSizeUp,		// �傫�� (�E/��/��)
		const VECTOR3& rSizeDown	// �傫�� (��/��/�O)
	);

private:
	// �ÓI�����o�ϐ�
	static CListManager<CTileTrans>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CTileTrans>::AIterator m_iterator;	// �C�e���[�^�[
	const std::string m_sNextStagePath;	// �J�ڐ�X�e�[�W�p�X
};

#endif	// _TILE_TRANS_H_
