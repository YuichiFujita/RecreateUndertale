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
#define GET_MANAGER			(CManager::GetInstance())					// �}�l�[�W���[�C���X�^���X�擾
#define GET_INPUTKEY		(CManager::GetInstance()->GetKeyboard())	// �L�[�{�[�h���擾
#define GET_INPUTMOUSE		(CManager::GetInstance()->GetMouse())		// �}�E�X���擾
#define GET_INPUTPAD		(CManager::GetInstance()->GetPad())			// �p�b�h���擾
#define GET_RETENTION		(CManager::GetInstance()->GetRetention())	// �f�[�^�ۑ����擾
#define GET_RENDERER		(CManager::GetInstance()->GetRenderer())	// �����_���[���擾
#define GET_DEVICE			(CManager::GetInstance()->GetRenderer()->GetDevice())					// �f�o�C�X���擾
#define PLAY_SOUND(label)	(CManager::GetInstance()->GetSound()->Play((CSound::ELabel)(label)))	// �T�E���h�Đ�

// VECTOR2�֌W
#define VEC2_ZERO	(VECTOR2())		// 0�N���A
#define VEC2_ONE	(VECTOR2(1.0f))	// 1�N���A

// VECTOR3�֌W
#define VEC3_ZERO	(VECTOR3())		// 0�N���A
#define VEC3_ONE	(VECTOR3(1.0f))	// 1�N���A
#define SCREEN_CENT	(VECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))	// �E�C���h�E�̒������W
#define SCREEN_SIZE	(VECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f))	// �E�C���h�E�̉�ʃT�C�Y

// POSGRID2�֌W
#define GRID2_ZERO	(POSGRID2())	// 0�N���A
#define GRID2_ONE	(POSGRID2(1))	// 1�N���A

// POSGRID3�֌W
#define GRID3_ZERO	(POSGRID3())	// 0�N���A
#define GRID3_ONE	(POSGRID3(1))	// 1�N���A

// MATRIX�֌W
#define MTX_IDENT	(MATRIX())	// �P�ʃ}�g���b�N�X�N���A

// RenderState�֌W
#define RS_BL_NOR	(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_INVSRCALPHA))	// �ʏ탿�u�����h
#define RS_BL_ADD	(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// ���Z���u�����h
#define RS_BL_SUB	(CRenderState::SBlendAlpha(D3DBLENDOP_REVSUBTRACT,	D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// ���Z���u�����h

//************************************************************
//	�񋓌^��`
//************************************************************
// ���z�u��
enum EAlignX
{
	XALIGN_LEFT = 0,	// ������
	XALIGN_CENTER,		// ��������
	XALIGN_RIGHT,		// �E����
	XALIGN_MAX,			// ���̗񋓌^�̑���
};

// �c�z�u��
enum EAlignY
{
	YALIGN_TOP = 0,	// �㑵��
	YALIGN_CENTER,	// ��������
	YALIGN_BOTTOM,	// ������
	YALIGN_MAX,		// ���̗񋓌^�̑���
};

//************************************************************
//	�\���̒�`
//************************************************************
// 2�����x�N�g��
struct VECTOR2 : public D3DXVECTOR2
{
	// �R���X�g���N�^�p��
	using D3DXVECTOR2::D3DXVECTOR2;

	// ���Z�q�I�[�o�[���C�h�Č��J
	using D3DXVECTOR2::operator+=;
	using D3DXVECTOR2::operator-=;
	using D3DXVECTOR2::operator*=;
	using D3DXVECTOR2::operator/=;
	using D3DXVECTOR2::operator+;
	using D3DXVECTOR2::operator-;
	using D3DXVECTOR2::operator*;
	using D3DXVECTOR2::operator/;
	using D3DXVECTOR2::operator==;
	using D3DXVECTOR2::operator!=;

	// �f�t�H���g�R���X�g���N�^
	VECTOR2() : D3DXVECTOR2(0.0f, 0.0f) {}

	// �����t���R���X�g���N�^
	VECTOR2(const float XY)				: D3DXVECTOR2(XY, XY)			{}
	VECTOR2(const D3DXVECTOR2& VEC2)	: D3DXVECTOR2(VEC2.x, VEC2.y)	{}
	VECTOR2(const D3DXVECTOR3& VEC3)	: D3DXVECTOR2(VEC3.x, VEC3.y)	{}

	// �f�X�g���N�^
	~VECTOR2() {}

	//********************************************************
	//	���Z�q�I�[�o�[���[�h
	//********************************************************
	// ���Z
	inline VECTOR2 operator+(const float fVal) const { return VECTOR2(x + fVal, y + fVal); }

	// ���Z
	inline VECTOR2 operator-(const float fVal) const { return VECTOR2(x - fVal, y - fVal); }

	// ���Z���
	inline VECTOR2& operator+=(const float fVal)
	{
		x += fVal;
		y += fVal;
		return *this;
	}

	// ���Z���
	inline VECTOR2& operator-=(const float fVal)
	{
		x -= fVal;
		y -= fVal;
		return *this;
	}

	// ��Z���
	inline VECTOR2& operator*=(const VECTOR2& rVec)
	{
		x *= rVec.x;
		y *= rVec.y;
		return *this;
	}

	// ���Z���
	inline VECTOR2& operator/=(const VECTOR2& rVec)
	{
		x /= rVec.x;
		y /= rVec.y;
		return *this;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/* @brief �x�N�g���̐��K�� */
	inline void Normal() { D3DXVec2Normalize(this, this); }

	/* @brief �x�N�g���̔��] */
	inline void Invert() { *this = VECTOR2(-x, -y); }

	/*
		@brief	���e�����덷�͈͓̔��ɂ��邩
		@param	const float [in] ���e�͈�
		@return	���茋��
	*/
	inline bool IsNearlyZero(const float fRange) const
	{
		if (fabsf(x) <= fRange && fabsf(y) <= fRange) { return true; }
		return false;
	}

	/*
		@brief	�v�f�����ׂă[����
		@return	���茋��
	*/
	inline bool IsZero() const
	{
		if (x == 0.0f && y == 0.0f) { return true; }
		return false;
	}
};

// 3�����x�N�g��
struct VECTOR3 : public D3DXVECTOR3
{
	// �R���X�g���N�^�p��
	using D3DXVECTOR3::D3DXVECTOR3;

	// ���Z�q�I�[�o�[���C�h�Č��J
	using D3DXVECTOR3::operator+=;
	using D3DXVECTOR3::operator-=;
	using D3DXVECTOR3::operator*=;
	using D3DXVECTOR3::operator/=;
	using D3DXVECTOR3::operator+;
	using D3DXVECTOR3::operator-;
	using D3DXVECTOR3::operator*;
	using D3DXVECTOR3::operator/;
	using D3DXVECTOR3::operator==;
	using D3DXVECTOR3::operator!=;

	// �f�t�H���g�R���X�g���N�^
	VECTOR3() : D3DXVECTOR3(0.0f, 0.0f, 0.0f) {}

	// �����t���R���X�g���N�^
	VECTOR3(const float XYZ)			: D3DXVECTOR3(XYZ, XYZ, XYZ)			{}
	VECTOR3(const D3DXVECTOR3& VEC3)	: D3DXVECTOR3(VEC3.x, VEC3.y, VEC3.z)	{}
	VECTOR3(const D3DXVECTOR2& VEC2)	: D3DXVECTOR3(VEC2.x, VEC2.y, 0.0f)		{}

	// �f�X�g���N�^
	~VECTOR3() {}

	//********************************************************
	//	���Z�q�I�[�o�[���[�h
	//********************************************************
	// ���Z
	inline VECTOR3 operator+(const float fVal) const { return VECTOR3(x + fVal, y + fVal, z + fVal); }

	// ���Z
	inline VECTOR3 operator-(const float fVal) const { return VECTOR3(x - fVal, y - fVal, z - fVal); }

	// ���Z���
	inline VECTOR3& operator+=(const float fVal)
	{
		x += fVal;
		y += fVal;
		z += fVal;
		return *this;
	}

	// ���Z���
	inline VECTOR3& operator-=(const float fVal)
	{
		x -= fVal;
		y -= fVal;
		z -= fVal;
		return *this;
	}

	// ��Z���
	inline VECTOR3& operator*=(const VECTOR3& rVec)
	{
		x *= rVec.x;
		y *= rVec.y;
		z *= rVec.z;
		return *this;
	}

	// ���Z���
	inline VECTOR3& operator/=(const VECTOR3& rVec)
	{
		x /= rVec.x;
		y /= rVec.y;
		z /= rVec.z;
		return *this;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/* @brief �x�N�g���̐��K�� */
	inline void Normal() { D3DXVec3Normalize(this, this); }

	/* @brief �x�N�g���̔��] */
	inline void Invert() { *this = VECTOR3(-x, -y, -z); }

	/*
		@brief	���e�����덷�͈͓̔��ɂ��邩
		@param	const float [in] ���e�͈�
		@return	���茋��
	*/
	inline bool IsNearlyZero(const float fRange) const
	{
		if (fabsf(x) <= fRange && fabsf(y) <= fRange && fabsf(z) <= fRange) { return true; }
		return false;
	}

	/*
		@brief	�v�f�����ׂă[����
		@return	���茋��
	*/
	inline bool IsZero() const
	{
		if (x == 0.0f && y == 0.0f && z == 0.0f) { return true; }
		return false;
	}
};

// 2�������W
struct POSGRID2
{
	// �f�t�H���g�R���X�g���N�^
	POSGRID2() : x(0), y(0) {}

	// �����t���R���X�g���N�^
	POSGRID2(const int XY)				: x(XY), y(XY)	{}
	POSGRID2(const int X, const int Y)	: x(X), y(Y)	{}

	// �f�X�g���N�^
	~POSGRID2() {}

	// �����o�ϐ�
	int x;	// ������W (x)
	int y;	// ������W (y)

	//********************************************************
	//	���Z�q�I�[�o�[���[�h
	//********************************************************
	// ���Z
	inline POSGRID2 operator+(const POSGRID2& rGrid) const	{ return POSGRID2(x + rGrid.x, y + rGrid.y); }
	inline POSGRID2 operator+(const int nVal) const			{ return POSGRID2(x + nVal, y + nVal); }
	inline POSGRID2 operator+() const						{ return *this; }

	// ���Z
	inline POSGRID2 operator-(const POSGRID2& rGrid) const	{ return POSGRID2(x - rGrid.x, y - rGrid.y); }
	inline POSGRID2 operator-(const int nVal) const			{ return POSGRID2(x - nVal, y - nVal); }
	inline POSGRID2 operator-() const						{ return POSGRID2(-x, -y); }

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
	inline POSGRID2& operator+=(const POSGRID2& rGrid)
	{
		x += rGrid.x;
		y += rGrid.y;
		return *this;
	}

	// ���Z���
	inline POSGRID2& operator-=(const int nVal)
	{
		x -= nVal;
		y -= nVal;
		return *this;
	}
	inline POSGRID2& operator-=(const POSGRID2& rGrid)
	{
		x -= rGrid.x;
		y -= rGrid.y;
		return *this;
	}

	// ��Z���
	inline POSGRID2& operator*=(const int nVal)
	{
		x *= nVal;
		y *= nVal;
		return *this;
	}
	inline POSGRID2& operator*=(const POSGRID2& rGrid)
	{
		x *= rGrid.x;
		y *= rGrid.y;
		return *this;
	}

	// ���Z���
	inline POSGRID2& operator/=(const int nVal)
	{
		x /= nVal;
		y /= nVal;
		return *this;
	}
	inline POSGRID2& operator/=(const POSGRID2& rGrid)
	{
		x /= rGrid.x;
		y /= rGrid.y;
		return *this;
	}

	/*
		@brief	���W����v���邩�̌���
		@param	const POSGRID2& [in] ���肷�������W
		@return	���茋��
	*/
	inline bool operator==(const POSGRID2& rGrid) const
	{
		if (rGrid.x == x && rGrid.y == y) { return true; }
		return false;
	}

	/*
		@brief	���W����v���Ȃ����̌���
		@param	const POSGRID2& [in] ���肷�������W
		@return	���茋��
	*/
	inline bool operator!=(const POSGRID2& rGrid) const
	{
		if (rGrid.x != x || rGrid.y != y) { return true; }
		return false;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/* @brief ������W�̔��] */
	inline void Invert() { *this = POSGRID2(-x, -y); }

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
	POSGRID3(const int XYZ)							: x(XYZ), y(XYZ), z(XYZ)	{}
	POSGRID3(const int X, const int Y, const int Z)	: x(X), y(Y), z(Z)			{}

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
	inline POSGRID3 operator+(const POSGRID3& rGrid) const	{ return POSGRID3(x + rGrid.x, y + rGrid.y, z + rGrid.z); }
	inline POSGRID3 operator+(const int nVal) const			{ return POSGRID3(x + nVal, y + nVal, z + nVal); }
	inline POSGRID3 operator+() const						{ return *this; }

	// ���Z
	inline POSGRID3 operator-(const POSGRID3& rGrid) const	{ return POSGRID3(x - rGrid.x, y - rGrid.y, z - rGrid.z); }
	inline POSGRID3 operator-(const int nVal) const			{ return POSGRID3(x - nVal, y - nVal, z - nVal); }
	inline POSGRID3 operator-() const						{ return POSGRID3(-x, -y, -z); }

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
	inline POSGRID3& operator+=(const POSGRID3& rGrid)
	{
		x += rGrid.x;
		y += rGrid.y;
		z += rGrid.z;
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
	inline POSGRID3& operator-=(const POSGRID3& rGrid)
	{
		x -= rGrid.x;
		y -= rGrid.y;
		z -= rGrid.z;
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
	inline POSGRID3& operator*=(const POSGRID3& rGrid)
	{
		x *= rGrid.x;
		y *= rGrid.y;
		z *= rGrid.z;
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
	inline POSGRID3& operator/=(const POSGRID3& rGrid)
	{
		x /= rGrid.x;
		y /= rGrid.y;
		z /= rGrid.z;
		return *this;
	}

	/*
		@brief	���W����v���邩�̌���
		@param	const POSGRID3& [in] ���肷�������W
		@return	���茋��
	*/
	inline bool operator==(const POSGRID3& rGrid) const
	{
		if (rGrid.x == x && rGrid.y == y && rGrid.z == z) { return true; }
		return false;
	}

	/*
		@brief	���W����v���Ȃ����̌���
		@param	const POSGRID3& [in] ���肷�������W
		@return	���茋��
	*/
	inline bool operator!=(const POSGRID3& rGrid) const
	{
		if (rGrid.x != x || rGrid.y != y || rGrid.z != z) { return true; }
		return false;
	}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/* @brief ������W�̔��] */
	inline void Invert() { *this = POSGRID3(-x, -y, -z); }

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

// �}�g���b�N�X
struct MATRIX : public D3DXMATRIX
{
	// �R���X�g���N�^�p��
	using D3DXMATRIX::D3DXMATRIX;

	// ���Z�q�I�[�o�[���C�h�Č��J
	using D3DXMATRIX::operator+=;
	using D3DXMATRIX::operator-=;
	using D3DXMATRIX::operator*=;
	using D3DXMATRIX::operator/=;
	using D3DXMATRIX::operator+;
	using D3DXMATRIX::operator-;
	using D3DXMATRIX::operator*;
	using D3DXMATRIX::operator/;
	using D3DXMATRIX::operator==;
	using D3DXMATRIX::operator!=;

	// �f�t�H���g�R���X�g���N�^
	MATRIX() : D3DXMATRIX(1.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, 0.0f,
						  0.0f, 0.0f, 1.0f, 0.0f,
						  0.0f, 0.0f, 0.0f, 1.0f) {}

	// �����t���R���X�g���N�^
	MATRIX(const D3DXMATRIX& MTX) : D3DXMATRIX(MTX) {}

	// �f�X�g���N�^
	~MATRIX() {}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	/* @brief �P�ʃ}�g���b�N�X�� */
	inline void Identity() { D3DXMatrixIdentity(this); }

	/* @brief �t�}�g���b�N�X�� */
	inline void Inverse() { D3DXMatrixInverse(this, nullptr, this); }

	/*
		@brief	�}�g���b�N�X���|�����킹��
		@param	const MATRIX& [in] �|�����킹��}�g���b�N�X
		@param	const MATRIX& [in] �|�����킹��}�g���b�N�X
	*/
	inline void Multiply(const MATRIX& rMtx0, const MATRIX& rMtx1) { D3DXMatrixMultiply(this, &rMtx0, &rMtx1); }

	/*
		@brief	�ʒu�}�g���b�N�X�̌v�Z
		@param	const VECTOR3& [in] �Q�Ƃ���ʒu
	*/
	inline void Translation(const VECTOR3& rPos) { D3DXMatrixTranslation(this, rPos.x, rPos.y, rPos.z); }

	/*
		@brief	�ʒu�}�g���b�N�X�̌v�Z
		@param	const float [in] �Q�Ƃ���X���W
		@param	const float [in] �Q�Ƃ���Y���W
		@param	const float [in] �Q�Ƃ���Z���W
	*/
	inline void Translation(const float fX, const float fY, const float fZ) { D3DXMatrixTranslation(this, fX, fY, fZ); }

	/*
		@brief	�����}�g���b�N�X�̌v�Z
		@param	const VECTOR3& [in] �Q�Ƃ������
	*/
	inline void Rotation(const VECTOR3& rRot) { D3DXMatrixRotationYawPitchRoll(this, rRot.y, rRot.x, rRot.z); }

	/*
		@brief	�����}�g���b�N�X�̌v�Z
		@param	const float [in] �Q�Ƃ���Yaw����
		@param	const float [in] �Q�Ƃ���Pitch����
		@param	const float [in] �Q�Ƃ���Roll����
	*/
	inline void Rotation(const float fYaw, const float fPitch, const float fRoll) { D3DXMatrixRotationYawPitchRoll(this, fYaw, fPitch, fRoll); }

	/*
		@brief	�g�嗦�}�g���b�N�X�̌v�Z
		@param	const VECTOR3& [in] �Q�Ƃ���g�嗦
	*/
	inline void Scaling(const VECTOR3& rScale) { D3DXMatrixScaling(this, rScale.x, rScale.y, rScale.z); }

	/*
		@brief	�g�嗦�}�g���b�N�X�̌v�Z
		@param	const float [in] �Q�Ƃ���X�g�嗦
		@param	const float [in] �Q�Ƃ���Y�g�嗦
		@param	const float [in] �Q�Ƃ���Z�g�嗦
	*/
	inline void Scaling(const float fX, const float fY, const float fZ) { D3DXMatrixScaling(this, fX, fY, fZ); }

	/*
		@brief	�}�g���b�N�X�ʒu�̎擾
		@return	�}�g���b�N�X�̈ʒu
	*/
	inline VECTOR3 GetPosition() const { return VECTOR3(this->_41, this->_42, this->_43); }

	/*
		@brief	�}�g���b�N�X�����̎擾
		@return	�}�g���b�N�X�̌���
	*/
	inline VECTOR3 GetRotation() const
	{
		float fYaw, fPitch, fRoll;	// �v�Z���ʂ̕ۑ��p
		float fCosPitch;			// �����v�Z�p

		// �}�g���b�N�X����Pitch�����߂�
		fPitch = asinf(-(*this)._32);

		// �}�g���b�N�X����Yaw�ERoll�����߂�
		fCosPitch = cosf(fPitch);
		if (fabs(fCosPitch) > 0.0001f)
		{ // Pitch�̊p�x���v�Z�ɖ��Ȃ��ꍇ

			fYaw  = atan2f(this->_31 / fCosPitch, this->_33 / fCosPitch);
			fRoll = atan2f(this->_12 / fCosPitch, this->_22 / fCosPitch);
		}
		else
		{ // Pitch��90�x�܂���-90�x�̏ꍇ

			fYaw  = 0.0f;	// ���m�Ȓl�����Ȃ��̂�0.0f�Ƃ���
			fRoll = atan2f(this->_21, this->_11);
		}

		// �}�g���b�N�X�̌�����Ԃ�
		return VECTOR3(fPitch, fYaw, fRoll);
	}

	/*
		@brief	�}�g���b�N�X�g�嗦�̎擾
		@return	�}�g���b�N�X�̊g�嗦
	*/
	inline VECTOR3 GetScale() const
	{
		VECTOR3 scale;
		scale.x = sqrtf(this->_11 * this->_11 + this->_12 * this->_12 + this->_13 * this->_13);
		scale.y = sqrtf(this->_21 * this->_21 + this->_22 * this->_22 + this->_23 * this->_23);
		scale.z = sqrtf(this->_31 * this->_31 + this->_32 * this->_32 + this->_33 * this->_33);
		return scale;
	}
};

// �F
struct COLOR : public D3DXCOLOR
{
	// �R���X�g���N�^�p��
	using D3DXCOLOR::D3DXCOLOR;

	// ���Z�q�I�[�o�[���C�h�Č��J
	using D3DXCOLOR::operator+=;
	using D3DXCOLOR::operator-=;
	using D3DXCOLOR::operator*=;
	using D3DXCOLOR::operator/=;
	using D3DXCOLOR::operator+;
	using D3DXCOLOR::operator-;
	using D3DXCOLOR::operator*;
	using D3DXCOLOR::operator/;
	using D3DXCOLOR::operator==;
	using D3DXCOLOR::operator!=;

	// �f�t�H���g�R���X�g���N�^
	COLOR() : D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) {}

	// �����t���R���X�g���N�^
	COLOR(const float ALL)						: D3DXCOLOR(ALL, ALL, ALL, ALL)		{}
	COLOR(const float COL, const float ALPHA)	: D3DXCOLOR(COL, COL, COL, ALPHA)	{}
	COLOR(const D3DXCOLOR& COL)					: D3DXCOLOR(COL)					{}

	// �f�X�g���N�^
	~COLOR() {}

	//********************************************************
	//	�����o�֐�
	//********************************************************
	inline void Black()						{ *this = COLOR(0.0f, 0.0f, 0.0f, 1.0f); }		// ���F/�s����
	inline void Black(const float fAlpha)	{ *this = COLOR(0.0f, 0.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline void White()						{ *this = COLOR(1.0f, 1.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void White(const float fAlpha)	{ *this = COLOR(1.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline void Red()						{ *this = COLOR(1.0f, 0.0f, 0.0f, 1.0f); }		// �ԐF/�s����
	inline void Red(const float fAlpha)		{ *this = COLOR(1.0f, 0.0f, 0.0f, fAlpha); }	// �ԐF/�����x
	inline void Green()						{ *this = COLOR(0.0f, 1.0f, 0.0f, 1.0f); }		// �ΐF/�s����
	inline void Green(const float fAlpha)	{ *this = COLOR(0.0f, 1.0f, 0.0f, fAlpha); }	// �ΐF/�����x
	inline void Blue()						{ *this = COLOR(0.0f, 0.0f, 1.0f, 1.0f); }		// �F/�s����
	inline void Blue(const float fAlpha)	{ *this = COLOR(0.0f, 0.0f, 1.0f, fAlpha); }	// �F/�����x
	inline void Yellow()					{ *this = COLOR(1.0f, 1.0f, 0.0f, 1.0f); }		// ���F/�s����
	inline void Yellow(const float fAlpha)	{ *this = COLOR(1.0f, 1.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline void Cyan()						{ *this = COLOR(0.0f, 1.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void Cyan(const float fAlpha)	{ *this = COLOR(0.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline void Purple()					{ *this = COLOR(1.0f, 0.0f, 1.0f, 1.0f); }		// ���F/�s����
	inline void Purple(const float fAlpha)	{ *this = COLOR(1.0f, 0.0f, 1.0f, fAlpha); }	// ���F/�����x

	/*
		@brief	�J���[�R�[�h����F/�����x�̐ݒ�
		@param	const std::string&	[in] �J���[�R�[�h������
		@param	const float			[in] �����x
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
		@param	const std::string&	[in] �J���[�R�[�h������
	*/
	inline void Code(const std::string& rCode)
	{
		this->Code(rCode, 1.0f);
	}

	/*
		@brief	�����x���[����
		@return	���茋��
	*/
	inline bool IsAlpha() const
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
		int* pNumDivide,	// �������ʂ̊i�[�z��
		const int nNum,		// �������鐔�l
		const int nMaxDigit	// �������鐔���̌���
	);
	void NormalizeNormal	// �@���̐��K��
	( // ����
		const VECTOR3& rPosLeft,	// ���ʒu
		const VECTOR3& rPosCenter,	// ���S�ʒu
		const VECTOR3& rPosRight,	// �E�ʒu
		VECTOR3& rNor				// �@��
	);
	void ReplaceConsecChar	// ��������̘A�������̒u��
	( // ����
		std::string* pDestStr,		// �u���������s��������
		const char cRepChar,		// ���o���镶��
		const std::string& rRepStr,	// �u�������镶����
		const int nRepStrLength		// �u�������镶����̒��� (�ʏ��string��size)
	);

	VECTOR2 CalcPosParabola		// �o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ʒu�����߂鏈��
	( // ����
		const float fGravity,		// �d��
		const float fMoveX,			// X�ړ���
		const float fDestPosX,		// �ő�X���W
		const float fDestPosY,		// �ő�Y���W
		const float fTime,			// �o�ߎ���
		float* pMaxTime = nullptr,	// �ő�o�ߎ���
		float* pMaxPosY = nullptr	// �ő哞�BY���W
	);
	VECTOR2 CalcMoveParabola	// �o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ړ��ʂ����߂鏈��
	( // ����
		const float fGravity,		// �d��
		const float fMoveX,			// X�ړ���
		const float fDestPosX,		// �ő�X���W
		const float fDestPosY,		// �ő�Y���W
		const float fTime,			// �o�ߎ���
		float* pMaxTime = nullptr,	// �ő�o�ߎ���
		float* pMaxPosY = nullptr	// �ő哞�BY���W
	);

	float RandomRot();					// �����_�������擾
	void NormalizeRot(float& rRot);		// �����̐��K��
	void NormalizeRot(VECTOR3& rRot);	// �O�������̐��K��
	void PathToBaseName(std::string* pPath);		// �p�X�̃x�[�X�l�[���ϊ�
	void StandardizePathPart(std::string* pPath);	// �p�X��؂�̕W����
	std::string SandString(const std::string& rTop, const std::string& rMain, const std::string& rCur);		// ������̍��E�ǉ� (�}���`�o�C�g������)
	std::wstring SandString(const std::wstring& rTop, const std::wstring& rMain, const std::wstring& rCur);	// ������̍��E�ǉ� (���C�h������)
	std::wstring MultiByteToWide(const std::string& rSrcStr);	// �}���`�o�C�g������̃��C�h������ϊ�
	std::string WideToMultiByte(const std::wstring& rSrcStr);	// ���C�h������̃}���`�o�C�g������ϊ�
	void VecToRot(const VECTOR3& rVec, float* pPhi, float* pTheta);			// �x�N�g���̌����ϊ�
	void RotToVec(const float fPhi, const float fTheta, VECTOR3* pVec);		// �����̃x�N�g���ϊ�
	float GetTexWidthFromAspect(const float fHeight, const int nTexIdx);	// �c������A�X�y�N�g����l�����������擾
	float GetTexHeightFromAspect(const float fWidth, const int nTexIdx);	// ��������A�X�y�N�g����l�������c���擾

	// �e���v���[�g�֐�
	template<class T> T* ZeroClear(T* pClear);	// �[���N���A
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
		T* pSortNum,		// �\�[�g�z��
		const int nMaxKeep	// �z��T�C�Y
	);
	template<class T> void Shuffle		// �V���b�t��
	(
		T* pShuffleData,		// �V���b�t���z��
		const int nMaxShuffle	// �z��T�C�Y
	);
}

// �C�[�W���O�֐����
namespace easing
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
	inline COLOR Black()					{ return COLOR(0.0f, 0.0f, 0.0f, 1.0f); }	// ���F/�s����
	inline COLOR Black(const float fAlpha)	{ return COLOR(0.0f, 0.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline COLOR White()					{ return COLOR(1.0f, 1.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline COLOR White(const float fAlpha)	{ return COLOR(1.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline COLOR Red()						{ return COLOR(1.0f, 0.0f, 0.0f, 1.0f); }	// �ԐF/�s����
	inline COLOR Red(const float fAlpha)	{ return COLOR(1.0f, 0.0f, 0.0f, fAlpha); }	// �ԐF/�����x
	inline COLOR Green()					{ return COLOR(0.0f, 1.0f, 0.0f, 1.0f); }	// �ΐF/�s����
	inline COLOR Green(const float fAlpha)	{ return COLOR(0.0f, 1.0f, 0.0f, fAlpha); }	// �ΐF/�����x
	inline COLOR Blue()						{ return COLOR(0.0f, 0.0f, 1.0f, 1.0f); }	// �F/�s����
	inline COLOR Blue(const float fAlpha)	{ return COLOR(0.0f, 0.0f, 1.0f, fAlpha); }	// �F/�����x
	inline COLOR Yellow()					{ return COLOR(1.0f, 1.0f, 0.0f, 1.0f); }	// ���F/�s����
	inline COLOR Yellow(const float fAlpha)	{ return COLOR(1.0f, 1.0f, 0.0f, fAlpha); }	// ���F/�����x
	inline COLOR Cyan()						{ return COLOR(0.0f, 1.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline COLOR Cyan(const float fAlpha)	{ return COLOR(0.0f, 1.0f, 1.0f, fAlpha); }	// ���F/�����x
	inline COLOR Purple()					{ return COLOR(1.0f, 0.0f, 1.0f, 1.0f); }	// ���F/�s����
	inline COLOR Purple(const float fAlpha)	{ return COLOR(1.0f, 0.0f, 1.0f, fAlpha); }	// ���F/�����x

	// �J���[�R�[�h/�s����
	inline COLOR Code(const std::string& rCode, const float fAlpha)
	{
		assert((int)rCode.size() == 6);
		int R = std::stoi(rCode.substr(0, 2), nullptr, 16);
		int G = std::stoi(rCode.substr(2, 2), nullptr, 16);
		int B = std::stoi(rCode.substr(4, 2), nullptr, 16);
		COLOR col = D3DCOLOR_RGBA(R, G, B, (int)(fAlpha * 255.0f));
		return col;
	}

	// �J���[�R�[�h/�����x
	inline COLOR Code(const std::string& rCode)
	{
		return Code(rCode, 1.0f);
	}
}

// �}�e���A���֐����
namespace material
{
	// ���F�}�e���A���擾
	inline D3DXMATERIAL Black()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Black();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL White()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::White();
		return mat;
	}

	// �ԐF�}�e���A���擾
	inline D3DXMATERIAL Red()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Red();
		return mat;
	}

	// �ΐF�}�e���A���擾
	inline D3DXMATERIAL Green()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Green();
		return mat;
	}

	// �F�}�e���A���擾
	inline D3DXMATERIAL Blue()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Blue();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Yellow()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Yellow();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Cyan()
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Cyan();
		return mat;
	}

	// ���F�}�e���A���擾
	inline D3DXMATERIAL Purple()
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
template<class T> T* useful::ZeroClear(T* pClear)
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
	T* pSortNum,		// �\�[�g�z��
	const int nMaxKeep	// �z��T�C�Y
)
{
	T	keepNum;		// �\�[�g�p
	int	nCurrentMaxIdx;	// �ő�l�̃C���f�b�N�X
	for (int nCntKeep = 0; nCntKeep < (nMaxKeep - 1); nCntKeep++)
	{ // ����ւ���l�̑��� -1�񕪌J��Ԃ�

		// ���݂̌J��Ԃ������� (�v�f1�Ƃ���)
		nCurrentMaxIdx = nCntKeep;

		for (int nCntSort = nCntKeep + 1; nCntSort < nMaxKeep; nCntSort++)
		{ // ����ւ���l�̑��� -nCntKeep���J��Ԃ�

			if (pSortNum[nCurrentMaxIdx] < pSortNum[nCntSort])
			{ // �ő�l�ɐݒ肳��Ă���l���A���݂̒l�̂ق����傫���ꍇ

				// ���݂̗v�f�ԍ����ő�l�ɐݒ�
				nCurrentMaxIdx = nCntSort;
			}
		}

		if (nCntKeep != nCurrentMaxIdx)
		{ // �ő�l�̗v�f�ԍ��ɕϓ����������ꍇ

			// �v�f�̓���ւ�
			keepNum						= pSortNum[nCntKeep];
			pSortNum[nCntKeep]			= pSortNum[nCurrentMaxIdx];
			pSortNum[nCurrentMaxIdx]	= keepNum;
		}
	}
}

//============================================================
//	�V���b�t������
//============================================================
template<class T> void useful::Shuffle
(
	T* pShuffleData,		// �V���b�t���z��
	const int nMaxShuffle	// �z��T�C�Y
)
{
	for (int nCntShu = nMaxShuffle - 1; nCntShu > 0; nCntShu--)
	{ // �����̑������J��Ԃ�

		T swap;	// �v�f�̓���ւ��p
		int nRandom = rand() % nCntShu;	// �v�f�����ւ���C���f�b�N�X

		// �v�f�̓���ւ�
		swap					= pShuffleData[nRandom];
		pShuffleData[nRandom]	= pShuffleData[nCntShu];
		pShuffleData[nCntShu]	= swap;
	}
}

#endif	// _USEFUL_H_
