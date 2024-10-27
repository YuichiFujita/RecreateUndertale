//============================================================
//
//	���X�g�}�l�[�W���[�w�b�_�[ [listManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _LIST_MANAGER_H_
#define _LIST_MANAGER_H_

//************************************************************
//	�N���X��`
//************************************************************
// ���X�g�}�l�[�W���[�N���X
template<class T> class CListManager
{
public:
	// �R���X�g���N�^
	CListManager();

	// �f�X�g���N�^
	~CListManager();

	// �C�e���[�^�[�^�G�C���A�X��`
	using AIterator = std::_List_iterator<std::_List_val<std::_List_simple_types<T*>>>;

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	AIterator GetBegin();	// ���X�g�擪�擾
	AIterator GetEnd();		// ���X�g�Ō���擾
	AIterator GetIndex(const int nIdx);		// ���X�g�C���f�b�N�X�擾
	AIterator AddList(T* pObject);			// ���X�g�ǉ�
	void DelList(const AIterator iterator);	// ���X�g�폜
	int GetNumAll();			// ���X�g���̗v�f���擾
	std::list<T*> GetList();	// ���X�g�擾

	// �ÓI�����o�֐�
	static CListManager* Create();	// ����
	static void Release(CListManager*& prListManager);	// �j��

private:
	// �����o�ϐ�
	std::list<T*> m_list;	// �I�u�W�F�N�g���X�g
};

//************************************************************
//	�e�N���X [CListManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
template<class T> CListManager<T>::CListManager()
{
	// �I�u�W�F�N�g���X�g�̑S�v�f���폜
	m_list.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
template<class T> CListManager<T>::~CListManager()
{

}

//============================================================
//	����������
//============================================================
template<class T> HRESULT CListManager<T>::Init()
{
	// �I�u�W�F�N�g���X�g�̑S�v�f���폜
	m_list.clear();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
template<class T> void CListManager<T>::Uninit()
{
	// �I�u�W�F�N�g���X�g�̑S�v�f���폜
	m_list.clear();
}

//============================================================
//	���X�g�擪�擾����
//============================================================
template<class T>
std::_List_iterator<std::_List_val<std::_List_simple_types<T*>>> CListManager<T>::GetBegin()
{
	// ���X�g�擪��Ԃ�
	return m_list.begin();
}

//============================================================
//	���X�g�Ō���擾����
//============================================================
template<class T>
std::_List_iterator<std::_List_val<std::_List_simple_types<T*>>> CListManager<T>::GetEnd()
{
	// ���X�g�Ō����Ԃ�
	return m_list.end();
}

//============================================================
//	���X�g�C���f�b�N�X�擾����
//============================================================
template<class T>
std::_List_iterator<std::_List_val<std::_List_simple_types<T*>>> CListManager<T>::GetIndex(const int nIdx)
{
	AIterator itr = m_list.begin();	// ���X�g�擪

	// �C���f�b�N�X���͈͊O�̏ꍇ������
	if (nIdx <= NONE_IDX || nIdx >= (int)m_list.size()) { assert(false); return itr; }

	// �����̃C���f�b�N�X���i�߂�
	std::advance(itr, nIdx);

	// �i�߂��C�e���[�^�[��Ԃ�
	return itr;
}

//============================================================
//	���X�g�ǉ�����
//============================================================
template<class T>
std::_List_iterator<std::_List_val<std::_List_simple_types<T*>>> CListManager<T>::AddList(T* pObject)
{
	// ���X�g�̍Ō���ɃI�u�W�F�N�g��ǉ����A�C�e���[�^�[��Ԃ�
	return m_list.insert(m_list.end(), pObject);
}

//============================================================
//	���X�g�폜����
//============================================================
template<class T> void CListManager<T>::DelList(const AIterator iterator)
{
	// �����C�e���[�^�[�̗v�f�����X�g����폜
	m_list.erase(iterator);
}

//============================================================
//	���X�g���̗v�f���̎擾����
//============================================================
template<class T> int CListManager<T>::GetNumAll()
{
	// ���X�g���̗v�f����Ԃ�
	return (int)m_list.size();
}

//============================================================
//	���X�g�擾����
//============================================================
template<class T> std::list<T*> CListManager<T>::GetList()
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_list;
}

//============================================================
//	��������
//============================================================
template<class T> CListManager<T>* CListManager<T>::Create()
{
	// ���X�g�}�l�[�W���[�̐���
	CListManager* pListManager = new CListManager;
	if (pListManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���X�g�}�l�[�W���[�̏�����
		if (FAILED(pListManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���X�g�}�l�[�W���[�̔j��
			SAFE_DELETE(pListManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pListManager;
	}
}

//============================================================
//	�j������
//============================================================
template<class T> void CListManager<T>::Release(CListManager*& prListManager)
{
	// ���X�g�}�l�[�W���[�̏I��
	assert(prListManager != nullptr);
	prListManager->Uninit();

	// �������J��
	SAFE_DELETE(prListManager);
}

#endif	// _LIST_MANAGER_H_
