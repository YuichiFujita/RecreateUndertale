//============================================================
//
//	�X�^�[�g��ʃw�b�_�[ [sceneStart.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCENE_START_H_
#define _SCENE_START_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CStartManager;	// �X�^�[�g�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�^�[�g��ʃN���X
class CSceneStart : public CScene
{
public:
	// �R���X�g���N�^
	explicit CSceneStart(const EMode mode);

	// �f�X�g���N�^
	~CSceneStart() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

	// �ÓI�����o�֐�
	static CStartManager* GetStartManager();	// �X�^�[�g�}�l�[�W���[�擾

private:
	// �ÓI�����o�ϐ�
	static CStartManager* m_pStartManager;	// �X�^�[�g�}�l�[�W���[
};

#endif	// _SCENE_START_H_
