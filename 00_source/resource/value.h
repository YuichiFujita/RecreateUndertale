//============================================================
//
//	�����w�b�_�[ [value.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _VALUE_H_
#define _VALUE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �����N���X
class CValue : public CAnim2D
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NORMAL = 0,	// �ʏ�e�N�X�`��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CValue();

	// �f�X�g���N�^
	~CValue() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CValue *Create	// ����
	( // ����
		const EType type = TYPE_NORMAL,			// �������
		const D3DXVECTOR3& rPos = VEC3_ZERO,	// �ʒu
		const D3DXVECTOR3& rSize = VEC3_ONE,	// �傫��
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// ���C���֐�
	void SetType(const EType type);	// ��ސݒ�
	void SetNumber(const int nNum);	// �l�ݒ�

private:
	// �����o�ϐ�
	int m_nNum;	// �\�����l
};

#endif	// _VALUE_H_
