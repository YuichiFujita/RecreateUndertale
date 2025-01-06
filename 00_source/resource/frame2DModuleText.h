//============================================================
//
//	�e�L�X�g�\���@�\�w�b�_�[ [frame2DModuleText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_MODULE_TEXT_H_
#define _FRAME2D_MODULE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModule.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextState;	// �e�L�X�g�@�\��ԃN���X
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g�\���@�\�N���X
class CFrame2DModuleText : public CFrame2DModule
{
public:
	// �R���X�g���N�^
	CFrame2DModuleText(const bool bAutoUninit = true);

	// �f�X�g���N�^
	~CFrame2DModuleText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline CFrame2DModuleText* GetModuleText() override	{ return this; }	// �e�L�X�g�\���@�\�擾

	// �����o�֐�
	HRESULT BindTextBox(const std::string& rFilePath, const std::string& rBoxKey, const std::string& rNextStartKey = "0");	// �e�L�X�g�{�b�N�X����
	void TransText(const std::string& rNextTextKey);				// �e�L�X�g�J��
	HRESULT ChangeState(CFrame2DTextState* pState);					// ��ԕύX
	inline CFrame2DTextState* GetState() const { return m_pState; }	// ��Ԏ擾

private:
	// �����o�֐�
	HRESULT BindText(const std::string& rTextKey);	// �e�L�X�g����
	void DeleteBuffText();							// �e�L�X�g�o�b�t�@�A�z�z��폜
	CFrame2DTextBuffer* CreateBuffText(const std::string& rCreateKey);				// �e�L�X�g�o�b�t�@����
	HRESULT LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// �e�L�X�g�{�b�N�X�Ǎ�
	void LoadText(std::ifstream* pFile);					// �e�L�X�g�Ǎ�
	CFrame2DTextBuffer* LoadString(std::ifstream* pFile);	// ������Ǎ�

	// �����o�ϐ�
	std::map<std::string, CFrame2DTextBuffer*> m_mapBuffText;	// �e�L�X�g�o�b�t�@�A�z�z��
	CFrame2DTextState* m_pState;	// ���
	std::string m_sNextPath;		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	std::string m_sNextBoxKey;		// ���e�L�X�g�{�b�N�X�̌����L�[
	std::string m_sNextStartKey;	// ���e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
	bool m_bAutoUninitFrame;		// �t���[�������j���t���O
};

#endif	// _FRAME2D_MODULE_TEXT_H_
