//============================================================
//
//	�����_���w�b�_�[ [random.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RANDOM_H_
#define _RANDOM_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include <random>
#include <algorithm>

//************************************************************
//	�N���X��`
//************************************************************
// �����_���N���X
template<class T> class CRandom
{
public:
	// �R���X�g���N�^
	CRandom();

	// �f�X�g���N�^
	~CRandom();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void AddList(T num, int nAdd = 1);	// �z��ǉ�
	void AllDeleteList();		// �z��S�폜
	T GetRandomNum();			// �����_�����l�擾
	int GetNumAll();			// �z����̗v�f���擾
	std::vector<T> GetList();	// �z��擾

	// �ÓI�����o�֐�
	static CRandom* Create();	// ����
	static void Release(CRandom*& prRandom);	// �j��

private:
	// �C�e���[�^�[�^�G�C���A�X��`
	using AIterator = std::_List_iterator<std::_List_val<std::_List_simple_types<T>>>;

	// �����o�ϐ�
	std::vector<T> m_vector;	// �I�u�W�F�N�g�z��
};

//************************************************************
//	�e�N���X [CRandom] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
template<class T> CRandom<T>::CRandom()
{
	// �I�u�W�F�N�g�z��̑S�v�f���폜
	m_vector.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
template<class T> CRandom<T>::~CRandom()
{

}

//============================================================
//	����������
//============================================================
template<class T> HRESULT CRandom<T>::Init()
{
	// �I�u�W�F�N�g�z��̑S�v�f���폜
	m_vector.clear();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
template<class T> void CRandom<T>::Uninit()
{
	// �I�u�W�F�N�g�z��̑S�v�f���폜
	m_vector.clear();
}

//============================================================
//	�z��ǉ�����
//============================================================
template<class T> void CRandom<T>::AddList(T num, int nAdd)
{
	// ���Z�������R���ł͂Ȃ��ꍇ������
	if (nAdd <= 0) { return; }
	for (int nCntAdd = 0; nCntAdd < nAdd; nCntAdd++)
	{ // �ǉ������J��Ԃ�

		// �z��̍Ō���ɃI�u�W�F�N�g��ǉ�
		m_vector.push_back(num);
	}
}

//============================================================
//	�z��S�폜����
//============================================================
template<class T> void CRandom<T>::AllDeleteList()
{
	// �I�u�W�F�N�g�z��̑S�v�f���폜
	m_vector.clear();
}

//============================================================
//	�����_�����l�擾����
//============================================================
template<class T> T CRandom<T>::GetRandomNum()
{
	int nNumArray = (int)(m_vector.size());	// �z��̗v�f��
	if (nNumArray > 0)
	{ // �v�f���ݒ肳��Ă���ꍇ

		// ������������쐬
		std::random_device rd;
		std::mt19937 gen(rd());

		// �v�f���V���b�t������
		std::shuffle(m_vector.begin(), m_vector.end(), gen);

		// �g�p����v�f�ԍ������߂�
		int nRandHit = rand() % nNumArray;

		// �����_���Œ��I���ꂽ�l��Ԃ�
		auto numRand = m_vector.begin();	// �z��̐擪
		numRand += nRandHit;				// �v�f�ԍ����C�e���[�^�[���Z
		return *numRand;
	}

	// �����l��Ԃ�
	return {};
}

//============================================================
//	�z����̗v�f���̎擾����
//============================================================
template<class T> int CRandom<T>::GetNumAll()
{
	// �z����̗v�f����Ԃ�
	return (int)m_vector.size();
}

//============================================================
//	�z��擾����
//============================================================
template<class T> std::vector<T> CRandom<T>::GetList()
{
	// �I�u�W�F�N�g�z���Ԃ�
	return m_vector;
}

//============================================================
//	��������
//============================================================
template<class T> CRandom<T>* CRandom<T>::Create()
{
	// �����_���̐���
	CRandom* pRandom = new CRandom;
	if (pRandom == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �����_���̏�����
		if (FAILED(pRandom->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �����_���̔j��
			SAFE_DELETE(pRandom);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pRandom;
	}
}

//============================================================
//	�j������
//============================================================
template<class T> void CRandom<T>::Release(CRandom*& prRandom)
{
	// �����_���̏I��
	assert(prRandom != nullptr);
	prRandom->Uninit();

	// �������J��
	SAFE_DELETE(prRandom);
}

#endif	// _RANDOM_H_
