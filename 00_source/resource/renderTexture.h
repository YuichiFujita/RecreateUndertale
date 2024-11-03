//============================================================
//
//	�����_�[�e�N�X�`���w�b�_�[ [renderTexture.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_

//************************************************************
//	�N���X��`
//************************************************************
// �����_�[�e�N�X�`���N���X
class CRenderTexture
{
public:
	// �R���X�g���N�^
	CRenderTexture();

	// �f�X�g���N�^
	~CRenderTexture();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Draw();	// �`��
	inline int GetTextureIndex() const { return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾

	// �ÓI�����o�֐�
	static CRenderTexture *Create();	// ����
	static void Release(CRenderTexture*& prRenderTexture);	// �j��

private:
	// �����o�ϐ�
	LPDIRECT3DSURFACE9 m_pSurTexture;	// �e�N�X�`���T�[�t�F�C�X�ւ̃|�C���^
	int m_nTextureIdx;					// �����_�[�e�N�X�`���C���f�b�N�X
};

#endif	// _RENDER_TEXTURE_H_
