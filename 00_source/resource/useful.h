//============================================================
//
//	�֗��֐��w�b�_�[ [useful.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _USEFUL_H_
#define _USEFUL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "renderState.h"

//************************************************************
//	�}�N����`
//************************************************************
// �֗��}�N��
#define SCREEN_WIDTH	(960)	// �E�C���h�E�̉���
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̏c��
#define MAX_STRING		(128)	// ������̍ő啶����
#define MAX_FILENAME	(256)	// �t�@�C�����̍ő啶����
#define NONE_IDX		(-1)	// �C���f�b�N�X��g�p
#define NONE_STRING		("\0")	// �������g�p
#define SIZE_TILE		(60)	// �}�b�v�^�C���̑傫��

#define HALF_PI	(D3DX_PI * 0.5f)	// �񕪂̈�̉~���� (��/�Q)
#define QRTR_PI	(D3DX_PI * 0.25f)	// �l���̈�̉~���� (��/�S)

#define NUM_ARRAY(a)	(sizeof((a)) / sizeof((a)[0]))	// �z��̗v�f���v�Z

// �������J���}�N��
#define SAFE_UNINIT(p)		if ((p) != nullptr) { (p)->Uninit();		(p) = nullptr; }	// Uninit�֐��̔j���}�N��
#define SAFE_FREE(p)		if ((p) != nullptr) { free((p));			(p) = nullptr; }	// free�֐��̔j���}�N��
#define SAFE_RELEASE(p)		if ((p) != nullptr) { (p)->Release();		(p) = nullptr; }	// Release�֐��̔j���}�N��
#define SAFE_DEL_OBJECT(p)	if ((p) != nullptr) { DeleteObject((p));	(p) = nullptr; }	// DeleteObject�֐��̔j���}�N��
#define SAFE_REF_RELEASE(p)	if ((p) != nullptr) { (p)->Release((p)); }						// �Q�ƃ|�C���^�t��Release�֐��̔j���}�N��
#define SAFE_DELETE(p)		if ((p) != nullptr) { delete	(p);		(p) = nullptr; }	// �z����g�p���Ȃ�delete���g�p����j���}�N��
#define SAFE_DEL_ARRAY(p)	if ((p) != nullptr) { delete[]	(p);		(p) = nullptr; }	// �z����g�p����delete[]���g�p����j���}�N��

// �}�l�[�W���[�֌W
#define GET_MANAGER		(CManager::GetInstance())					// �}�l�[�W���[�C���X�^���X�擾
#define GET_INPUTKEY	(CManager::GetInstance()->GetKeyboard())	// �L�[�{�[�h���擾
#define GET_INPUTMOUSE	(CManager::GetInstance()->GetMouse())		// �}�E�X���擾
#define GET_INPUTPAD	(CManager::GetInstance()->GetPad())			// �p�b�h���擾
#define GET_RETENTION	(CManager::GetInstance()->GetRetention())	// �f�[�^�ۑ����擾
#define GET_RENDERER	(CManager::GetInstance()->GetRenderer())	// �����_���[���擾

#define GET_DEVICE			(CManager::GetInstance()->GetRenderer()->GetDevice())					// �f�o�C�X���擾
#define PLAY_SOUND(label)	(CManager::GetInstance()->GetSound()->Play((CSound::ELabel)(label)))	// �T�E���h�Đ�

// D3DXVECTOR2�֌W
#define VEC2_ZERO	(D3DXVECTOR2(0.0f, 0.0f))	// 0�N���A
#define VEC2_ONE	(D3DXVECTOR2(1.0f, 1.0f))	// 1�N���A
#define VEC2_ALL(f)	(D3DXVECTOR2((f), (f))		// ���l�N���A

// D3DXVECTOR3�֌W
#define VEC3_ZERO	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))	// 0�N���A
#define VEC3_ONE	(D3DXVECTOR3(1.0f, 1.0f, 1.0f))	// 1�N���A
#define VEC3_ALL(f)	(D3DXVECTOR3((f), (f), (f)))	// ���l�N���A

#define SCREEN_CENT	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))	// �E�C���h�E�̒������W
#define SCREEN_SIZE	(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f))	// �E�C���h�E�̉�ʃT�C�Y

// POSGRID2�֌W
#define GRID2_ZERO	(POSGRID2(0, 0))	// 0�N���A
#define GRID2_ONE	(POSGRID2(1, 1))	// 1�N���A

// POSGRID3�֌W
#define GRID3_ZERO	(POSGRID3(0, 0, 0))	// 0�N���A
#define GRID3_ONE	(POSGRID3(1, 1, 1))	// 1�N���A

// D3DXCOLOR�֌W
#define XCOL_ABLACK		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))	// ���F(����)
#define XCOL_BLACK		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	// ���F(�s����)
#define XCOL_AWHITE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))	// ���F(����)
#define XCOL_WHITE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// ���F(�s����)
#define XCOL_ARED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f))	// �ԐF(����)
#define XCOL_RED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// �ԐF(�s����)
#define XCOL_AGREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f))	// �ΐF(����)
#define XCOL_GREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))	// �ΐF(�s����)
#define XCOL_ABLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f))	// �F(����)
#define XCOL_BLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))	// �F(�s����)
#define XCOL_AYELLOW	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f))	// ���F(����)
#define XCOL_YELLOW		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	// ���F(�s����)
#define XCOL_ACYAN		(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.0f))	// ���F(����)
#define XCOL_CYAN		(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))	// ���F(�s����)

// RenderState�֌W
#define RS_BL_NORMAL	(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_INVSRCALPHA))	// �ʏ탿�u�����h
#define RS_BL_ADD		(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// ���Z���u�����h
#define RS_BL_SUB		(CRenderState::SBlendAlpha(D3DBLENDOP_REVSUBTRACT,	D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// ���Z���u�����h

//************************************************************
//	�\���̒�`
//************************************************************
// 2�������W
struct POSGRID2
{
	// �f�t�H���g�R���X�g���N�^
	POSGRID2() : x(0), y(0) {}

	// �����t���R���X�g���N�^
	POSGRID2(const int XY) : x(XY), y(XY) {}
	POSGRID2(const int X, const int Y) : x(X), y(Y) {}

	// �f�X�g���N�^
	~POSGRID2() {}

	// �����o�ϐ�
	int x;	// ������W (x)
	int y;	// ������W (y)

	//********************************************************
	//	���Z�q�I�[�o�[���[�h
	//********************************************************
	// ���Z
	inline POSGRID2 operator+(const POSGRID2& grid) const	{ return POSGRID2(x + grid.x, y + grid.y); }
	inline POSGRID2 operator+(const int nVal) const			{ return POSGRID2(x + nVal, y + nVal); }

	// ���Z
	inline POSGRID2 operator-(const POSGRID2& grid) const	{ return POSGRID2(x - grid.x, y - grid.y); }
	inline POSGRID2 operator-(const int nVal) const			{ return POSGRID2(x - nVal, y - nVal); }
	inline POSGRID2 operator-(void) const					{ return POSGRID2(-x, -y); }

	// ��Z
	inline POSGRID2 operator*(const int nVal) const	{ return POSGRID2(x * nVal, y * nVal); }

	// ���Z
	inline POSGRID2 operator/(const int nVal) const	{ return POSGRID2(x / nVal, y / nVal); }

	// ���Z���
	inline POSGRID2& operator+=(const int nVal)
	{
		x += nVal;
		y += nVal;
		return *this;
	}
	inline POSGRID2& operator+=(const POSGRID2& grid)
	{
		x += grid.x;
		y += grid.y;
		return *this;
	}

	// ���Z���
	inline POSGRID2& operator-=(const int nVal)
	{
		x -= nVal;
		y -= nVal;
		return *this;
	}
	inline POSGRID2& operator-=(const POSGRID2& grid)
	{
		x -= grid.x;
		y -= grid.y;
		return *this;
	}

	// ��Z���
	inline POSGRID2& operator*=(const int nVal)
	{
		x *= nVal;
		y *= nVal;
		return *this;
	}
	inline POSGRID2& operator*=(const POSGRID2& grid)
	{
		x *= grid.x;
		y *= grid.y;
		return *this;
	}

	// ���Z���
	inline POSGRID2& operator/=(const int nVal)
	{
		x /= nVal;
		y /= nVal;
		return *this;
	}
	inline POSGRID2& operator/=(const POSGRID2& grid)
	{
		x /= grid.x;
		y /= grid.y;
		return *this;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/*
		@brief	���W����v���邩�̌���
		@return	���茋��
	*/
	inline bool operator==(const POSGRID2& grid) const
	{
		if (grid.x == x && grid.y == y) { return true; }
		return false;
	}

	/*
		@brief	���W����v���Ȃ����̌���
		@return	���茋��
	*/
	inline bool operator!=(const POSGRID2& grid) const
	{
		if (grid.x != x || grid.y != y) { return true; }
		return false;
	}

	/*
		@brief	������W�̔��]
		@return	���]���ꂽ������W
	*/
	inline POSGRID2 Invert() { return POSGRID2(-x, -y); }

	/*
		@brief	�v�f�����ׂă[����
		@return	���茋��
	*/
	inline bool IsZero() const
	{
		if (x == 0 && y == 0) { return true; }
		return false;
	}
};

// 3�������W
struct POSGRID3
{
	// �f�t�H���g�R���X�g���N�^
	POSGRID3() : x(0), y(0), z(0) {}

	// �����t���R���X�g���N�^
	POSGRID3(const int XYZ) : x(XYZ), y(XYZ), z(XYZ) {}
	POSGRID3(const int X, const int Y, const int Z) : x(X), y(Y), z(Z) {}

	// �f�X�g���N�^
	~POSGRID3() {}

	// �����o�ϐ�
	int x;	// ������W (x)
	int y;	// ������W (y)
	int z;	// ������W (z)

	//********************************************************
	//	���Z�q�I�[�o�[���[�h
	//********************************************************
	// ���Z
	inline POSGRID3 operator+(const POSGRID3& grid) const	{ return POSGRID3(x + grid.x, y + grid.y, z + grid.z); }
	inline POSGRID3 operator+(const int nVal) const			{ return POSGRID3(x + nVal, y + nVal, z + nVal); }

	// ���Z
	inline POSGRID3 operator-(const POSGRID3& grid) const	{ return POSGRID3(x - grid.x, y - grid.y, z - grid.z); }
	inline POSGRID3 operator-(const int nVal) const			{ return POSGRID3(x - nVal, y - nVal, z - nVal); }
	inline POSGRID3 operator-(void) const					{ return POSGRID3(-x, -y, -z); }

	// ��Z
	inline POSGRID3 operator*(const int nVal) const	{ return POSGRID3(x * nVal, y * nVal, z * nVal); }

	// ���Z
	inline POSGRID3 operator/(const int nVal) const	{ return POSGRID3(x / nVal, y / nVal, z / nVal); }

	// ���Z���
	inline POSGRID3& operator+=(const int nVal)
	{
		x += nVal;
		y += nVal;
		z += nVal;
		return *this;
	}
	inline POSGRID3& operator+=(const POSGRID3& grid)
	{
		x += grid.x;
		y += grid.y;
		z += grid.z;
		return *this;
	}

	// ���Z���
	inline POSGRID3& operator-=(const int nVal)
	{
		x -= nVal;
		y -= nVal;
		z -= nVal;
		return *this;
	}
	inline POSGRID3& operator-=(const POSGRID3& grid)
	{
		x -= grid.x;
		y -= grid.y;
		z -= grid.z;
		return *this;
	}

	// ��Z���
	inline POSGRID3& operator*=(const int nVal)
	{
		x *= nVal;
		y *= nVal;
		z *= nVal;
		return *this;
	}
	inline POSGRID3& operator*=(const POSGRID3& grid)
	{
		x *= grid.x;
		y *= grid.y;
		z *= grid.z;
		return *this;
	}

	// ���Z���
	inline POSGRID3& operator/=(const int nVal)
	{
		x /= nVal;
		y /= nVal;
		z /= nVal;
		return *this;
	}
	inline POSGRID3& operator/=(const POSGRID3& grid)
	{
		x /= grid.x;
		y /= grid.y;
		z /= grid.z;
		return *this;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/*
		@brief	���W����v���邩�̌���
		@return	���茋��
	*/
	inline bool operator==(const POSGRID3& grid) const
	{
		if (grid.x == x && grid.y == y && grid.z == z) { return true; }
		return false;
	}

	/*
		@brief	���W����v���Ȃ����̌���
		@return	���茋��
	*/
	inline bool operator!=(const POSGRID3& grid) const
	{
		if (grid.x != x || grid.y != y || grid.z != z) { return true; }
		return false;
	}

	/*
		@brief	������W�̔��]
		@return	���]���ꂽ������W
	*/
	inline POSGRID3 Invert() { return POSGRID3(-x, -y, -z); }

	/*
		@brief	�v�f�����ׂă[����
		@return	���茋��
	*/
	inline bool IsZero() const
	{
		if (x == 0 && y == 0 && z == 0) { return true; }
		return false;
	}
};

// �F
struct Color : public D3DXCOLOR
{
	// �f�t�H���g�R���X�g���N�^
	Color() : D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) {}

	// �����t���R���X�g���N�^
	Color(const float all) : D3DXCOLOR(all, all, all, all) {}
	Color(const float col, const float alpha) : D3DXCOLOR(col, col, col, alpha) {}
	Color(const float r, const float g, const float b, const float a) : D3DXCOLOR(r, g, b, a) {}

	/*
		@brief	D3DCOLOR�^(DWORD)����̏������R���X�g���N�^
	*/
	Color(const D3DCOLOR argb)
	{
		const float fRate = 1.0f / 255.0f;
		a = fRate * (float)(unsigned char)(argb >> 24);
		r = fRate * (float)(unsigned char)(argb >> 16);
		g = fRate * (float)(unsigned char)(argb >> 8);
		b = fRate * (float)(unsigned char)(argb >> 0);
	}

	/*
		@brief	D3DXCOLOR�^(float4)����̏������R���X�g���N�^
	*/
	Color(const D3DXCOLOR col) : D3DXCOLOR(col) {}

	// �f�X�g���N�^
	~Color() {}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	inline void Black(void)					{ *this = Color(0.0f, 0.0f, 0.0f, 1.0f); }		// ���F/�s����
	inline void Black(const float fAlpha)	{ *this = Color(0.0f, 0.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline void White(void)					{ *this = Color(1.0f, 1.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void White(const float fAlpha)	{ *this = Color(1.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline void Red(void)					{ *this = Color(1.0f, 0.0f, 0.0f, 1.0f); }		// �ԐF/�s����
	inline void Red(const float fAlpha)		{ *this = Color(1.0f, 0.0f, 0.0f, fAlpha); }	// �ԐF/�����x
	inline void Green(void)					{ *this = Color(0.0f, 1.0f, 0.0f, 1.0f); }		// �ΐF/�s����
	inline void Green(const float fAlpha)	{ *this = Color(0.0f, 1.0f, 0.0f, fAlpha); }	// �ΐF/�����x
	inline void Blue(void)					{ *this = Color(0.0f, 0.0f, 1.0f, 1.0f); }		// �F/�s����
	inline void Blue(const float fAlpha)	{ *this = Color(0.0f, 0.0f, 1.0f, fAlpha); }	// �F/�����x
	inline void Yellow(void)				{ *this = Color(1.0f, 1.0f, 0.0f, 1.0f); }		// ���F/�s����
	inline void Yellow(const float fAlpha)	{ *this = Color(1.0f, 1.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline void Cyan(void)					{ *this = Color(0.0f, 1.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void Cyan(const float fAlpha)	{ *this = Color(0.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline void Purple(void)				{ *this = Color(1.0f, 0.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void Purple(const float fAlpha)	{ *this = Color(1.0f, 0.0f, 1.0f, fAlpha); }	// ���F/�����x

	/*
		@brief	�J���[�R�[�h����F/�����x�̐ݒ�
	*/
	inline void Code(const std::string& rCode, const float fAlpha)
	{
		assert((int)rCode.size() == 6);
		int R = std::stoi(rCode.substr(0, 2), nullptr, 16);
		int G = std::stoi(rCode.substr(2, 2), nullptr, 16);
		int B = std::stoi(rCode.substr(4, 2), nullptr, 16);
		*this = D3DCOLOR_RGBA(R, G, B, (int)(fAlpha * 255.0f));
	}

	/*
		@brief	�J���[�R�[�h����F�̐ݒ�
	*/
	inline void Code(const std::string& rCode)
	{
		this->Code(rCode, 1.0f);
	}

	/*
		@brief	�����x���[����
		@return	���茋��
	*/
	inline bool IsAlpha(void) const
	{
		if (a <= 0.0f) { return true; }
		return false;
	}
};

//************************************************************
//	�G�C���A�X��`
//************************************************************
using AText = std::vector<std::string>;	// �e�L�X�g�ۑ��^
using ATextBox = std::vector<AText>;	// �����e�L�X�g�ۑ��^

//************************************************************
//	���O��Ԑ錾
//************************************************************
// �֗��֐����
namespace useful
{
	// �ʏ�֐�
	void DivideDigitNum		// ���l�̌������Ƃ̕���
	( // ����
		int *pNumDivide,	// �������ʂ̊i�[�z��
		const int nNum,		// �������鐔�l
		const int nMaxDigit	// �������鐔���̌���
	);
	void NormalizeNormal	// �@���̐��K��
	( // ����
		const D3DXVECTOR3& rPosLeft,	// ���ʒu
		const D3DXVECTOR3& rPosCenter,	// ���S�ʒu
		const D3DXVECTOR3& rPosRight,	// �E�ʒu
		D3DXVECTOR3& rNor				// �@��
	);
	void ReplaceConsecChar	// ��������̘A�������̒u��
	( // ����
		std::string *pDestStr,		// �u���������s��������
		const char cRepChar,		// ���o���镶��
		const std::string& rRepStr,	// �u�������镶����
		const int nRepStrLength		// �u�������镶����̒��� (�ʏ��string��size)
	);

	D3DXVECTOR2 CalcPosParabola		// �o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ʒu�����߂鏈��
	( // ����
		const float fGravity,		// �d��
		const float fMoveX,			// X�ړ���
		const float fDestPosX,		// �ő�X���W
		const float fDestPosY,		// �ő�Y���W
		const float fTime,			// �o�ߎ���
		float *pMaxTime = nullptr,	// �ő�o�ߎ���
		float *pMaxPosY = nullptr	// �ő哞�BY���W
	);
	D3DXVECTOR2 CalcMoveParabola	// �o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ړ��ʂ����߂鏈��
	( // ����
		const float fGravity,		// �d��
		const float fMoveX,			// X�ړ���
		const float fDestPosX,		// �ő�X���W
		const float fDestPosY,		// �ő�Y���W
		const float fTime,			// �o�ߎ���
		float *pMaxTime = nullptr,	// �ő�o�ߎ���
		float *pMaxPosY = nullptr	// �ő哞�BY���W
	);

	float RandomRot(void);			// �����_�������擾
	void NormalizeRot(float& rRot);	// �����̐��K��
	void NormalizeRot(D3DXVECTOR3& rRot);			// �O�������̐��K��
	void PathToBaseName(std::string *pPath);		// �p�X�̃x�[�X�l�[���ϊ�
	void StandardizePathPart(std::string *pPath);	// �p�X��؂�̕W����
	std::string SandString(const std::string &rTop, const std::string &rMain, const std::string &rCur);		// ������̍��E�ǉ� (�}���`�o�C�g������)
	std::wstring SandString(const std::wstring &rTop, const std::wstring &rMain, const std::wstring &rCur);	// ������̍��E�ǉ� (���C�h������)
	std::wstring MultiByteToWide(const std::string &rSrcStr);	// �}���`�o�C�g������̃��C�h������ϊ�
	std::string WideToMultiByte(const std::wstring &rSrcStr);	// ���C�h������̃}���`�o�C�g������ϊ�
	void VecToRot(const D3DXVECTOR3& rVec, float *pPhi, float *pTheta);		// �x�N�g���̌����ϊ�
	void RotToVec(const float fPhi, const float fTheta, D3DXVECTOR3 *pVec);	// �����̃x�N�g���ϊ�
	float GetTexWidthFromAspect(const float fHeight, const int nTexID);		// �c������A�X�y�N�g����l�����������擾
	float GetTexHeightFromAspect(const float fWidth, const int nTexID);		// ��������A�X�y�N�g����l�������c���擾
	D3DXVECTOR3 GetMatrixPosition(const D3DXMATRIX& rMtx);	// �}�g���b�N�X�ʒu�擾
	D3DXVECTOR3 GetMatrixRotation(const D3DXMATRIX& rMtx);	// �}�g���b�N�X�����擾
	D3DXVECTOR3 GetMatrixScaling(const D3DXMATRIX& rMtx);	// �}�g���b�N�X�g�嗦�擾

	// �e���v���[�g�֐�
	template<class T> T *ZeroClear(T *pClear);	// �[���N���A
	template<class T> bool LimitNum		// �l�͈͓̔�����
	( // ����
		T& rNum,		// �������l
		const T min,	// �ŏ��͈�
		const T max		// �ő�͈�
	);
	template<class T> bool LimitMinNum	// �l�̍ŏ��l����
	( // ����
		T& rNum,		// �������l
		const T min		// �ŏ��͈�
	);
	template<class T> bool LimitMaxNum	// �l�̍ő�l����
	( // ����
		T& rNum,		// �������l
		const T max		// �ő�͈�
	);
	template<class T> float ValueToRate	// �l�̊����ϊ�
	( // ����
		const T num,	// ���������鐔�l
		const T min,	// �ŏ��͈�
		const T max		// �ő�͈�
	);
	template<class T> T RateToValue		// �����̒l�ϊ�
	( // ����
		const float fRate,	// �l�����鐔�l
		const T min,		// �ŏ��͈�
		const T max			// �ő�͈�
	);
	template<class T> void SortNum		// �l�̃\�[�g
	( // ����
		T *pSortNum,		// �\�[�g�z��
		const int nMaxKeep	// �z��T�C�Y
	);
	template<class T> void Shuffle		// �V���b�t��
	(
		T *pShuffleData,		// �V���b�t���z��
		const int nMaxShuffle	// �z��T�C�Y
	);
}

// �C�[�W���O�֐����
namespace easeing
{
	// �ʏ�֐�
	inline float Liner(const float x)		{ return x; }

	inline float InSine(const float x)		{ return 1.0f - cosf((x * D3DX_PI) * 0.5f); }
	inline float OutSine(const float x)		{ return sinf((x * D3DX_PI) * 0.5f); }
	inline float InOutSine(const float x)	{ return -(cosf(x * D3DX_PI) - 1.0f) * 0.5f; }

	inline float InQuad(const float x)		{ return x * x; }
	inline float OutQuad(const float x)		{ return 1.0f - (1.0f - x) * (1.0f - x); }
	inline float InOutQuad(const float x)	{ return (x < 0.5f) ? (2.0f * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 2.0f) * 0.5f); }

	inline float InCubic(const float x)		{ return x * x * x; }
	inline float OutCubic(const float x)	{ return 1.0f - powf(1.0f - x, 3.0f); }
	inline float InOutCubic(const float x)	{ return (x < 0.5f) ? (4.0f * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 3.0f) * 0.5f); }

	inline float InQuart(const float x)		{ return x * x * x * x; }
	inline float OutQuart(const float x)	{ return 1.0f - powf(1.0f - x, 4.0f); }
	inline float InOutQuart(const float x)	{ return (x < 0.5f) ? (8.0f * x * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 4.0f) * 0.5f); }

	inline float InQuint(const float x)		{ return x * x * x * x * x; }
	inline float OutQuint(const float x)	{ return 1.0f - powf(1.0f - x, 5.0f); }
	inline float InOutQuint(const float x)	{ return (x < 0.5f) ? (16.0f * x * x * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 5.0f) * 0.5f); }

	// �e���v���[�g�֐�
	template<class T> inline float Liner(T num, const T min, const T max)		{ return Liner(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InSine(T num, const T min, const T max)		{ return InSine(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutSine(T num, const T min, const T max)		{ return OutSine(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutSine(T num, const T min, const T max)	{ return InOutSine(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuad(T num, const T min, const T max)		{ return InQuad(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuad(T num, const T min, const T max)		{ return OutQuad(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuad(T num, const T min, const T max)	{ return InOutQuad(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InCubic(T num, const T min, const T max)		{ return InCubic(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutCubic(T num, const T min, const T max)	{ return OutCubic(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutCubic(T num, const T min, const T max)	{ return InOutCubic(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuart(T num, const T min, const T max)		{ return InQuart(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuart(T num, const T min, const T max)	{ return OutQuart(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuart(T num, const T min, const T max)	{ return InOutQuart(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuint(T num, const T min, const T max)		{ return InQuint(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuint(T num, const T min, const T max)	{ return OutQuint(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuint(T num, const T min, const T max)	{ return InOutQuint(useful::ValueToRate(num, min, max)); }
}

// �J���[�֐����
namespace color
{
	inline Color Black(void)				{ return Color(0.0f, 0.0f, 0.0f, 1.0f); }	// ���F/�s����
	inline Color Black(const float fAlpha)	{ return Color(0.0f, 0.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline Color White(void)				{ return Color(1.0f, 1.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline Color White(const float fAlpha)	{ return Color(1.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline Color Red(void)					{ return Color(1.0f, 0.0f, 0.0f, 1.0f); }	// �ԐF/�s����
	inline Color Red(const float fAlpha)	{ return Color(1.0f, 0.0f, 0.0f, fAlpha); }	// �ԐF/�����x
	inline Color Green(void)				{ return Color(0.0f, 1.0f, 0.0f, 1.0f); }	// �ΐF/�s����
	inline Color Green(const float fAlpha)	{ return Color(0.0f, 1.0f, 0.0f, fAlpha); }	// �ΐF/�����x
	inline Color Blue(void)					{ return Color(0.0f, 0.0f, 1.0f, 1.0f); }	// �F/�s����
	inline Color Blue(const float fAlpha)	{ return Color(0.0f, 0.0f, 1.0f, fAlpha); }	// �F/�����x
	inline Color Yellow(void)				{ return Color(1.0f, 1.0f, 0.0f, 1.0f); }	// ���F/�s����
	inline Color Yellow(const float fAlpha)	{ return Color(1.0f, 1.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline Color Cyan(void)					{ return Color(0.0f, 1.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline Color Cyan(const float fAlpha)	{ return Color(0.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline Color Purple(void)				{ return Color(1.0f, 0.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline Color Purple(const float fAlpha)	{ return Color(1.0f, 0.0f, 1.0f, fAlpha); }	// ���F/�����x

	// �J���[�R�[�h/�s����
	inline Color Code(const std::string& rCode, const float fAlpha)
	{
		assert((int)rCode.size() == 6);
		int R = std::stoi(rCode.substr(0, 2), nullptr, 16);
		int G = std::stoi(rCode.substr(2, 2), nullptr, 16);
		int B = std::stoi(rCode.substr(4, 2), nullptr, 16);
		Color col = D3DCOLOR_RGBA(R, G, B, (int)(fAlpha * 255.0f));
		return col;
	}

	// �J���[�R�[�h/�����x
	inline Color Code(const std::string& rCode)
	{
		return Code(rCode, 1.0f);
	}
}

// �}�e���A���֐����
namespace material
{
	// ���F�}�e���A���擾
	inline D3DXMATERIAL Black(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Black();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL White(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::White();
		return mat;
	}

	// �ԐF�}�e���A���擾
	inline D3DXMATERIAL Red(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Red();
		return mat;
	}

	// �ΐF�}�e���A���擾
	inline D3DXMATERIAL Green(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Green();
		return mat;
	}

	// �F�}�e���A���擾
	inline D3DXMATERIAL Blue(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Blue();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Yellow(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Yellow();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Cyan(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Cyan();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Purple(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Purple();
		return mat;
	}
}

//************************************************************
//	�e���v���[�g�֐�
//************************************************************
//	�֗��֐����
//************************************************************
//============================================================
//	�[���N���A
//============================================================
template<class T> T *useful::ZeroClear(T *pClear)
{
	// ���������[���N���A
	memset(pClear, 0, sizeof(*pClear));

	// �N���A��̃A�h���X��Ԃ�
	return pClear;
}

//============================================================
//	�l�͈͓̔���������
//============================================================
template<class T> bool useful::LimitNum
(
	T& rNum,		// �������l
	const T min,	// �ŏ��͈�
	const T max		// �ő�͈�
)
{
	if (rNum < min)
	{ // �������l���ŏ��͈͂𒴂��Ă����ꍇ

		// �͈͓��ɕ␳
		rNum = min;

		// �^��Ԃ�
		return true;
	}
	else if (rNum > max)
	{ // �������l���ő�͈͂𒴂��Ă����ꍇ

		// �͈͓��ɕ␳
		rNum = max;

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�l�̍ŏ��l��������
//============================================================
template<class T> bool useful::LimitMinNum
(
	T& rNum,	// �������l
	const T min	// �ŏ��͈�
)
{
	if (rNum < min)
	{ // �������l���ŏ��͈͂𒴂��Ă����ꍇ

		// �͈͓��ɕ␳
		rNum = min;

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�l�̍ő�l��������
//============================================================
template<class T> bool useful::LimitMaxNum
(
	T& rNum,	// �������l
	const T max	// �ő�͈�
)
{
	if (rNum > max)
	{ // �������l���ő�͈͂𒴂��Ă����ꍇ

		// �͈͓��ɕ␳
		rNum = max;

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�l�̊����ϊ�
//============================================================
template<class T> float useful::ValueToRate
(
	const T num,	// ���������鐔�l
	const T min,	// �ŏ��͈�
	const T max		// �ő�͈�
)
{
	// ���鐔�����߂�
	float fDiv = static_cast<float>(max) - static_cast<float>(min);
	if (fDiv == 0.0f) { return 0.0f; }	// 0���Z�΍�

	// �����ϊ������l��Ԃ�
	return (static_cast<float>(num) - static_cast<float>(min)) / fDiv;
}

//============================================================
//	�����̒l�ϊ�
//============================================================
template<class T> T useful::RateToValue
(
	const float fRate,	// �l�����鐔�l
	const T min,		// �ŏ��͈�
	const T max			// �ő�͈�
)
{
	// �l�ϊ�����������Ԃ�
	return static_cast<T>((fRate * (max - min)) + min);
}

//============================================================
//	�\�[�g����
//============================================================
template<class T> void useful::SortNum
(
	T *pSortNum,		// �\�[�g�z��
	const int nMaxKeep	// �z��T�C�Y
)
{
	// �ϐ���錾
	T	keepNum;		// �\�[�g�p
	int	nCurrentMaxID;	// �ő�l�̃C���f�b�N�X

	for (int nCntKeep = 0; nCntKeep < (nMaxKeep - 1); nCntKeep++)
	{ // ����ւ���l�̑��� -1�񕪌J��Ԃ�

		// ���݂̌J��Ԃ������� (�v�f1�Ƃ���)
		nCurrentMaxID = nCntKeep;

		for (int nCntSort = nCntKeep + 1; nCntSort < nMaxKeep; nCntSort++)
		{ // ����ւ���l�̑��� -nCntKeep���J��Ԃ�

			if (pSortNum[nCurrentMaxID] < pSortNum[nCntSort])
			{ // �ő�l�ɐݒ肳��Ă���l���A���݂̒l�̂ق����傫���ꍇ

				// ���݂̗v�f�ԍ����ő�l�ɐݒ�
				nCurrentMaxID = nCntSort;
			}
		}

		if (nCntKeep != nCurrentMaxID)
		{ // �ő�l�̗v�f�ԍ��ɕϓ����������ꍇ

			// �v�f�̓���ւ�
			keepNum					= pSortNum[nCntKeep];
			pSortNum[nCntKeep]		= pSortNum[nCurrentMaxID];
			pSortNum[nCurrentMaxID]	= keepNum;
		}
	}
}

//============================================================
//	�V���b�t������
//============================================================
template<class T> void useful::Shuffle
(
	T *pShuffleData,		// �V���b�t���z��
	const int nMaxShuffle	// �z��T�C�Y
)
{
	for (int nCntShu = nMaxShuffle - 1; nCntShu > 0; nCntShu--)
	{ // �����̑������J��Ԃ�

		// �ϐ���錾
		T swap;		// �v�f�̓���ւ��p
		int nRandom = rand() % nCntShu;	// �v�f�����ւ���C���f�b�N�X

		// �v�f�̓���ւ�
		swap					= pShuffleData[nRandom];
		pShuffleData[nRandom]	= pShuffleData[nCntShu];
		pShuffleData[nCntShu]	= swap;
	}
}

#endif	// _USEFUL_H_
