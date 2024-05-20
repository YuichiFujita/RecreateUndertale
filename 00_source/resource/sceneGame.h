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
class CTimerUI;		// �^�C�}�[UI�N���X
class CCinemaScope;	// �V�l�}�X�R�[�v�N���X
class CPause;		// �|�[�Y�N���X
class CHitStop;		// �q�b�g�X�g�b�v�N���X
class CFlash;		// �t���b�V���N���X

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
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

	// �ÓI�����o�֐�
	static CGameManager	*GetGameManager(void);	// �Q�[���}�l�[�W���[�擾
	static CTimerUI		*GetTimerUI(void);		// �^�C�}�[UI�擾
	static CCinemaScope	*GetCinemaScope(void);	// �V�l�}�X�R�[�v�擾
	static CPause		*GetPause(void);		// �|�[�Y�擾
	static CHitStop		*GetHitStop(void);		// �q�b�g�X�g�b�v�擾
	static CFlash		*GetFlash(void);		// �t���b�V���擾

private:
	// �ÓI�����o�ϐ�
	static CGameManager	*m_pGameManager;	// �Q�[���}�l�[�W���[
	static CTimerUI		*m_pTimerUI;		// �^�C�}�[UI
	static CCinemaScope	*m_pCinemaScope;	// �V�l�}�X�R�[�v
	static CPause		*m_pPause;			// �|�[�Y
	static CHitStop		*m_pHitStop;		// �q�b�g�X�g�b�v
	static CFlash		*m_pFlash;			// �t���b�V��
};

#endif	// _SCENE_GAME_H_
