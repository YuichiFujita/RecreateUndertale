//============================================================
//
//	�Q�[����ʃw�b�_�[ [sceneGame.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CGameManager;	// �Q�[���}�l�[�W���[�N���X
class CPause;		// �|�[�Y�N���X
class CStage;		// �X�e�[�W�N���X
class CPlayer;		// �v���C���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[����ʃN���X
class CSceneGame : public CScene
{
public:
	// �R���X�g���N�^
	explicit CSceneGame(const EMode mode);

	// �f�X�g���N�^
	~CSceneGame() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

	// �ÓI�����o�֐�
	static CGameManager* GetGameManager();	// �Q�[���}�l�[�W���[�擾
	static CPause* GetPause();		// �|�[�Y�擾
	static CStage* GetStage();		// �X�e�[�W�擾
	static CPlayer* GetPlayer();	// �v���C���[�擾

private:
	// �ÓI�����o�ϐ�
	static CGameManager* m_pGameManager;	// �Q�[���}�l�[�W���[
	static CPause* m_pPause;	// �|�[�Y���
	static CStage* m_pStage;	// �X�e�[�W���
};

#endif	// _SCENE_GAME_H_
