//============================================================
//
//	�I�u�W�F�N�g���� [object.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "manager.h"
#include "loading.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CObject* CObject::m_apTop[DIM_MAX][MAX_PRIO] = {};	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CObject* CObject::m_apCur[DIM_MAX][MAX_PRIO] = {};	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
DWORD CObject::m_dwNextIdx = 0;	// ���̃��j�[�N�C���f�b�N�X
int CObject::m_nNumAll = 0;		// �I�u�W�F�N�g�̑���

//************************************************************
//	�e�N���X [CObject] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObject::CObject(const ELabel label, const EDim dimension, const int nPriority)
{
	if (m_apCur[dimension][nPriority] != nullptr)
	{ // �Ō�������݂���ꍇ

		// ���݂̍Ō���I�u�W�F�N�g�̎��I�u�W�F�N�g�����g�ɐݒ�
		m_apCur[dimension][nPriority]->m_pNext = this;

		// �O�I�u�W�F�N�g��ݒ�
		m_pPrev = m_apCur[dimension][nPriority];	// ���݂̍Ō���I�u�W�F�N�g

		// ���I�u�W�F�N�g���N���A
		m_pNext = nullptr;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[dimension][nPriority] = this;
	}
	else
	{ // �Ō�������݂��Ȃ��ꍇ

		// ���g�̏��A�h���X��擪�ɐݒ�
		m_apTop[dimension][nPriority] = this;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[dimension][nPriority] = this;

		// �O�I�u�W�F�N�g�̃N���A
		m_pPrev = nullptr;

		// ���I�u�W�F�N�g�̃N���A
		m_pNext = nullptr;
	}

	// ���g�̏���ݒ�
	m_label		= label;		// �I�u�W�F�N�g���x��
	m_dimension	= dimension;	// ����
	m_nPriority	= nPriority;	// �D�揇��
	m_dwIdx		= m_dwNextIdx;	// ���j�[�N�C���f�b�N�X
	m_bUpdate	= true;			// �X�V��
	m_bDraw		= true;			// �`���
	m_bDeath	= false;		// ���S�t���O

#ifdef _DEBUG
	// ���g�̕\����ON�ɂ���
	m_bDebugDisp = true;
#endif	// _DEBUG

	// ���̃��j�[�N�C���f�b�N�X��ݒ�
	m_dwNextIdx++;

	// �I�u�W�F�N�g�̑��������Z
	m_nNumAll++;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObject::~CObject()
{
	// �I�u�W�F�N�g�̑��������Z
	m_nNumAll--;
}

//============================================================
//	�j������
//============================================================
void CObject::Release()
{
	if (this != nullptr)
	{ // �g�p����Ă���ꍇ

		if (!m_bDeath)
		{ // ���S�t���O�������Ă��Ȃ��ꍇ

			// ���S�t���O�𗧂Ă�
			m_bDeath = true;
		}
		else { assert(false); }	// ���S�ς�
	}
}

//============================================================
//	���x���̐ݒ菈��
//============================================================
void CObject::SetLabel(const ELabel label)
{
	if (label > NONE_IDX && label < LABEL_MAX)
	{ // �����̃��x�����g�p�\�ȏꍇ

		// �����̃��x����ݒ�
		m_label = label;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObject::SetDimension(const EDim dimension)
{
	//--------------------------------------------------------
	//	���X�g�̍Đڑ�
	//--------------------------------------------------------
	// �O�̃I�u�W�F�N�g���Ȃ��Ȃ���
	if (m_pNext != nullptr)
	{ // ���̃I�u�W�F�N�g�����݂���ꍇ

		// �O�̃I�u�W�F�N�g��ύX
		m_pNext->m_pPrev = m_pPrev;
	}

	// ���̃I�u�W�F�N�g���Ȃ��Ȃ���
	if (m_pPrev != nullptr)
	{ // �O�̃I�u�W�F�N�g�����݂���ꍇ

		// ���̃I�u�W�F�N�g��ύX
		m_pPrev->m_pNext = m_pNext;
	}

	// �擪�I�u�W�F�N�g�̕ύX
	if (m_apTop[m_dimension][m_nPriority] == this)
	{ // �擪�I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

		// ���̃I�u�W�F�N�g��擪�Ɏw��
		m_apTop[m_dimension][m_nPriority] = m_pNext;
	}

	// �Ō���I�u�W�F�N�g�̕ύX
	if (m_apCur[m_dimension][m_nPriority] == this)
	{ // �Ō���I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

		// �O�̃I�u�W�F�N�g���Ō���Ɏw��
		m_apCur[m_dimension][m_nPriority] = m_pPrev;
	}

	//--------------------------------------------------------
	//	�����̐ݒ�E���X�g�ւ̒ǉ�
	//--------------------------------------------------------
	// �����̎�����ݒ�
	m_dimension = dimension;

	// ���g�̃I�u�W�F�N�g�������̗D�揇�ʃ��X�g�ɕύX
	if (m_apCur[dimension][m_nPriority] != nullptr)
	{ // �Ō�������݂���ꍇ

		// ���݂̍Ō���I�u�W�F�N�g�̎��I�u�W�F�N�g�����g�ɐݒ�
		m_apCur[dimension][m_nPriority]->m_pNext = this;

		// �O�I�u�W�F�N�g��ݒ�
		m_pPrev = m_apCur[dimension][m_nPriority];	// ���݂̍Ō���I�u�W�F�N�g

		// ���I�u�W�F�N�g���N���A
		m_pNext = nullptr;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[dimension][m_nPriority] = this;
	}
	else
	{ // �Ō�������݂��Ȃ��ꍇ

		// ���g�̏��A�h���X��擪�ɐݒ�
		m_apTop[dimension][m_nPriority] = this;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[dimension][m_nPriority] = this;

		// �O�I�u�W�F�N�g�̃N���A
		m_pPrev = nullptr;

		// ���I�u�W�F�N�g�̃N���A
		m_pNext = nullptr;
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CObject::SetPriority(const int nPriority)
{
	//--------------------------------------------------------
	//	���X�g�̍Đڑ�
	//--------------------------------------------------------
	// �O�̃I�u�W�F�N�g���Ȃ��Ȃ���
	if (m_pNext != nullptr)
	{ // ���̃I�u�W�F�N�g�����݂���ꍇ

		// �O�̃I�u�W�F�N�g��ύX
		m_pNext->m_pPrev = m_pPrev;
	}

	// ���̃I�u�W�F�N�g���Ȃ��Ȃ���
	if (m_pPrev != nullptr)
	{ // �O�̃I�u�W�F�N�g�����݂���ꍇ

		// ���̃I�u�W�F�N�g��ύX
		m_pPrev->m_pNext = m_pNext;
	}

	// �擪�I�u�W�F�N�g�̕ύX
	if (m_apTop[m_dimension][m_nPriority] == this)
	{ // �擪�I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

		// ���̃I�u�W�F�N�g��擪�Ɏw��
		m_apTop[m_dimension][m_nPriority] = m_pNext;
	}

	// �Ō���I�u�W�F�N�g�̕ύX
	if (m_apCur[m_dimension][m_nPriority] == this)
	{ // �Ō���I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

		// �O�̃I�u�W�F�N�g���Ō���Ɏw��
		m_apCur[m_dimension][m_nPriority] = m_pPrev;
	}

	//--------------------------------------------------------
	//	�D�揇�ʂ̐ݒ�E���X�g�ւ̒ǉ�
	//--------------------------------------------------------
	// �����̗D�揇�ʂ�ݒ�
	m_nPriority = nPriority;

	// ���g�̃I�u�W�F�N�g�������̗D�揇�ʃ��X�g�ɕύX
	if (m_apCur[m_dimension][nPriority] != nullptr)
	{ // �Ō�������݂���ꍇ

		// ���݂̍Ō���I�u�W�F�N�g�̎��I�u�W�F�N�g�����g�ɐݒ�
		m_apCur[m_dimension][nPriority]->m_pNext = this;

		// �O�I�u�W�F�N�g��ݒ�
		m_pPrev = m_apCur[m_dimension][nPriority];	// ���݂̍Ō���I�u�W�F�N�g

		// ���I�u�W�F�N�g���N���A
		m_pNext = nullptr;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[m_dimension][nPriority] = this;
	}
	else
	{ // �Ō�������݂��Ȃ��ꍇ

		// ���g�̏��A�h���X��擪�ɐݒ�
		m_apTop[m_dimension][nPriority] = this;

		// ���g�̏��A�h���X���Ō���ɐݒ�
		m_apCur[m_dimension][nPriority] = this;

		// �O�I�u�W�F�N�g�̃N���A
		m_pPrev = nullptr;

		// ���I�u�W�F�N�g�̃N���A
		m_pNext = nullptr;
	}
}

//============================================================
//	�S�j������ (�������x���w��)
//============================================================
void CObject::ReleaseAll(const std::vector<ELabel> label)
{
	// ���x���w�肪�Ȃ��ꍇ������
	if (label.size() <= 0) { return; }

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;
				if (pObject->m_label == LABEL_NONE)
				{ // �����j�����Ȃ����x���̏ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (pObject->m_bDeath)
				{ // ���S���Ă���ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				for (ELabel release : label)
				{ // �v�f�����J��Ԃ�

					if (pObject->m_label == release)
					{ // �j�����郉�x���ƈ�v�����ꍇ

						// �I�u�W�F�N�g�̏I��
						pObject->Uninit();
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}
}

//============================================================
//	�S�j������ (���x���w��)
//============================================================
void CObject::ReleaseAll(const ELabel label)
{
	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;
				if (pObject->m_label == LABEL_NONE)
				{ // �����j�����Ȃ����x���̏ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (pObject->m_bDeath)
				{ // ���S���Ă���ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (pObject->m_label == label)
				{ // �j�����郉�x���ƈ�v�����ꍇ

					// �I�u�W�F�N�g�̏I��
					pObject->Uninit();
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}
}

//============================================================
//	�S�j������
//============================================================
void CObject::ReleaseAll()
{
	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;
				if (pObject->m_label == LABEL_NONE)
				{ // �����j�����Ȃ����x���̏ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (pObject->m_bDeath)
				{ // ���S���Ă���ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				// �I�u�W�F�N�g�̏I��
				pObject->Uninit();

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}

	// �S���S����
	DeathAll();
}

//============================================================
//	�S�X�V����
//============================================================
void CObject::UpdateAll(const float fDeltaTime)
{
	// �I�u�W�F�N�g���\��
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�I�u�W�F�N�g��]�F%d\n", m_nNumAll);

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;
				if (pObject->m_label == LABEL_NONE)
				{ // �����X�V���Ȃ����x���̏ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (!pObject->m_bUpdate
				||   pObject->m_bDeath)
				{ // �����X�V��OFF�A�܂��͎��S���Ă���ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				// �I�u�W�F�N�g�̍X�V
				pObject->Update(fDeltaTime);

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}

	// �S���S����
	DeathAll();
}

//============================================================
//	�S�`�揈��
//============================================================
void CObject::DrawAll()
{
	CLoading* pLoading = GET_MANAGER->GetLoading();	// ���[�f�B���O

	// ���[�h���̏ꍇ������
	assert(pLoading != nullptr);
	if (pLoading->GetState() != CLoading::LOAD_NONE) { return; }

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;

#ifdef _DEBUG
				if (!pObject->m_bDebugDisp)
				{ // �\�����Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}
#endif	// _DEBUG

				if (!pObject->m_bDraw
				||   pObject->m_bDeath)
				{ // �����`�悪OFF�A�܂��͎��S���Ă���ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				// �I�u�W�F�N�g�̕`��
				pObject->Draw();

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}
}

//============================================================
//	�S���S����
//============================================================
void CObject::DeathAll()
{
	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;
				if (!pObject->m_bDeath)
				{ // ���S�t���O�������Ă��Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObject = pObjectNext;
					continue;
				}

				if (pObject != nullptr)
				{ // �g�p����Ă���ꍇ

					// �O�̃I�u�W�F�N�g���Ȃ��Ȃ���
					if (pObject->m_pNext != nullptr)
					{ // ���̃I�u�W�F�N�g�����݂���ꍇ

						// �O�̃I�u�W�F�N�g��ύX
						pObject->m_pNext->m_pPrev = pObject->m_pPrev;
					}

					// ���̃I�u�W�F�N�g���Ȃ��Ȃ���
					if (pObject->m_pPrev != nullptr)
					{ // �O�̃I�u�W�F�N�g�����݂���ꍇ

						// ���̃I�u�W�F�N�g��ύX
						pObject->m_pPrev->m_pNext = pObject->m_pNext;
					}

					// �擪�I�u�W�F�N�g�̕ύX
					if (m_apTop[nCntDim][pObject->m_nPriority] == pObject)
					{ // �擪�I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

						// ���̃I�u�W�F�N�g��擪�Ɏw��
						m_apTop[nCntDim][pObject->m_nPriority] = pObject->m_pNext;
					}

					// �Ō���I�u�W�F�N�g�̕ύX
					if (m_apCur[nCntDim][pObject->m_nPriority] == pObject)
					{ // �Ō���I�u�W�F�N�g���j������I�u�W�F�N�g�������ꍇ

						// �O�̃I�u�W�F�N�g���Ō���Ɏw��
						m_apCur[nCntDim][pObject->m_nPriority] = pObject->m_pPrev;
					}

					// �������J��
					delete pObject;
					pObject = nullptr;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}
}

//============================================================
//	�S�\���󋵂̐ݒ菈��
//============================================================
#ifdef _DEBUG
void CObject::SetEnableDebugDispAll(const bool bDisp2D, const bool bDisp3D)
{
	bool aDisp[DIM_MAX] = { bDisp3D, bDisp2D };	// �e�����̕\����
	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{ // �����̑������J��Ԃ�

		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

			// �I�u�W�F�N�g�̐擪����
			CObject* pObject = m_apTop[nCntDim][nCntPri];
			while (pObject != nullptr)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// ���̃I�u�W�F�N�g����
				CObject* pObjectNext = pObject->m_pNext;

				// �����̕\���t���O��ݒ�
				pObject->m_bDebugDisp = aDisp[nCntDim];

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObject = pObjectNext;
			}
		}
	}
}
#endif	// _DEBUG
