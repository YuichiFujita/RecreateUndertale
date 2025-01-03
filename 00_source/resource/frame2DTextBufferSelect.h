//============================================================
//
//	�I��t���e�L�X�g�ۑ��o�b�t�@�w�b�_�[ [frame2DTextBufferSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_SELECT_H_
#define _FRAME2D_TEXT_BUFFER_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBuffer.h"
#include "frame2D.h"
#include "frame2DModuleTextSelect.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DModule;	// �t���[��2D�@�\�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferSelect : public CFrame2DTextBuffer
{
public:
	// �R���X�g���N�^
	CFrame2DTextBufferSelect();

	// �f�X�g���N�^
	~CFrame2DTextBufferSelect() override;

	// �I�[�o�[���C�h�֐�
	CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) override;		// �e�L�X�g�@�\����
	void LoadKeyString(std::ifstream* pFile, std::string& rString) override;	// ���݃L�[������Ǎ�
	inline CFrame2DTextBufferSelect* GetSelect() override { return this; }		// �I��t���e�L�X�g�擾

	// �����o�֐�
	void LoadSelect(std::ifstream* pFile, const CFrame2DModuleTextSelect::ESelect select);	// �I����������Ǎ�

	// �����o�ϐ�
	std::string m_aNextTextKey[CFrame2DModuleTextSelect::SELECT_MAX];	// ���e�L�X�g�̌����L�[
	AText m_aSelect[CFrame2DModuleTextSelect::SELECT_MAX];	// �I���e�L�X�g�ۑ�
};

#endif	// _FRAME2D_TEXT_BUFFER_SELECT_H_
