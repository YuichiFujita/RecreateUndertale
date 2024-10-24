//============================================================
//
//	�Q�[�W2D�w�b�_�[ [gauge2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GAUGE2D_H_
#define _GAUGE2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[�W2D�N���X
class CGauge2D : public CObject
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �ʏ���
		STATE_CHANGE,	// �Q�[�W�ϓ����
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �|���S����
	enum EPolygon
	{
		POLYGON_BACK = 0,	// �w�i
		POLYGON_FRONT,		// �Q�[�W
		POLYGON_FRAME,		// �g
		POLYGON_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CGauge2D(const int nFrame);

	// �f�X�g���N�^
	~CGauge2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	inline VECTOR3 GetVec3Position() const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CGauge2D* Create	// ����
	( // ����
		const int nMax,			// �ő�\���l
		const int nFrame,		// �\���l�ϓ��t���[��
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rSizeGauge = VEC3_ONE,		// �Q�[�W�傫��
		const COLOR& rColFront = color::White(),	// �\�Q�[�W�F
		const COLOR& rColBack = color::Black(),		// ���Q�[�W�F
		const bool bDrawFrame = false,				// �g�`���
		const char* pPathTex = nullptr,				// �t���[���e�N�X�`���p�X
		const VECTOR3& rSizeFrame = VEC3_ONE,		// �g�傫��
		const VECTOR3& rOffsetFrame = VEC3_ONE		// �g�I�t�Z�b�g
	);

	// �����o�֐�
	void BindTexture(const int nPolygonIdx, const int nTextureIdx);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const int nPolygonIdx, const char* pTexturePath);	// �e�N�X�`������ (�p�X)
	int GetTextureIndex(const int nPolygonIdx) const;					// �e�N�X�`���C���f�b�N�X�擾

	void AddNum(const int nAdd);					// �Q�[�W���Z
	void SetNum(const int nNum);					// �Q�[�W�ݒ�
	void SetMaxNum(const int nMax);					// �Q�[�W�ő�l�ݒ�
	void SetOffsetFrame(const VECTOR3& rOffset);	// �g�I�t�Z�b�g�ݒ�
	void SetSizeGauge(const VECTOR3& rSize);		// �Q�[�W�傫���ݒ�
	void SetSizeFrame(const VECTOR3& rSize);		// �w�i�傫���ݒ�
	void SetAlphaFront(const float fAlpha);			// �\�Q�[�W�����x�擾
	void SetColorFront(const COLOR& rCol);			// �\�Q�[�W�F�ݒ�
	void SetAlphaBack(const float fAlpha);			// ���Q�[�W�����x�擾
	void SetColorBack(const COLOR& rCol);			// ���Q�[�W�F�ݒ�
	void SetEnableDrawFrame(const bool bDraw);		// �g�\���󋵐ݒ�
	inline int GetNum() const				{ return m_nNumGauge; }		// �Q�[�W�擾
	inline int GetMaxNum() const			{ return m_nMaxNumGauge; }	// �Q�[�W�ő�l�擾
	inline VECTOR3 GetOffsetFrame() const	{ return m_offsetFrame; }	// �g�I�t�Z�b�g�擾
	inline VECTOR3 GetSizeGauge() const		{ return m_sizeGauge; }		// �Q�[�W�傫���擾
	inline VECTOR3 GetSizeFrame() const		{ return m_sizeFrame; }		// �w�i�傫���擾
	inline float GetAlphaFront() const		{ return m_colFront.a; }	// �\�Q�[�W�����x�擾
	inline COLOR GetColorFront() const		{ return m_colFront; }		// �\�Q�[�W�F�擾
	inline float GetAlphaBack() const		{ return m_colBack.a; }		// ���Q�[�W�����x�擾
	inline COLOR GetColorBack() const		{ return m_colBack; }		// ���Q�[�W�F�擾
	inline bool IsEnableDrawFrame() const	{ return m_bDrawFrame; }	// �g�\���󋵎擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	VECTOR3	m_pos;						// �ʒu
	VECTOR3	m_offsetFrame;				// �g�I�t�Z�b�g
	VECTOR3	m_sizeGauge;				// �Q�[�W�傫��
	VECTOR3	m_sizeFrame;				// �g�傫��
	COLOR	m_colFront;					// �\�Q�[�W�F
	COLOR	m_colBack;					// ���Q�[�W�F
	EState	m_state;					// ���
	bool	m_bDrawFrame;				// �g�\����
	float	m_fChange;					// �Q�[�W�ϓ���
	float	m_fCurrentNumGauge;			// ���ݕ\���l
	float	m_fAddRight;				// �������Z��
	int		m_nCounterState;			// ��ԊǗ��J�E���^�[
	int		m_nNumGauge;				// �\���l
	int		m_nMaxNumGauge;				// �\���l�̍ő�l
	int		m_aTextureIdx[POLYGON_MAX];	// �e�N�X�`���C���f�b�N�X
	const int m_nFrame;					// �\���l�̕ϓ��t���[���萔
};

#endif	// _GAUGE2D_H_
