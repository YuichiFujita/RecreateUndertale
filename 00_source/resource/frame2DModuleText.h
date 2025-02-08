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
	// �G�C���A�X��`
	using AMapBuffText = std::map<std::string, CFrame2DTextBuffer*>;	// �e�L�X�g�o�b�t�@�A�z�z��^

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
	void BindBuffTextArray(AMapBuffText* pMapBuffText, const std::string& rFilePath, const std::string& rBoxKey, const std::string& rStartKey = "0");	// �e�L�X�g�o�b�t�@�A�z�z�񊄓�
	HRESULT BindTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// �e�L�X�g�{�b�N�X����
	HRESULT BindText(const std::string& rTextKey);		// �e�L�X�g����
	HRESULT TransText(const std::string& rNextTextKey);	// �e�L�X�g�J��
	HRESULT ChangeState(CFrame2DTextState* pState);		// ��ԕύX
	inline CFrame2DTextState* GetState() const { return m_pState; }	// ��Ԏ擾

	HRESULT PushFrontString(const std::string& rStr, const std::string& rTextKey);	// ������̐擪�ǉ� (�}���`�o�C�g������)
	HRESULT PushFrontString(const std::wstring& rStr, const std::string& rTextKey);	// ������̐擪�ǉ� (���C�h������)
	HRESULT PushBackString(const std::string& rStr, const std::string& rTextKey);	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	HRESULT PushBackString(const std::wstring& rStr, const std::string& rTextKey);	// ������̍Ō���ǉ� (���C�h������)
	int GetNumString(const std::string& rTextKey) const;	// �s���擾
	int GetNumText() const;	// �e�L�X�g���擾

private:
	// �����o�֐�
	void ReleaseBuffText();	// �e�L�X�g�o�b�t�@�A�z�z��j��
	CFrame2DTextBuffer* CreateBuffText(const std::string& rCreateKey, const int nFaceIdx);	// �e�L�X�g�o�b�t�@����
	bool LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// �e�L�X�g�{�b�N�X�Ǎ�
	bool LoadText(std::ifstream* pFile, const std::string& rFilePath);			// �e�L�X�g�Ǎ�
	CFrame2DTextBuffer* LoadString(std::ifstream* pFile, const int nFaceIdx);	// ������Ǎ�

	// �����o�ϐ�
	CFrame2DTextState* m_pState;	// ���
	AMapBuffText* m_pMapBuffText;	// �e�L�X�g�o�b�t�@�A�z�z��
	std::string m_sNextPath;		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	std::string m_sNextBoxKey;		// ���e�L�X�g�{�b�N�X�̌����L�[
	std::string m_sStartKey;		// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
	bool m_bAutoUninitFrame;		// �t���[�������j���t���O
};

#endif	// _FRAME2D_MODULE_TEXT_H_
