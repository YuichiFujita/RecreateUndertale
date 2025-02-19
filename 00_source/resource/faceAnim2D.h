//============================================================
//
//	�\��A�j���[�V����2D�w�b�_�[ [faceAnim2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FACE_ANIM2D_H_
#define _FACE_ANIM2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "extension.h"
#include "anim2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �\��A�j���[�V����2D�N���X
class CFaceAnim2D
{
public:
	// �R���X�g���N�^
	CFaceAnim2D();

	// �f�X�g���N�^
	~CFaceAnim2D();

	// �\��Ǘ��\����
	struct SEmotion
	{
		// �f�t�H���g�R���X�g���N�^
		SEmotion() :
			vecNextTime	 ({}),			// �p�^�[���ύX���Ԕz��
			sPathTexture (""),			// �e�N�X�`���p�X
			ptrnTexture	 (GRID2_ZERO),	// �e�N�X�`��������
			nMaxPtrn	 (0),			// �ő�p�^�[����
			offset		 (VEC3_ZERO),	// ���_�I�t�Z�b�g
			size		 (VEC3_ZERO),	// �L�����N�^�[�傫��
			bLoop		 (false)		// ���[�vON/OFF
		{}

		// �f�X�g���N�^
		~SEmotion() {}

		// �e�N�X�`���������E�p�^�[�������̐ݒ�
		inline HRESULT SetTexPtrn(const POSGRID2& rPtrn)
		{
			// �e�N�X�`���������E�p�^�[��������ݒ�
			ptrnTexture = rPtrn;
			nMaxPtrn = rPtrn.x * rPtrn.y;

			// �p�^�[���ύX���Ԃ̔j��
			vecNextTime.clear();

			// �p�^�[���ύX���Ԃ̐���
			vecNextTime.resize(nMaxPtrn);

			// �p�^�[���ύX���Ԃ�������
			if (FAILED(SetNextTime(CAnim2D::DEF_NEXT))) { return E_FAIL; }

			return S_OK;
		}

		// �p�^�[���ύX���Ԃ̐ݒ�
		inline HRESULT SetNextTime(const float fNextTime)
		{
			if (fNextTime <= 0.0f)					 { return E_FAIL; }	// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ���s
			if (nMaxPtrn != (int)vecNextTime.size()) { return E_FAIL; }	// �p�^�[���ő吔�Ɠ����T�C�Y�ł͂Ȃ��ꍇ���s

			for (int i = 0; i < nMaxPtrn; i++)
			{
				// �����̃p�^�[���ύX���Ԃ�ݒ�
				vecNextTime[i] = fNextTime;
			}

			return S_OK;
		}

		// �����o�ϐ�
		std::vector<float> vecNextTime;	// �p�^�[���ύX���Ԕz��
		std::string sPathTexture;		// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;			// �e�N�X�`��������
		int nMaxPtrn;	// �ő�p�^�[����
		VECTOR3 offset;	// ���_�I�t�Z�b�g
		VECTOR3 size;	// ��傫��
		bool bLoop;		// ���[�vON/OFF
	};

	// ��Ǘ��\����
	struct SFace
	{
		// �f�t�H���g�R���X�g���N�^
		SFace() :
			vecEmotion	({})	// �\����
		{}

		// �f�X�g���N�^
		~SFace() {}

		// �����o�֐�
		inline int GetNumEmotion() { return (int)vecEmotion.size(); }	// �\����̑����擾

		// �����o�ϐ�
		std::vector<SEmotion> vecEmotion;	// �\����
	};

	// �����o�֐�
	HRESULT Init();		// ������
	void Uninit();		// �I��
	HRESULT LoadAll();	// �S�Ǎ�
	SFace GetInfo(const int nIdx);	// ����擾

	// �ÓI�����o�֐�
	static CFaceAnim2D* Create();	// ����
	static void Release(CFaceAnim2D*& prFaceAnim2D);	// �j��

private:
	// �����o�֐�
	HRESULT LoadSetup();	// �Z�b�g�A�b�v
	HRESULT LoadFaceSetup(SFace* pInfoFace, const char* pFacePath);		// ����Z�b�g�A�b�v
	HRESULT LoadEmotionSetup(SFace* pInfoFace, const char* pEmoPath);	// �\����Z�b�g�A�b�v

	// �����o�ϐ�
	std::vector<SFace> m_vecFace;	// ����
};

#endif	// _FACE_ANIM2D_H_
