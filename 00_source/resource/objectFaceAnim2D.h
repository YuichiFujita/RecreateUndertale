//============================================================
//
//	�I�u�W�F�N�g�\��A�j���[�V����2D�w�b�_�[ [objectFaceAnim2D.h]	// TODO�F��UI
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTFACE_ANIM2D_H_
#define _OBJECTFACE_ANIM2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim2D.h"
#include "faceAnim2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�\��A�j���[�V����2D�N���X
class CObjectFaceAnim2D : public CAnim2D
{
public:
	// �R���X�g���N�^
	explicit CObjectFaceAnim2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_2D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectFaceAnim2D() override;

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
	static CObjectFaceAnim2D* Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot = VEC3_ZERO);	// ����

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

#endif	// _OBJECTFACE_ANIM2D_H_
