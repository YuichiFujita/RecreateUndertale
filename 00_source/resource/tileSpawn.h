//============================================================
//
//	�o���^�C���w�b�_�[ [tileSpawn.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TILE_SPAWN_H_
#define _TILE_SPAWN_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �o���^�C���N���X
class CTileSpawn : public CObject3D
{
public:
	// �R���X�g���N�^
	CTileSpawn(const char *pPrevPass);

	// �f�X�g���N�^
	~CTileSpawn();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTileSpawn *Create(const char *pPrevPass, const D3DXVECTOR3& rPos);	// ����

private:
	// �����o�ϐ�
	const std::string m_sPrevStagePass;	// �J�ڌ��X�e�[�W�p�X
};

#endif	// _TILE_SPAWN_H_
