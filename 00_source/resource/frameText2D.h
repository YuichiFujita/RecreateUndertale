//============================================================
//
//	�t���[���e�L�X�g2D�w�b�_�[ [frameText2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME_TEXT2D_H_
#define _FRAME_TEXT2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t���[���e�L�X�g2D�N���X
class CFrameText2D : public CFrame2D
{
public:
	// �萔
	static const VECTOR3 POS[];		// �e�L�X�g�{�b�N�X�ʒu
	static const VECTOR3 ROT[];		// �e�L�X�g�{�b�N�X����
	static const VECTOR3 SIZE[];	// �e�L�X�g�{�b�N�X�傫��
	static const VECTOR3 OFFSET[];	// �e�L�X�g�I�t�Z�b�g

	// �z�u��
	enum EPlace
	{
		PLACE_DOWN = 0,	// �����z�u
		PLACE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFrameText2D();

	// �f�X�g���N�^
	~CFrameText2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�

	// �ÓI�����o�֐�
	static CFrameText2D* Create(const EPlace place);	// ���� (�z�u�v���Z�b�g)
	static CFrameText2D* Create	// ���� (�z�u�w��)
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rSize,	// �傫��
		const VECTOR3& rOffset	// �I�t�Z�b�g
	);

	// �����o�֐�
	void ChangeText(const AText& rText);	// �e�L�X�g�ύX
	void SetOffset(const VECTOR3& rOffset);	// �e�L�X�g�I�t�Z�b�g�ݒ�
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const int nStrIdx)		{ m_pText->DeleteString(nStrIdx); }	// ������폜
	inline void DeleteStringAll()					{ m_pText->DeleteStringAll(); }		// ������S�폜
	inline void SetTextEnableDraw(const bool bDraw)	{ m_pText->SetEnableDraw(bDraw); };	// �`��󋵐ݒ�
	inline bool IsTextScroll() const				{ return m_pText->IsScroll(); }		// ��������󋵎擾
	inline VECTOR3 GetOffset() const				{ return m_offset; }				// �e�L�X�g�I�t�Z�b�g�擾

private:
	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CScrollText2D* m_pText;	// �e�L�X�g���
	VECTOR3 m_offset;		// �e�L�X�g�I�t�Z�b�g
};

#endif	// _FRAME_TEXT2D_H_
