//============================================================
//
//	�\��UI�w�b�_�[ [faceUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FACE_UI_H_
#define _FACE_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim2D.h"
#include "faceAnim2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �\��UI�N���X
class CFaceUI : public CAnim2D
{
public:
	// �R���X�g���N�^
	CFaceUI();

	// �f�X�g���N�^
	~CFaceUI() override;

	// �G�C���A�X��`
	using AEmotion = CFaceAnim2D::SEmotion;	// �\��Ǘ��^
	using AFace = CFaceAnim2D::SFace;		// ��Ǘ��^

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�

	// �ÓI�����o�֐�
	static CFaceUI* Create	// ����
	( // ����
		const int nIdxFace,				// ��C���f�b�N�X
		const int nTypeEmo,				// �\����
		const VECTOR3& rPos,			// �ʒu
		const VECTOR3& rRot = VEC3_ZERO	// ����
	);

	// �����o�֐�
	void BindFaceData(const int nIdxFace);	// �犄��
	void SetEmotion(const int nTypeEmo);	// �\��ݒ�
	void AddInfo(const AEmotion& rEmotion);	// �\��ǉ�
	void SetAllInfo(const AFace& rFace);	// �\��S�ݒ�
	inline VECTOR3 GetOriginPosition() const	{ return m_pos; }		// ���_�ʒu�擾
	inline int GetEmotion() const	{ return m_nTypeEmo; }				// �\��擾
	inline int GetNumEmotion()		{ return m_info.GetNumEmotion(); }	// �\����擾

private:
	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	VECTOR3 m_pos;	// ���_�ʒu
	AFace m_info;	// �\����
	int m_nTypeEmo;	// �\����
};

#endif	// _FACE_UI_H_
