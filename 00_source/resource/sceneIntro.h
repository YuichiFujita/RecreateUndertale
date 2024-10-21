//============================================================
//
//	�C���g����ʃw�b�_�[ [sceneIntro.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCENE_INTRO_H_
#define _SCENE_INTRO_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CIntroManager;	// �C���g���}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g����ʃN���X
class CSceneIntro : public CScene
{
public:
	// �R���X�g���N�^
	explicit CSceneIntro(const EMode mode);

	// �f�X�g���N�^
	~CSceneIntro() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

	// �ÓI�����o�֐�
	static CIntroManager* GetIntroManager();	// �C���g���}�l�[�W���[�擾

private:
	// �ÓI�����o�ϐ�
	static CIntroManager* m_pIntroManager;	// �C���g���}�l�[�W���[
};

#endif	// _SCENE_INTRO_H_
