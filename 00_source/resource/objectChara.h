//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[�w�b�_�[ [objectChara.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTCHARA_H_
#define _OBJECTCHARA_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "motion.h"
#include "character.h"

//************************************************************
//	�O���錾
//************************************************************
class CMultiModel;	// �}���`���f���N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�L�����N�^�[�N���X
class CObjectChara : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectChara(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectChara() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Scale(const VECTOR3& rScale) override;	// �g�嗦�ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }		// �����擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectChara* Create(const VECTOR3& rPos, const VECTOR3& rRot = VEC3_ZERO);	// ����

	// ���z�֐�
	virtual void SetMotion(const int nType, const int nBlendFrame = 0);	// ���[�V�����ݒ�

	// �����o�֐�
	void SetPartsInfo	// �p�[�c���ݒ�
	( // ����
		const int nPartsIdx,	// �p�[�c�C���f�b�N�X
		const int nParentIdx,	// �e�C���f�b�N�X
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const char* pFileName	// �t�@�C����
	);

	void BindCharaData(const char* pCharaPath);	// �L�����N�^�[��񊄓�
	void SetNumParts(const int nNumParts);		// �p�[�c���ݒ�
	void SetPartsInfoAll(CCharacter::SPartsInfo& rInfo);					// �p�[�c���S�ݒ�
	void SetPartsPosition(const int nPartsIdx, const VECTOR3& rPos);		// �p�[�c�ʒu�ݒ�
	void SetPartsRotation(const int nPartsIdx, const VECTOR3& rRot);		// �p�[�c�����ݒ�
	VECTOR3 GetPartsPosition(const int nPartsIdx) const;					// �p�[�c�ʒu�擾
	VECTOR3 GetPartsRotation(const int nPartsIdx) const;					// �p�[�c�����擾
	CMultiModel* GetParts(const int nPartsIdx) const;						// �p�[�c�擾
	inline CMotion* GetMotion() const	{ return m_pMotion; }				// ���[�V�����擾
	inline int GetNumParts() const		{ return (int)m_vecParts.size(); }	// �p�[�c���擾

	void SetMaterial(const D3DXMATERIAL& rMat, const int nPartsIdx, const int nMatIdx);	// �}�e���A���ݒ�
	void SetAllMaterial(const D3DXMATERIAL& rMat);	// �}�e���A���S�ݒ�
	void ResetMaterial();				// �}�e���A���Đݒ�
	void SetAlpha(const float fAlpha);	// �����x�ݒ�
	float GetAlpha() const;				// �����x�擾
	float GetMaxAlpha() const;			// �ő哧���x�擾

	inline void AddMotionInfo(const CMotion::SMotion& rInfo)	{ m_pMotion->AddInfo(rInfo); }				// ���[�V�������ǉ�
	inline void SetEnableMotionUpdate(const bool bUpdate)		{ m_pMotion->SetEnableUpdate(bUpdate); }	// �X�V�󋵐ݒ�
	inline int GetMotionType() const			{ return m_pMotion->GetType(); }							// ���[�V������ގ擾
	inline int GetMotionNumType() const			{ return m_pMotion->GetNumType(); }							// ���[�V������ޑ����擾
	inline int GetMotionKey() const				{ return m_pMotion->GetKey();}								// ���[�V�����L�[�ԍ��擾
	inline int GetMotionNumKey() const			{ return m_pMotion->GetNumKey(m_pMotion->GetType()); }		// ���[�V�����L�[�����擾
	inline int GetMotionKeyCounter() const		{ return m_pMotion->GetKeyCounter(); }						// ���[�V�����L�[�J�E���^�[�擾
	inline int GetMotionWholeCounter() const	{ return m_pMotion->GetWholeCounter(); }					// ���[�V�����S�̃J�E���^�[�擾
	inline int GetMotionWholeFrame() const		{ return m_pMotion->GetWholeFrame(m_pMotion->GetType()); }	// ���[�V�����S�̃t���[�����擾
	inline int GetMotionCancelFrame() const		{ return m_pMotion->GetCancelFrame(m_pMotion->GetType()); }	// ���[�V�����L�����Z���t���[���擾
	inline int GetMotionComboFrame() const		{ return m_pMotion->GetComboFrame(m_pMotion->GetType()); }	// ���[�V�����R���{�t���[���擾
	inline bool IsMotionFinish() const			{ return m_pMotion->IsFinish(); }							// ���[�V�����I���擾
	inline bool IsMotionLoop() const			{ return m_pMotion->IsLoop(m_pMotion->GetType()); }			// ���[�V�������[�v�擾
	inline bool IsMotionCancel() const			{ return m_pMotion->IsCancel(m_pMotion->GetType()); }		// ���[�V�����L�����Z���擾
	inline bool IsMotionCombo() const			{ return m_pMotion->IsCombo(m_pMotion->GetType()); }		// ���[�V�����R���{�擾
	inline bool IsWeaponDisp() const			{ return m_pMotion->IsWeaponDisp(m_pMotion->GetType()); }	// ���[�V��������\���擾
	inline bool IsLeftWeaponCollision()			{ return m_pMotion->IsLeftWeaponCollision(); }				// ���̍U������t���O�擾
	inline bool IsRightWeaponCollision()		{ return m_pMotion->IsRightWeaponCollision(); }				// �E�̍U������t���O�擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	std::vector<CMultiModel*> m_vecParts;	// �p�[�c���
	CMotion* m_pMotion;		// ���[�V�����̏��
	MATRIX	 m_mtxWorld;	// ���[���h�}�g���b�N�X
	VECTOR3	 m_pos;			// �ʒu
	VECTOR3	 m_rot;			// ����
};

#endif	// _OBJECTCHARA_H_
