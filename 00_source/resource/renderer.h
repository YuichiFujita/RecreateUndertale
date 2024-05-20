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
	// �R���X�g���N�^
	CRenderer();

	// �f�X�g���N�^
	~CRenderer();

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ������
	void Uninit(void);						// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Draw(void);						// �`��

	HRESULT CreateRenderTexture(void);			// �����_�[�e�N�X�`���[����
	LPDIRECT3DDEVICE9 GetDevice(void) const;	// �f�o�C�X�擾
	D3DXCOLOR GetClearColor(void) const;		// ��ʃN���A�F�擾

	// �ÓI�����o�֐�
	static CRenderer *Create(HWND hWnd, BOOL bWindow);	// ����
	static void Release(CRenderer *&prRenderer);		// �j��

private:
	// �����o�֐�
	HRESULT CreateDevice(HWND hWnd, D3DPRESENT_PARAMETERS d3dpp);	// �f�o�C�X����

	// �����o�ϐ�
	LPDIRECT3D9			m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Direct3D�f�o�C�X

	int m_nScreenTexID;		// �X�N���[���e�N�X�`���̃C���f�b�N�X
	CScreen *m_pDrawScreen;	// �X�N���[���`��|���S��
	LPDIRECT3DSURFACE9 m_pDefSurScreen;	// ���̃X�N���[���`��T�[�t�F�C�X�ۑ��p
	LPDIRECT3DSURFACE9 m_pSurScreen;	// �X�N���[���`��T�[�t�F�C�X�ւ̃|�C���^
};

#endif	// _RENDERER_H_
