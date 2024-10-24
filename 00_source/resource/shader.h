//============================================================
//
//	�V�F�[�_�[�w�b�_�[ [shader.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "texture.h"

//************************************************************
//	�N���X��`
//************************************************************
// �V�F�[�_�[�N���X
class CShader
{
public:
	// �R���X�g���N�^
	CShader();

	// �f�X�g���N�^
	virtual ~CShader();

	// ���z�֐�
	virtual HRESULT Init();	// ������
	virtual void Uninit();	// �I��
	virtual void SetLightDirect(MATRIX* pMtxWorld, const int nLightIdx);	// ���C�g�����x�N�g���ݒ�
	virtual void SetTexture(const CTexture::STexture& rTexture);			// �e�N�X�`���ݒ� (�|�C���^)
	virtual void SetTexture(const int nTextureIdx);							// �e�N�X�`���ݒ� (�C���f�b�N�X)
	virtual void SetMaterial(const D3DMATERIAL9& rMaterial);				// �}�e���A���ݒ�
	virtual void SetDiffuse(const COLOR& rDiffuse);							// �g�U���ݒ�
	virtual void SetAmbient(const COLOR& rAmbient);							// �����ݒ�
	virtual void SetEmissive(const COLOR& rEmissive);						// ���ˌ��ݒ�
	virtual void SetOnlyDiffuse(const COLOR& rDiffuse);						// �g�U���̂ݐݒ�

	// �����o�֐�
	void Begin();						// �J�n
	void BeginPass(const BYTE pass);	// �p�X�J�n
	void EndPass();						// �p�X�I��
	void End();							// �I��
	void SetMatrix(MATRIX* pMtxWorld);	// �}�g���b�N�X�ݒ�
	void CommitChanges();				// ��ԕύX�̓`�B
	bool IsEffectOK() const;			// �G�t�F�N�g�g�p�\�󋵂̎擾
	LPD3DXEFFECT GetEffect() const;		// �G�t�F�N�g�|�C���^�擾

	// �ÓI�����o�֐�
	static HRESULT Create();	// ����
	static void Release();		// �j��

protected:
	// �����o�֐�
	void SetEffect(const LPD3DXEFFECT pEffect);			// �G�t�F�N�g�|�C���^�ݒ�
	void SetTechnique(const D3DXHANDLE pTechnique);		// �e�N�j�b�N�֐��ݒ�
	inline void SetMatrixWorld(const D3DXHANDLE pMtxWorld)		{ m_pMtxWorld = pMtxWorld; }		// ���[���h�}�g���b�N�X�ݒ�
	inline void SetMatrixView(const D3DXHANDLE pMtxView)		{ m_pMtxView = pMtxView; }			// �r���[�}�g���b�N�X�ݒ�
	inline void SetMatrixProjection(const D3DXHANDLE pMtxProj)	{ m_pMtxProjection = pMtxProj; }	// �v���W�F�N�V�����}�g���b�N�X�ݒ�

private:
	// �����o�ϐ�
	LPD3DXEFFECT m_pEffect;			// �G�t�F�N�g�|�C���^
	D3DXHANDLE m_pTechnique;		// �e�N�j�b�N�֐�
	D3DXHANDLE m_pMtxWorld;			// ���[���h�}�g���b�N�X
	D3DXHANDLE m_pMtxView;			// �r���[�}�g���b�N�X
	D3DXHANDLE m_pMtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
};

#endif	// _SHADER_H_
