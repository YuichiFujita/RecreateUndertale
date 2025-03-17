//============================================================
//
//	�e�L�X�g�@�\��ԃw�b�_�[ [frame2DTextState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_H_
#define _FRAME2D_TEXT_STATE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sound.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DModuleText;			// �e�L�X�g�\���@�\�N���X
class CFrame2DTextBuffer;			// �e�L�X�g���ۑ��o�b�t�@�N���X
class CFrame2DTextStateText;		// �e�L�X�g��ԃN���X
class CFrame2DTextStateSelect;		// �I��t���e�L�X�g��ԃN���X
class CFrame2DTextStateFaceText;	// �\��t���e�L�X�g��ԃN���X
class CFrame2DTextStateFaceSelect;	// �\��/�I��t���e�L�X�g��ԃN���X
class CFrame2DTextStateItem;		// �A�C�e���e�L�X�g��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g�@�\��ԃN���X
class CFrame2DTextState
{
public:
	// �t�H���g��
	enum EFont
	{
		FONT_DEFAULT = 0,	// �f�t�H���g
		FONT_MAX			// ���̗񋓌^�̑���
	};

	// �T�E���h��
	enum ESound
	{
		SOUND_DEFAULT = 0,	// �f�t�H���g
		SOUND_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFrame2DTextState();

	// �f�X�g���N�^
	virtual ~CFrame2DTextState();

	// �������z�֐�
	virtual HRESULT Init()	= 0;	// ������
	virtual void Uninit()	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V
	virtual void BindTextBuffer(CFrame2DTextBuffer* pBuffer) = 0;	// �e�L�X�g���ۑ��o�b�t�@����

	// ���z�֐�
	inline virtual CFrame2DTextStateText* GetStateText()			 { return nullptr; }	// �e�L�X�g��Ԏ擾
	inline virtual CFrame2DTextStateSelect* GetStateSelect()		 { return nullptr; }	// �I��t���e�L�X�g��Ԏ擾
	inline virtual CFrame2DTextStateFaceText* GetStateFaceText()	 { return nullptr; }	// �\��t���e�L�X�g��Ԏ擾
	inline virtual CFrame2DTextStateFaceSelect* GetStateFaceSelect() { return nullptr; }	// �\��/�I��t���e�L�X�g��Ԏ擾
	inline virtual CFrame2DTextStateItem* GetStateItem()			 { return nullptr; }	// �A�C�e���e�L�X�g��Ԏ擾
	inline virtual void SetPriority(const int)			{ assert(false); }	// �D�揇�ʐݒ�
	inline virtual void SetVec3Position(const VECTOR3&)	{ assert(false); }	// �ʒu�ݒ�
	inline virtual void SetVec3Rotation(const VECTOR3&)	{ assert(false); }	// �����ݒ�
	inline virtual void SetVec3Size(const VECTOR3&)		{ assert(false); }	// �傫���ݒ�
	inline virtual void SetFontPath(const EFont /*font*/)		{}	// �t�H���g�p�X�ݒ�
	inline virtual void SetSoundLabel(const ESound /*sound*/)	{}	// �T�E���h���x���ݒ�

	// �����o�֐�
	std::string GetFontPath(const EFont font);			 // �t�H���g�p�X�擾
	CSound::ELabel GetSoundLabel(const ESound sound);	 // �T�E���h���x���擾
	inline void SetContext(CFrame2DModuleText* pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�
	inline void SetCurTextKey(const std::string& rKey)	 { m_sCurTextKey = rKey; }	// �e�L�X�g�����L�[�ݒ�
	inline std::string GetCurTextKey() const			 { return m_sCurTextKey; }	// �e�L�X�g�����L�[�擾

protected:
	// �������z�֐�
	virtual void SetPositionRelative() = 0;	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CFrame2DModuleText* m_pContext;	// �R���e�L�X�g

private:
	// �����o�ϐ�
	std::string m_sCurTextKey;	// �����ς݃e�L�X�g�̌����L�[
	EFont m_font;	// �t�H���g
	ESound m_sound;	// �T�E���h
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"

#endif	// _FRAME2D_TEXT_STATE_H_
