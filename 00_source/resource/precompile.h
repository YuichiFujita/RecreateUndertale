//============================================================
//
//	�v���R���p�C���w�b�_�[ [precompile.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PRECOMPILE_H_
#define _PRECOMPILE_H_

//************************************************************
//	�x�����b�Z�[�W������
//************************************************************
#pragma warning(disable : 26812)	// enumclass�x���̍폜

//************************************************************
//	�}�N����`
//************************************************************
#define _CRT_SECURE_NO_WARNINGS	// �r���h���̌x���Ώ��p�}�N��
#define _CRTDBG_MAP_ALLOC		// ���������[�N�o�͗p�}�N��
#define  DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���Ώ��p�}�N��

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <d3dx9.h>
#include <dinput.h>		// ����
#include <Xinput.h>		// �p�b�h
#include <xaudio2.h>	// �T�E���h
#include <crtdbg.h>		// ���������[�N���o�ɕK�v
#include <iostream>		// ���o�̓X�g���[��
#include <fstream>		// �t�@�C�����o�̓X�g���[��
#include <sstream>		// ��������o�̓X�g���[��
#include <iomanip>		// �����_�o��
#include <filesystem>	// �t�@�C������
#include <functional>	// �֐��|�C���^
#include <string>		// ������
#include <thread>		// �X���b�h
#include <future>		// �X���b�h�Ԃ�l�擾
#include <vector>		// ���I�z��
#include <list>			// ���X�g�\��
#include <map>			// �A�z�z��

#include "useful.h"			// �֗��֐�
#include "listManager.h"	// ���X�g�Ǘ�
#include "input.h"			// ���͌��m
#include "inputManager.h"	// ���̓}�l�[�W���[
#include "debugproc.h"		// �f�o�b�O�\��

//************************************************************
//	���������[�N�̃\�[�X�\�� ON/OFF
//************************************************************
#if 1
#ifdef _DEBUG
#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif	// _DEBUG
#endif

#endif	// _PRECOMPILE_H_
