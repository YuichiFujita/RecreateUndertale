//============================================================
//
//	����^�C���w�b�_�[ [collTile.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _COLLTILE_H_
#define _COLLTILE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// ����^�C���N���X
class CCollTile : public CObject3D
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
	CCollTile();

	// �f�X�g���N�^
	~CCollTile();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CCollTile *Create(const EType type, const D3DXVECTOR3& rPos);	// ����
	static CListManager<CCollTile> *GetList(void);	// ���X�g�擾
	static bool CollisionTile	// ����^�C���Ƃ̓����蔻��
	( // ����
		D3DXVECTOR3& rPos,			// �ʒu
		const D3DXVECTOR3& rPosOld,	// �ߋ��ʒu
		const D3DXVECTOR3& rSize	// �傫��
	);

	// �����o�֐�
	void SetType(const EType type);					// ��ސݒ�
	EType GetType(void) const { return m_type; }	// ��ގ擾

private:
	// �ÓI�����o�ϐ�
	static CListManager<CCollTile> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CCollTile>::AIterator m_iterator;	// �C�e���[�^�[
	EType m_type;	// ���
};

#endif	// _COLLTILE_H_
