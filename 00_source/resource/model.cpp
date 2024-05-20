//============================================================
//
//	���f������ [model.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *LOAD_FOLDER = "data\\MODEL";	// ���f���t�H���_���΃p�X

	const D3DXVECTOR3 INIT_VTXMIN = D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f);	// ���f���̍ŏ��̒��_���W�̏����l
	const D3DXVECTOR3 INIT_VTXMAX = D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f);	// ���f���̍ő�̒��_���W�̏����l
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
int CModel::m_nNumAll = 0;	// ���f���̑���

//************************************************************
//	�e�N���X [CModel] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CModel::CModel()
{
	// ���f���A�z�z����N���A
	m_mapModel.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CModel::~CModel()
{

}

//============================================================
//	���f������������
//============================================================
HRESULT CModel::Init(void)
{
	// ���f���A�z�z���������
	m_mapModel.clear();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���f���I������
//============================================================
void CModel::Uninit(void)
{
	for (auto& rMap : m_mapModel)
	{ // ���f���̗v�f�����J��Ԃ�

		// �e�N�X�`���C���f�b�N�X�̔j��
		SAFE_FREE(rMap.second.modelData.pTextureID);

		// ���b�V���̔j��
		SAFE_RELEASE(rMap.second.modelData.pMesh);

		// �}�e���A���̔j��
		SAFE_RELEASE(rMap.second.modelData.pBuffMat);
	}

	// ���f���A�z�z����N���A
	m_mapModel.clear();
}

//============================================================
//	���f���S�Ǎ�����
//============================================================
HRESULT CModel::LoadAll(void)
{
	// ���f���̑S�Ǎ�
	if (FAILED(SearchFolderAll(LOAD_FOLDER)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���f���o�^����
//============================================================
int CModel::Regist(std::string sFilePass)
{
	// �ϐ���錾
	SMapInfo tempMapInfo;	// �}�b�v���
	int nID = m_nNumAll;	// ���f���Ǎ��ԍ�

	// �t�@�C���p�X��W����
	useful::StandardizePathPart(&sFilePass);

	// ���ɓǂݍ���ł��Ȃ������m�F
	int nCntModel = 0;
	for (const auto& rMap : m_mapModel)
	{ // ���f���̗v�f�����J��Ԃ�

		if (rMap.second.sFilePassName.compare(sFilePass) == 0)
		{ // �����񂪈�v�����ꍇ

			// ���łɓǂݍ���ł��郂�f���̔z��ԍ���Ԃ�
			return nCntModel;
		}

		// ���̃��f���ԍ��ɂ���
		nCntModel++;
	}

	// x�t�@�C���̓Ǎ�
	if (FAILED(LoadXFileModel(&tempMapInfo, sFilePass)))
		{ // x�t�@�C���̓Ǎ��Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return NONE_IDX;
		}

	// �e�N�X�`���̓Ǎ�
	if (FAILED(LoadTextureModel(&tempMapInfo)))
		{ // �e�N�X�`���̓Ǎ��Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return NONE_IDX;
		}

	// �����蔻��̍쐬
	if (FAILED(SetCollisionModel(&tempMapInfo)))
		{ // �����蔻��̍쐬�Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return NONE_IDX;
		}

	// �t�@�C���p�X����ۑ�
	tempMapInfo.sFilePassName = sFilePass;

	// ���f�����𐶐�
	m_mapModel.insert(std::make_pair(m_nNumAll, tempMapInfo));

	// ���f���̑��������Z
	m_nNumAll++;

	// �ǂݍ��񂾃��f���̔z��ԍ���Ԃ�
	return nID;
}

//============================================================
//	���f�����擾����
//============================================================
CModel::SModel *CModel::GetInfo(const int nID)
{
	if (nID > NONE_IDX && nID < (int)m_mapModel.size())
	{ // ���f��������ꍇ

		// �����̃��f������Ԃ�
		return &m_mapModel.find(nID)->second.modelData;
	}
	else
	{ // ���f�����Ȃ��ꍇ

		// nullptr��Ԃ�
		assert(false);
		return nullptr;
	}
}

//============================================================
//	��������
//============================================================
CModel *CModel::Create(void)
{
	// ���f���̐���
	CModel *pModel = new CModel;
	if (pModel == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���f���̏�����
		if (FAILED(pModel->Init()))
		{ // ���f���������Ɏ��s�����ꍇ

			// ���f���̔j��
			SAFE_DELETE(pModel);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pModel;
	}
}

//============================================================
//	�j������
//============================================================
void CModel::Release(CModel *&prModel)
{
	// ���f���̏I��
	assert(prModel != nullptr);
	prModel->Uninit();

	// �������J��
	SAFE_DELETE(prModel);
}

//============================================================
//	x�t�@�C���̓ǂݍ���
//============================================================
HRESULT CModel::LoadXFileModel(SMapInfo *pMapInfo, std::string sFilePass)
{
	// �}�b�v���̎w�肪�Ȃ��ꍇ�G���[
	if (pMapInfo == nullptr) { return E_FAIL; }

	// x�t�@�C���̓Ǎ�
	HRESULT hr;
	hr = D3DXLoadMeshFromX
	( // ����
		sFilePass.c_str(),				// ���f���̑��΃p�X
		D3DXMESH_SYSTEMMEM,				// ���b�V���쐬�p�I�v�V����
		GET_DEVICE,						// �f�o�C�X�ւ̃|�C���^
		nullptr,						// �אڐ��f�[�^
		&pMapInfo->modelData.pBuffMat,	// �}�e���A���ւ̃|�C���^
		nullptr,						// �G�t�F�N�g�f�[�^
		&pMapInfo->modelData.dwNumMat,	// �}�e���A���̐�
		&pMapInfo->modelData.pMesh		// ���b�V�� (���_���) �ւ̃|�C���^
	);
	if (FAILED(hr))
	{ // x�t�@�C���̓Ǎ��Ɏ��s�����ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "x�t�@�C���̓Ǎ��Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �}�e���A�������������m��
	pMapInfo->modelData.pTextureID = (int*)malloc(pMapInfo->modelData.dwNumMat * sizeof(int*));
	if (pMapInfo->modelData.pTextureID == nullptr)
	{ // ���I�m�ۂɎ��s�����ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�������̊m�ۂɎ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�e�N�X�`���̓ǂݍ���
//============================================================
HRESULT CModel::LoadTextureModel(SMapInfo *pMapInfo)
{
	// �}�b�v���̎w�肪�Ȃ��ꍇ�G���[
	if (pMapInfo == nullptr) { return E_FAIL; }

	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapInfo->modelData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMapInfo->modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		if (pMat[nCntMat].pTextureFilename != nullptr)
		{ // �e�N�X�`���t�@�C�������݂���ꍇ

			// �e�N�X�`����o�^
			pMapInfo->modelData.pTextureID[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{ // �e�N�X�`���t�@�C�������݂��Ȃ��ꍇ

			// �e�N�X�`����o�^
			pMapInfo->modelData.pTextureID[nCntMat] = NONE_IDX;	// �e�N�X�`���Ȃ�
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�����蔻��̍쐬
//============================================================
HRESULT CModel::SetCollisionModel(SMapInfo *pMapInfo)
{
	// �}�b�v���̎w�肪�Ȃ��ꍇ�G���[
	if (pMapInfo == nullptr) { return E_FAIL; }

	// �ϐ���錾
	int			nNumVtx;	// ���f���̒��_��
	DWORD		dwSizeFVF;	// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y
	BYTE		*pVtxBuff;	// ���f���̒��_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	vtx;		// ���f���̒��_���W

	// ���f���̒��_�����擾
	nNumVtx = pMapInfo->modelData.pMesh->GetNumVertices();

	// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(pMapInfo->modelData.pMesh->GetFVF());

	// ���f���̒��_�o�b�t�@�����b�N
	pMapInfo->modelData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{ // ���f���̒��_�����J��Ԃ�

		// ���f���̒��_���W����
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		// x���_���W�̐ݒ�
		if (vtx.x < pMapInfo->modelData.vtxMin.x)
		{ // ����� x���_���W�����������ꍇ

			// x���_������
			pMapInfo->modelData.vtxMin.x = vtx.x;
		}
		else if (vtx.x > pMapInfo->modelData.vtxMax.x)
		{ // ����� x���_���W�����傫���ꍇ

			// x���_������
			pMapInfo->modelData.vtxMax.x = vtx.x;
		}

		// y���_���W�̐ݒ�
		if (vtx.y < pMapInfo->modelData.vtxMin.y)
		{ // ����� y���_���W�����������ꍇ

			// y���_������
			pMapInfo->modelData.vtxMin.y = vtx.y;
		}
		else if (vtx.y > pMapInfo->modelData.vtxMax.y)
		{ // ����� y���_���W�����傫���ꍇ

			// y���_������
			pMapInfo->modelData.vtxMax.y = vtx.y;
		}

		// z���_���W�̐ݒ�
		if (vtx.z < pMapInfo->modelData.vtxMin.z)
		{ // ����� z���_���W�����������ꍇ

			// z���_������
			pMapInfo->modelData.vtxMin.z = vtx.z;
		}
		else if (vtx.z > pMapInfo->modelData.vtxMax.z)
		{ // ����� z���_���W�����傫���ꍇ

			// z���_������
			pMapInfo->modelData.vtxMax.z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += dwSizeFVF;
	}

	// ���f���̒��_�o�b�t�@���A�����b�N
	pMapInfo->modelData.pMesh->UnlockVertexBuffer();

	// ���f���T�C�Y�����߂�
	pMapInfo->modelData.size = pMapInfo->modelData.vtxMax - pMapInfo->modelData.vtxMin;

	// ���f���̉~�̓����蔻����쐬
	pMapInfo->modelData.fRadius = ((pMapInfo->modelData.size.x * 0.5f) + (pMapInfo->modelData.size.z * 0.5f)) * 0.5f;

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�t�H���_�S��������
//============================================================
HRESULT CModel::SearchFolderAll(std::string sFolderPath)
{
	// �ϐ���錾
	HANDLE hFile;	// �����n���h��
	WIN32_FIND_DATA findFileData;	// �t�@�C�����

	// �����p�X�̃f�B���N�g�����擾
	std::string sAllLoadPath = sFolderPath + "\\*.*";	// �S�Ǎ��p�X
	hFile = FindFirstFile(sAllLoadPath.c_str(), &findFileData);
	if (INVALID_HANDLE_VALUE == hFile)
	{ // �n���h���������̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	do
	{ // �t�@�C�����̏��S�Ă�ǂݍ���

		// ���݂̃f�B���N�g���A�e�f�B���N�g���̏ꍇ���̃��[�v�Ɉڍs
		if (strcmp(findFileData.cFileName, ".") == 0)	{ continue; }
		if (strcmp(findFileData.cFileName, "..") == 0)	{ continue; }

		// �t�@�C�����𑊑΃p�X�ɕϊ�
		std::string sFullPath = sFolderPath;	// ���݂̑��΃p�X��ݒ�
		sFullPath += "\\";						// �p�X��؂蕶����ǉ�
		sFullPath += findFileData.cFileName;	// �t�@�C������ǉ�

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{ // �f�B���N�g���������ꍇ

			// �V���ȃf�B���N�g����S����
			SearchFolderAll(sFullPath);
		}
		else
		{ // �t�@�C���������ꍇ

			// ���f����o�^
			Regist(sFullPath.c_str());
		}

	} while (FindNextFile(hFile, &findFileData));	// ���̃t�@�C��������

	// �����n���h�������
	FindClose(hFile);

	// ������Ԃ�
	return S_OK;
}
