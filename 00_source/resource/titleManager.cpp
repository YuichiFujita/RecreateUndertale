//============================================================
//
//	�^�C�g���}�l�[�W���[���� [titleManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleManager.h"
#include "manager.h"

// TODO�F�f�o�b�O
#include "objectMeshField.h"
#include "objectMeshWall.h"
#include "object3D.h"
#include "objectBillboard.h"
#include "objectMeshCircle.h"
#include "objectMeshCube.h"
#include "objectMeshCylinder.h"
#include "objectMeshDome.h"
#include "objectMeshRing.h"
#include "objectMeshTube.h"
#include "objectModel.h"
#include "objectTornado.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�e�N���X [CTitleManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTitleManager::CTitleManager()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTitleManager::~CTitleManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTitleManager::Init()
{
	// �n��
	CObjectMeshField* pField = CObjectMeshField::Create(VEC3_ZERO, VEC3_ZERO, VECTOR2(5000.0f, 500.0f), color::Yellow(), POSGRID2(10, 10));
	pField->SetLabel(CObject::LABEL_DEBUG);

	// ��
	CObjectMeshWall* pWall = CObjectMeshWall::Create(VECTOR3(0.0f, 0.0f, 250.0f), VEC3_ZERO, VECTOR2(5000.0f, 500.0f), color::Cyan(), POSGRID2(10, 10));
	pWall->SetLabel(CObject::LABEL_DEBUG);

	// 3D
	CObject3D* p3D = CObject3D::Create(VECTOR3(0.0f, 50.0f, 0.0f), VECTOR3(50.0f, 50.0f, 0.0f));
	p3D->SetLabel(CObject::LABEL_DEBUG);

	// �r���{�[�h
	CObjectBillboard* pBill = CObjectBillboard::Create(VECTOR3(150.0f, 50.0f, 0.0f), VECTOR3(50.0f, 50.0f, 0.0f));
	pBill->SetLabel(CObject::LABEL_DEBUG);
	//pBill->SetRotate(CObjectBillboard::ROTATE_LATERAL);

	// �T�[�N��
	CObjectMeshCircle* pCircle = CObjectMeshCircle::Create(VECTOR3(-150.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10, 10), 50.0f);
	pCircle->SetLabel(CObject::LABEL_DEBUG);

	// �L���[�u
	CObjectMeshCube* pCube = CObjectMeshCube::Create(VECTOR3(300.0f, 50.0f, 0.0f), VEC3_ZERO, VECTOR3(50.0f), color::White());
	pCube->SetLabel(CObject::LABEL_DEBUG);

	// �V�����_�[
	CObjectMeshCylinder* pCylinder = CObjectMeshCylinder::Create(VECTOR3(-300.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f, 50.0f);
	pCylinder->SetLabel(CObject::LABEL_DEBUG);

	// �h�[��
	CObjectMeshDome* pDome = CObjectMeshDome::Create(VECTOR3(450.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f);
	pDome->SetLabel(CObject::LABEL_DEBUG);

	// �����O
	CObjectMeshRing* pRing = CObjectMeshRing::Create(VECTOR3(-450.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f, 50.0f, 50.0f);
	pRing->SetLabel(CObject::LABEL_DEBUG);

	// �`���[�u
	CObjectMeshTube* pTube = CObjectMeshTube::Create(VECTOR3(600.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10),50.0f, 50.0f);
	pTube->SetLabel(CObject::LABEL_DEBUG);

	// ���f��
	CObjectModel* pModel = CObjectModel::Create(VECTOR3(-600.0f, 50.0f, 0.0f), VEC3_ZERO);
	pModel->SetLabel(CObject::LABEL_DEBUG);
	pModel->BindModel("data\\MODEL\\02_head.x");

	// �g���l�[�h
	CObjectTornado* pTornado = CObjectTornado::Create(VECTOR3(750.0f, 50.0f, 0.0f), VEC3_ZERO, color::White());
	pTornado->SetLabel(CObject::LABEL_DEBUG);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTitleManager::Uninit()
{

}

//============================================================
//	�X�V����
//============================================================
void CTitleManager::Update(const float fDeltaTime)
{
	CInputKeyboard*	pKeyboard	= GET_INPUTKEY;	// �L�[�{�[�h
	CInputPad*		pPad		= GET_INPUTPAD;	// �p�b�h
	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pKeyboard->IsTrigger(DIK_SPACE)
	||  pPad->IsTrigger(CInputPad::KEY_A)
	||  pPad->IsTrigger(CInputPad::KEY_B)
	||  pPad->IsTrigger(CInputPad::KEY_X)
	||  pPad->IsTrigger(CInputPad::KEY_Y)
	||  pPad->IsTrigger(CInputPad::KEY_START))
	{
		// �C���g����ʂɑJ�ڂ���
		GET_MANAGER->SetFadeScene(CScene::MODE_INTRO);
	}
}

//============================================================
//	��������
//============================================================
CTitleManager* CTitleManager::Create()
{
	// �^�C�g���}�l�[�W���[�̐���
	CTitleManager* pTitleManager = new CTitleManager;
	if (pTitleManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �^�C�g���}�l�[�W���[�̏�����
		if (FAILED(pTitleManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �^�C�g���}�l�[�W���[�̔j��
			SAFE_DELETE(pTitleManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTitleManager;
	}
}

//============================================================
//	�j������
//============================================================
void CTitleManager::Release(CTitleManager*& prTitleManager)
{
	// �^�C�g���}�l�[�W���[�̏I��
	assert(prTitleManager != nullptr);
	prTitleManager->Uninit();

	// �������J��
	SAFE_DELETE(prTitleManager);
}
