//============================================================
//
//	�}�b�v�^�C���w�b�_�[ [tileMap.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �}�b�v�^�C���N���X
class CTileMap : public CObject3D
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NONE = 0,		// �e�N�X�`������
		TYPE_FALL_POINT,	// ���������n�_
		TYPE_RUINS_GATE,	// ���C���Y�����O
		TYPE_RUINS_STAIRS,	// ���C���Y��K�i
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTileMap();

	// �f�X�g���N�^
	~CTileMap();

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTileMap* Create(const EType type, const VECTOR3& rPos);	// ����

	// �����o�֐�
	void SetType(const EType type);					// ��ސݒ�
	inline EType GetType() const { return m_type; }	// ��ގ擾

private:
	// �����o�ϐ�
	EType m_type;	// ���
};

#endif	// _TILE_MAP_H_
