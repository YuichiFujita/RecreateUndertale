//============================================================
//
//	�I�u�W�F�N�g�����L�����N�^�[�w�b�_�[ [objectDivChara.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_DIVCHARA_H_
#define _OBJECT_DIVCHARA_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "objectChara.h"
#include "motion.h"

//************************************************************
//	�O���錾
//************************************************************
class CMultiModel;	// �}���`���f���N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�����L�����N�^�[�N���X
class CObjectDivChara : public CObject
{
public:
	// �g�̗�
	enum EBody
	{
		BODY_LOWER = 0,	// �����g
		BODY_UPPER,		// �㔼�g
		BODY_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectDivChara(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectDivChara() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetEnableUpdate(const bool bUpdate) override;		// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_apBody[BODY_LOWER]->GetVec3Position(); }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_apBody[BODY_LOWER]->GetVec3Rotation(); }	// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return m_apBody[BODY_LOWER]->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_apBody[BODY_LOWER]->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectDivChara *Create	// ����
	( // ����
		const D3DXVECTOR3 &rPos,				// �ʒu
		const D3DXVECTOR3 &rRot = VEC3_ZERO,	// ����
		const int nUpperParentID = 0			// �㔼�g�e�C���f�b�N�X
	);

	// ���z�֐�
	virtual void SetMotion	// ���[�V�����ݒ�
	( // ����
		const EBody bodyID,			// �g�̃C���f�b�N�X
		const int nType,			// ���[�V�������
		const int nBlendFrame = 0	// �u�����h�t���[��
	);

	// �����o�֐�
	void SetPartsInfo	// �p�[�c���ݒ�
	( // ����
		const EBody bodyID,			// �g�̃C���f�b�N�X
		const int nID,				// �p�[�c�C���f�b�N�X
		const int nParentID,		// �e�C���f�b�N�X
		const D3DXVECTOR3 &rPos,	// �ʒu
		const D3DXVECTOR3 &rRot,	// ����
		const char *pFileName		// �t�@�C����
	);
	void SetMaterial	// �}�e���A���ݒ�
	( // ����
		const D3DXMATERIAL &rMat,	// �ݒ�}�e���A��
		const EBody bodyID,			// �g�̃C���f�b�N�X
		const int nPartsID,			// �p�[�c�C���f�b�N�X
		const int nMatID			// �}�e���A���C���f�b�N�X
	);

	void BindCharaData	// �L�����N�^�[��񊄓�
	( // ����
		const char *pCharaPassLower,	// �����g�L�������p�X
		const char *pCharaPassUpper		// �㔼�g�L�������p�X
	);
	void SetEnableMotionUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void AddMotionInfo(const EBody bodyID, const CMotion::SMotion& rInfo);	// ���[�V�������ǉ�

	int  GetMotionType(const EBody bodyID) const;			// ���[�V������ގ擾
	int  GetMotionNumType(const EBody bodyID) const;		// ���[�V������ޑ����擾
	int  GetMotionKey(const EBody bodyID) const;			// ���[�V�����L�[�ԍ��擾
	int  GetMotionNumKey(const EBody bodyID) const;			// ���[�V�����L�[�����擾
	int  GetMotionKeyCounter(const EBody bodyID) const;		// ���[�V�����L�[�J�E���^�[�擾
	int  GetMotionWholeCounter(const EBody bodyID) const;	// ���[�V�����S�̃J�E���^�[�擾
	int  GetMotionWholeFrame(const EBody bodyID) const;		// ���[�V�����S�̃t���[�����擾
	int  GetMotionCancelFrame(const EBody bodyID) const;	// ���[�V�����L�����Z���t���[���擾
	int  GetMotionComboFrame(const EBody bodyID) const;		// ���[�V�����R���{�t���[���擾
	bool IsMotionFinish(const EBody bodyID) const;			// ���[�V�����I���擾
	bool IsMotionLoop(const EBody bodyID) const;			// ���[�V�������[�v�擾
	bool IsMotionCancel(const EBody bodyID) const;			// ���[�V�����L�����Z���擾
	bool IsMotionCombo(const EBody bodyID) const;			// ���[�V�����R���{�擾
	bool IsWeaponDisp(const EBody bodyID) const;			// ���[�V��������\���擾
	bool IsLeftWeaponCollision(const EBody bodyID) const;	// ���̍U������t���O�擾
	bool IsRightWeaponCollision(const EBody bodyID) const;	// �E�̍U������t���O�擾

	void SetPartsPosition(const EBody bodyID, const int nPartsID, const D3DXVECTOR3 &rPos);	// �p�[�c�ʒu�ݒ�
	void SetPartsRotation(const EBody bodyID, const int nPartsID, const D3DXVECTOR3 &rRot);	// �p�[�c�����ݒ�
	D3DXVECTOR3 GetPartsPosition(const EBody bodyID, const int nPartsID) const;				// �p�[�c�ʒu�擾
	D3DXVECTOR3 GetPartsRotation(const EBody bodyID, const int nPartsID) const;				// �p�[�c�����擾

	void SetAllMaterial(const D3DXMATERIAL& rMat);	// �}�e���A���S�ݒ�
	void ResetMaterial(void);			// �}�e���A���Đݒ�
	void SetAlpha(const float fAlpha);	// �����x�ݒ�
	float GetAlpha(void) const;			// �����x�擾
	float GetMaxAlpha(void) const;		// �ő哧���x�擾
	void SetUpperParentID(const int nUpperParentID);		// �㔼�g�̐e�C���f�b�N�X�ݒ�
	CObjectChara *GetObjectChara(const EBody bodyID) const;	// �I�u�W�F�N�g�L�����N�^�[�擾
	CMultiModel *GetMultiModel(const EBody bodyID, const int nModelID) const;	// �}���`���f���擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CObjectChara *m_apBody[BODY_MAX];	// �g�̂̏��
	int m_nUpperParentID;	// �㔼�g�e�C���f�b�N�X
};

#endif	// _OBJECT_DIVCHARA_H_
