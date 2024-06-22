//============================================================
//
//	�}�b�v�^�C���w�b�_�[ [mapTile.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MAPTILE_H_
#define _MAPTILE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �}�b�v�^�C���N���X
class CMapTile : public CObject3D
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NONE = 0,	// �e�N�X�`������
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CMapTile();

	// �f�X�g���N�^
	~CMapTile();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMapTile *Create(const EType type, const D3DXVECTOR3& rPos);	// ����

	// �����o�֐�
	void SetType(const EType type);					// ��ސݒ�
	EType GetType(void) const { return m_type; }	// ��ގ擾

private:
	// �����o�ϐ�
	EType m_type;	// ���
};

#endif	// _MAPTILE_H_
