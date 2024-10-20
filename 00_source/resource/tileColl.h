//============================================================
//
//	����^�C���w�b�_�[ [tileColl.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TILE_COLL_H_
#define _TILE_COLL_H_

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
// ����^�C���N���X
class CTileColl : public CObject3D
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_BOX = 0,	// ��`
		TYPE_TRIANGLE,	// �O�p
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTileColl();

	// �f�X�g���N�^
	~CTileColl();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTileColl *Create(const EType type, const VECTOR3& rPos);	// ����
	static CListManager<CTileColl> *GetList(void);	// ���X�g�擾

	static void CollisionTile	// ����^�C���Ƃ̓����蔻��
	( // ����
		VECTOR3& rPosCur,				// ���݈ʒu
		const VECTOR3& rPosOld,			// �ߋ��ʒu
		const VECTOR3& rRot,			// ����
		const CObjectChara2D *pChara2D	// �L�����N�^�[2D���
	);
	static void CollisionTile	// ����^�C���Ƃ̓����蔻��
	( // ����
		VECTOR3& rPosCur,			// ���݈ʒu
		const VECTOR3& rPosOld,		// �ߋ��ʒu
		const VECTOR3& rSizeUp,		// �傫�� (�E/��/��)
		const VECTOR3& rSizeDown	// �傫�� (��/��/�O)
	);

	// �����o�֐�
	void SetType(const EType type);					// ��ސݒ�
	EType GetType(void) const { return m_type; }	// ��ގ擾

private:
	// �ÓI�����o�ϐ�
	static CListManager<CTileColl> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CTileColl>::AIterator m_iterator;	// �C�e���[�^�[
	EType m_type;	// ���
};

#endif	// _TILE_COLL_H_
