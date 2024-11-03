//============================================================
//
//	�����_���[�w�b�_�[ [renderer.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "renderTexture.h"

//************************************************************
//	�O���錾
//************************************************************
class CScreen;	// �X�N���[���N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����_���[�N���X
class CRenderer
{
public:
	// �萔
	static constexpr D3DCOLOR COL_CLEAR = D3DCOLOR_RGBA(0, 0, 0, 0);	// ��ʃN���A���̐F

	// �R���X�g���N�^
	CRenderer();

	// �f�X�g���N�^
	~CRenderer();

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ������
	void Uninit();							// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Draw();							// �`��
	HRESULT CreateRenderTexture();			// �����_�[�e�N�X�`���[����
	void DrawRenderTexture(LPDIRECT3DSURFACE9* pSurface);	// �����_�[�e�N�X�`���`��

	inline LPDIRECT3DDEVICE9 GetDevice() const	{ return m_pD3DDevice; }						// �f�o�C�X�擾
	inline int GetRenderTextureIndex() const	{ return m_pRenderScene->GetTextureIndex(); }	// �����_�[�e�N�X�`���C���f�b�N�X�擾

	// �ÓI�����o�֐�
	static CRenderer* Create(HWND hWnd, BOOL bWindow);	// ����
	static void Release(CRenderer*& prRenderer);		// �j��

private:
	// �����o�֐�
	HRESULT CreateDevice(HWND hWnd, D3DPRESENT_PARAMETERS d3dpp);	// �f�o�C�X����

	// �����o�ϐ�
	CRenderTexture*		m_pRenderScene;		// �V�[�������_�[�e�N�X�`��
	CScreen*			m_pDrawScreen;		// �X�N���[���`��|���S��
	LPDIRECT3DSURFACE9	m_pDefSurScreen;	// ���̕`��T�[�t�F�C�X�ۑ��p
	LPDIRECT3D9			m_pD3D;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	m_pD3DDevice;		// Direct3D�f�o�C�X
};

#endif	// _RENDERER_H_
