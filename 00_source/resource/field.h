//============================================================
//
//	�n�ʃw�b�_�[ [field.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FIELD_H_
#define _FIELD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshField.h"

//************************************************************
//	�N���X��`
//************************************************************
// �n�ʃN���X
class CField : public CObjectMeshField
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_ASH = 0,	// �ΎR�D�e�N�X�`��
		TEXTURE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CField();

	// �f�X�g���N�^
	~CField() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CField *Create	// ����
	( // ����
		const ETexture texture,		// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR2& rSize,	// �傫��
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart		// ������
	);
};

#endif	// _FIELD_H_
