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
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CGauge2D *Create	// ����
	( // ����
		const int nMax,				// �ő�\���l
		const int nFrame,			// �\���l�ϓ��t���[��
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rSizeGauge = VEC3_ONE,	// �Q�[�W�傫��
		const COLOR& rColFront = color::White(),	// �\�Q�[�W�F
		const COLOR& rColBack = color::Black(),		// ���Q�[�W�F
		const bool bDrawFrame = false,				// �g�`���
		const char *pPassTex = nullptr,				// �t���[���e�N�X�`���p�X
		const D3DXVECTOR3& rSizeFrame = VEC3_ONE,	// �g�傫��
		const D3DXVECTOR3& rOffsetFrame = VEC3_ONE	// �g�I�t�Z�b�g
	);

	// �����o�֐�
	void BindTexture(const int nPolygonID, const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const int nPolygonID, const char *pTexturePass);	// �e�N�X�`������ (�p�X)
	int GetTextureIndex(const int nPolygonID) const;					// �e�N�X�`���C���f�b�N�X�擾

	void AddNum(const int nAdd);						// �Q�[�W���Z
	void SetNum(const int nNum);						// �Q�[�W�ݒ�
	void SetMaxNum(const int nMax);						// �Q�[�W�ő�l�ݒ�
	void SetOffsetFrame(const D3DXVECTOR3& rOffset);	// �g�I�t�Z�b�g�ݒ�
	void SetSizeGauge(const D3DXVECTOR3& rSize);		// �Q�[�W�傫���ݒ�
	void SetSizeFrame(const D3DXVECTOR3& rSize);		// �w�i�傫���ݒ�
	void SetAlphaFront(const float fAlpha);				// �\�Q�[�W�����x�擾
	void SetColorFront(const COLOR& rCol);				// �\�Q�[�W�F�ݒ�
	void SetAlphaBack(const float fAlpha);				// ���Q�[�W�����x�擾
	void SetColorBack(const COLOR& rCol);				// ���Q�[�W�F�ݒ�
	void SetEnableDrawFrame(const bool bDraw);			// �g�\���󋵐ݒ�
	int GetNum(void) const					{ return m_nNumGauge; }		// �Q�[�W�擾
	int GetMaxNum(void) const				{ return m_nMaxNumGauge; }	// �Q�[�W�ő�l�擾
	D3DXVECTOR3 GetOffsetFrame(void) const	{ return m_offsetFrame; }	// �g�I�t�Z�b�g�擾
	D3DXVECTOR3 GetSizeGauge(void) const	{ return m_sizeGauge; }		// �Q�[�W�傫���擾
	D3DXVECTOR3 GetSizeFrame(void) const	{ return m_sizeFrame; }		// �w�i�傫���擾
	float GetAlphaFront(void) const			{ return m_colFront.a; }	// �\�Q�[�W�����x�擾
	COLOR GetColorFront(void) const			{ return m_colFront; }		// �\�Q�[�W�F�擾
	float GetAlphaBack(void) const			{ return m_colBack.a; }		// ���Q�[�W�����x�擾
	COLOR GetColorBack(void) const			{ return m_colBack; }		// ���Q�[�W�F�擾
	bool IsEnableDrawFrame(void) const		{ return m_bDrawFrame; }	// �g�\���󋵎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;					// �ʒu
	D3DXVECTOR3	m_offsetFrame;			// �g�I�t�Z�b�g
	D3DXVECTOR3	m_sizeGauge;			// �Q�[�W�傫��
	D3DXVECTOR3	m_sizeFrame;			// �g�傫��
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
	int		m_aTextureID[POLYGON_MAX];	// �e�N�X�`���C���f�b�N�X
	const int m_nFrame;					// �\���l�̕ϓ��t���[���萔
};

#endif	// _GAUGE2D_H_
