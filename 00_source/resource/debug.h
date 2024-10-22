//============================================================
//
//	�f�o�b�O�w�b�_�[ [debug.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _DEBUG_H_
#define _DEBUG_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "camera.h"

//************************************************************
//	�N���X��`
//************************************************************
// �f�o�b�O�N���X
class CDebug
{
public:
	// �R���X�g���N�^
	CDebug();

	// �f�X�g���N�^
	~CDebug();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void MeasureFps(const DWORD dwCurrentTime);	// FPS����
	void AddFrameCount();		// �t���[���J�E���g���Z
	int  GetFps() const;		// FPS�擾
	void SetFillMode();			// �h��Ԃ����[�h�ݒ�
	void UpdateDebugControl();	// �f�o�b�O����X�V
	void DrawDebugControl();	// �f�o�b�O����\��
	void DrawDebugData();		// �f�o�b�O���\��

	// �ÓI�����o�֐�
	static CDebug* Create();				// ����
	static void Release(CDebug*& prDebug);	// �j��

private:

#ifdef _DEBUG

	// �����o�֐�
	void ChangeDispDebug();		// �f�o�b�O�\���ύX
	void ChangeControlCamera();	// �J��������ύX
	void ChangeFillMode();		// �h��Ԃ����[�h�ύX
	void ChangeDisp2D();		// 2D�I�u�W�F�N�g�\���ύX
	void ChangeEditMode();		// �G�f�B�^�[���[�h�ύX
	void ChangeDispPause();		// �|�[�Y�\���ύX

	// �����o�ϐ�
	int  m_nFps;	// FPS�J�E���^
	bool m_bDisp2D;	// 2D�\����
	bool m_bDisp3D;	// 3D�\����
	DWORD m_dwFrameCount;	// �t���[���J�E���g
	DWORD m_dwFPSLastTime;	// �Ō��FPS���v����������
	D3DFILLMODE m_fillMode;	// �h��Ԃ����[�h
	CCamera::EState m_oldCameraState;	// �J�����̉ߋ����

#endif	// _DEBUG

};

#endif	// _DEBUG_H_
