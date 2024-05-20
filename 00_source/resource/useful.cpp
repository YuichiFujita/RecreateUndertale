//============================================================
//
//	�֗��֐����� [useful.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "useful.h"
#include "manager.h"
#include "texture.h"
#include <regex>

//************************************************************
//	�ʏ�֐�
//************************************************************
//	�֗��֐����
//************************************************************
//============================================================
//	���l�̌������Ƃ̕���
//============================================================
//	�X�R�A�\���̍ۂȂǂɎg�p
//============================================================
void useful::DivideDigitNum
(
	int *pNumDivide,	// �������ʂ̊i�[�z��
	const int nNum,		// �������鐔�l
	const int nMaxDigit	// �������鐔���̌���
)
{
	// �ϐ���錾
	int nDigit = 1;	// �e���̐��l�̌v�Z�p

	for (int nCntDigit = 0; nCntDigit < nMaxDigit; nCntDigit++)
	{ // ���̍ő吔���J��Ԃ�

		// ��������Z����
		nDigit *= 10;
	}

	for (int nCntTex = nMaxDigit - 1; nCntTex >= 0; nCntTex--, pNumDivide++)
	{ // �����̍ő傩�猅���̍ŏ��܂ŌJ��Ԃ�

		// �������Ƃ̐��l�����߂�
		*pNumDivide = (nNum % nDigit) / (nDigit / 10);

		// ���Z���Ď��̌����ɍ��킹��
		nDigit /= 10;
	}
}

//============================================================
//	�@���̐��K��
//============================================================
void useful::NormalizeNormal
(
	const D3DXVECTOR3& rPosLeft,	// ���ʒu
	const D3DXVECTOR3& rPosCenter,	// ���S�ʒu
	const D3DXVECTOR3& rPosRight,	// �E�ʒu
	D3DXVECTOR3& rNor				// �@��
)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine[2];	// �Ӄx�N�g��

	// �Ӄx�N�g�������߂�
	vecLine[0] = rPosLeft - rPosCenter;
	vecLine[1] = rPosRight - rPosCenter;

	// �@�����v�Z
	rNor.x = (vecLine[0].y * vecLine[1].z) - (vecLine[0].z * vecLine[1].y);
	rNor.y = (vecLine[0].z * vecLine[1].x) - (vecLine[0].x * vecLine[1].z);
	rNor.z = (vecLine[0].x * vecLine[1].y) - (vecLine[0].y * vecLine[1].x);

	// �@���𐳋K��
	D3DXVec3Normalize(&rNor, &rNor);
}

//============================================================
//	��������̘A�������̒u��
//============================================================
void useful::ReplaceConsecChar
(
	std::string *pDestStr,		// �u���������s��������
	const char cRepChar,		// ���o���镶��
	const std::string& rRepStr,	// �u�������镶����
	const int nRepStrLength		// �u�������镶����̒��� (�ʏ��string��size)

)
{
	int nStartID = 0;	// �������o�̊J�n�C���f�b�N�X
	while (1)
	{ // ��؂蕶�������������ꍇ

		// ���������������̕��������o
		int nFindID = pDestStr->find(cRepChar, nStartID);	// ���o�C���f�b�N�X

		// �����̕��������o����Ȃ������ꍇ���[�v�𔲂���
		if ((size_t)nFindID == std::string::npos) { break; }

		// �u�������̐擪�܂ŕ�������폜����
		std::string sFindStr = *pDestStr;	// �u���������������
		sFindStr.erase(0, nFindID);			// ���o�C���f�b�N�X�܂ŕ�����폜

		int nCntConsec = 0;	// �����A���J�E���^�[
		for (char cChar : sFindStr)
		{ // ������̒������J��Ԃ�

			if (cChar != cRepChar)
			{ // ���o�����ƕʂ̕����ɂȂ����ꍇ

				// �A�����������ׂč폜���A�u���������������
				pDestStr->replace(nFindID, nCntConsec, rRepStr);

				// �������o�̊J�n�C���f�b�N�X��ݒ�
				nStartID = nFindID + nRepStrLength;

				break;
			}

			// �����A���������Z
			nCntConsec++;
		}
	}
}

//============================================================
//	�o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ʒu�����߂鏈��
//============================================================
D3DXVECTOR2 useful::CalcPosParabola
(
	const float fGravity,	// �d��
	const float fMoveX,		// X�ړ���
	const float fDestPosX,	// �ő�X���W
	const float fDestPosY,	// �ő�Y���W
	const float fTime,		// �o�ߎ���
	float *pMaxTime,		// �ő�o�ߎ���
	float *pMaxPosY			// �ő哞�BY���W
)
{
	const float fMaxTime	= fDestPosX / fMoveX;	// �ő�o�ߎ���
	const float fHalfTime	= fMaxTime * 0.5f;		// �����̍ő�o�ߎ���
	const float fMoveY		= -0.5f * fGravity * fMaxTime;	// Y�ړ���
	const float fMaxPosY	= 0.5f * fGravity * (fHalfTime * fHalfTime) + fMoveY * fHalfTime;	// �ő哞�BY���W

	if (pMaxTime != nullptr)
	{
		// �ő�o�ߎ��Ԃ�ۑ�
		*pMaxTime = fMaxTime;
	}
	if (pMaxPosY != nullptr)
	{
		// �ő哞�BY���W��ۑ�
		*pMaxPosY = fMaxPosY;
	}

	// ���ݎ��Ԃ̈ʒu�����߂�
	D3DXVECTOR2 posTime = VEC2_ZERO;
	posTime.x = fMoveX * fTime;
	posTime.y = (0.5f * fGravity * (fTime * fTime) + fMoveY * fTime) * (fDestPosY / fMaxPosY);

	// ���ݎ��Ԃ̈ʒu��Ԃ�
	return posTime;
}

//============================================================
//	�o�ߎ��ԁEX�ړ��ʁE�d�͂���������̈ړ��ʂ����߂鏈��
//============================================================
D3DXVECTOR2 useful::CalcMoveParabola
(
	const float fGravity,	// �d��
	const float fMoveX,		// X�ړ���
	const float fDestPosX,	// �ő�X���W
	const float fDestPosY,	// �ő�Y���W
	const float fTime,		// �o�ߎ���
	float *pMaxTime,		// �ő�o�ߎ���
	float *pMaxPosY			// �ő哞�BY���W
)
{
	const float fMaxTime	= fDestPosX / fMoveX;	// �ő�o�ߎ���
	const float fHalfTime	= fMaxTime * 0.5f;		// �����̍ő�o�ߎ���
	const float fMoveY		= -0.5f * fGravity * fMaxTime;	// Y�ړ���
	const float fMaxPosY	= 0.5f * fGravity * (fHalfTime * fHalfTime) + fMoveY * fHalfTime;	// �ő哞�BY���W

	if (pMaxTime != nullptr)
	{
		// �ő�o�ߎ��Ԃ�ۑ�
		*pMaxTime = fMaxTime;
	}
	if (pMaxPosY != nullptr)
	{
		// �ő哞�BY���W��ۑ�
		*pMaxPosY = fMaxPosY;
	}

	// ���ݎ��Ԃ̈ړ��ʂ����߂�
	D3DXVECTOR2 moveTime = VEC2_ZERO;
	moveTime.x = fMoveX;
	moveTime.y = (fGravity * fTime + fMoveY) * (fDestPosY / fMaxPosY);

	// ���ݎ��Ԃ̈ړ��ʂ�Ԃ�
	return moveTime;
}

//============================================================
//	�����̐��K��
//============================================================
void useful::NormalizeRot(float& rRot)
{
	if (rRot > D3DX_PI)
	{ // ������ 3.14 �𒴂����ꍇ

		// �����̐��K��
		rRot -= D3DX_PI * 2.0f;
	}
	else if (rRot < -D3DX_PI)
	{ // ������ -3.14 �𒴂����ꍇ

		// �����̐��K��
		rRot += D3DX_PI * 2.0f;
	}
}

//============================================================
//	�O�������̐��K��
//============================================================
void useful::NormalizeRot(D3DXVECTOR3& rRot)
{
	// �S�Ă̌����𐳋K��
	NormalizeRot(rRot.x);
	NormalizeRot(rRot.y);
	NormalizeRot(rRot.z);
}

//============================================================
//	�p�X�̃x�[�X�l�[���ϊ�
//============================================================
void useful::PathToBaseName(std::string *pPath)
{
	std::filesystem::path fsPath(*pPath);	// �p�X

	// �p�X����x�[�X�l�[�����擾
	*pPath = fsPath.stem().string();
}

//============================================================
//	�p�X��؂�̕W����
//============================================================
void useful::StandardizePathPart(std::string *pPath)
{
	// �X���b�V����u��
	ReplaceConsecChar
	( // ����
		pPath,	// �u���������s��������
		'/',	// ���o���镶��
		"\\",	// �u�������镶����
		1		// �u�������镶����̒��� (�ʏ핶���ƈႢ\�͓�ňꕶ���ƂȂ�)
	);

	// �o�b�N�X���b�V����u��
	ReplaceConsecChar
	( // ����
		pPath,	// �u���������s��������
		'\\',	// ���o���镶��
		"\\",	// �u�������镶����
		1		// �u�������镶����̒��� (�ʏ핶���ƈႢ\�͓�ňꕶ���ƂȂ�)
	);
}

//============================================================
//	�x�N�g���̌����ϊ�
//============================================================
void useful::VecToRot(const D3DXVECTOR3& rVec, float *pPhi, float *pTheta)
{
	// ���ʊp�̌v�Z
	*pPhi = atan2f(rVec.y, rVec.x);

	// �p�̌v�Z
	*pTheta = atan2f(sqrtf((rVec.x * rVec.x) + (rVec.y * rVec.y)), rVec.z);
}

//============================================================
//	�����̃x�N�g���ϊ�
//============================================================
void useful::RotToVec(const float fPhi, const float fTheta, D3DXVECTOR3 *pVec)
{
	// �x�N�g���̌v�Z
	pVec->x = sinf(fTheta) * cosf(fPhi);
	pVec->y = sinf(fTheta) * sinf(fPhi);
	pVec->z = cosf(fTheta);
}

//============================================================
//	�c������e�N�X�`���̃A�X�y�N�g����l�����������̎擾����
//============================================================
float useful::GetTexWidthFromAspect(const float fHeight, const int nTexID)
{
	// �e�N�X�`���A�X�y�N�g����擾
	D3DXVECTOR2 aspect = GET_MANAGER->GetTexture()->GetInfo(nTexID).aspect;

	// �A�X�y�N�g�䂩��v�Z����������Ԃ�
	return fHeight * aspect.x;
}

//============================================================
//	��������e�N�X�`���̃A�X�y�N�g����l�������c���̎擾����
//============================================================
float useful::GetTexHeightFromAspect(const float fWidth, const int nTexID)
{
	// �e�N�X�`���A�X�y�N�g����擾
	D3DXVECTOR2 aspect = GET_MANAGER->GetTexture()->GetInfo(nTexID).aspect;

	// �A�X�y�N�g�䂩��v�Z�����c����Ԃ�
	return fWidth * aspect.y;
}

//============================================================
//	�����_�������擾
//============================================================
float useful::RandomRot(void)
{
	// �����_��������Ԃ�
	return (float)(rand() % 629 - 314) * 0.01f;
}

//============================================================
//	�}�g���b�N�X�̈ʒu�擾
//============================================================
D3DXVECTOR3 useful::GetMatrixPosition(const D3DXMATRIX&rMtx)
{
	// �}�g���b�N�X�̈ʒu��Ԃ�
	return D3DXVECTOR3(rMtx._41, rMtx._42, rMtx._43);
}

//============================================================
//	�}�g���b�N�X�̌����擾
//============================================================
D3DXVECTOR3 useful::GetMatrixRotation(const D3DXMATRIX& rMtx)
{
	float fYaw, fPitch, fRoll;	// �v�Z���ʂ̕ۑ��p
	float fCosPitch;			// �����v�Z�p

	// �}�g���b�N�X����Pitch�����߂�
	fPitch = asinf(-rMtx._32);

	// �}�g���b�N�X����Yaw�ERoll�����߂�
	fCosPitch = cosf(fPitch);
	if (fabs(fCosPitch) > 0.0001f)
	{ // Pitch�̊p�x���v�Z�ɖ��Ȃ��ꍇ

		fYaw  = atan2f(rMtx._31 / fCosPitch, rMtx._33 / fCosPitch);
		fRoll = atan2f(rMtx._12 / fCosPitch, rMtx._22 / fCosPitch);
	}
	else
	{ // Pitch��90�x�܂���-90�x�̏ꍇ

		fYaw  = 0.0f;	// ���m�Ȓl�����Ȃ��̂�0.0f�Ƃ���
		fRoll = atan2f(rMtx._21, rMtx._11);
	}

	// �}�g���b�N�X�̌�����Ԃ�
	return D3DXVECTOR3(fPitch, fYaw, fRoll);
}

//============================================================
//	�}�g���b�N�X�̊g�嗦�擾
//============================================================
D3DXVECTOR3 useful::GetMatrixScaling(const D3DXMATRIX& rMtx)
{
	D3DXVECTOR3 scale;	// �v�Z���ʂ̕ۑ��p

	// �}�g���b�N�X����g�嗦�����߂�
	scale.x = sqrtf(rMtx._11 * rMtx._11 + rMtx._12 * rMtx._12 + rMtx._13 * rMtx._13);
	scale.y = sqrtf(rMtx._21 * rMtx._21 + rMtx._22 * rMtx._22 + rMtx._23 * rMtx._23);
	scale.z = sqrtf(rMtx._31 * rMtx._31 + rMtx._32 * rMtx._32 + rMtx._33 * rMtx._33);

	// �}�g���b�N�X�̊g�嗦��Ԃ�
	return scale;
}

//************************************************************
//	�}�e���A�����
//************************************************************
//============================================================
//	���F�}�e���A���擾
//============================================================
D3DXMATERIAL material::White(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U���𔒐F�ɂ���
	mat.MatD3D.Diffuse = XCOL_WHITE;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�ԐF�}�e���A���擾
//============================================================
D3DXMATERIAL material::Red(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U����ԐF�ɂ���
	mat.MatD3D.Diffuse = XCOL_RED;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�ΐF�}�e���A���擾
//============================================================
D3DXMATERIAL material::Green(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U����ΐF�ɂ���
	mat.MatD3D.Diffuse = XCOL_GREEN;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�F�}�e���A���擾
//============================================================
D3DXMATERIAL material::Blue(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U����F�ɂ���
	mat.MatD3D.Diffuse = XCOL_BLUE;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	���F�}�e���A���擾
//============================================================
D3DXMATERIAL material::Yellow(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U�������F�ɂ���
	mat.MatD3D.Diffuse = XCOL_YELLOW;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	���F�}�e���A���擾
//============================================================
D3DXMATERIAL material::Cyan(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U���𐅐F�ɂ���
	mat.MatD3D.Diffuse = XCOL_CYAN;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�_���[�W�ԐF�}�e���A���擾
//============================================================
D3DXMATERIAL material::DamageRed(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U����ݒ�
	mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.85f);

	// �}�e���A���̕��ˌ���ݒ�
	mat.MatD3D.Emissive = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�����ΐF�}�e���A���擾
//============================================================
D3DXMATERIAL material::GlowGreen(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U����ΐF�ɂ���
	mat.MatD3D.Diffuse = XCOL_GREEN;

	// �}�e���A���̕��ˌ���ΐF�ɂ���
	mat.MatD3D.Emissive = XCOL_GREEN;

	// �}�e���A����Ԃ�
	return mat;
}

//============================================================
//	�������F�}�e���A���擾
//============================================================
D3DXMATERIAL material::GlowCyan(void)
{
	// �ϐ���錾
	D3DXMATERIAL mat;	// �ݒ�p�}�e���A��

	// �}�e���A���̃������N���A
	ZeroMemory(&mat, sizeof(mat));

	// �}�e���A���̊g�U���𐅐F�ɂ���
	mat.MatD3D.Diffuse = XCOL_CYAN;

	// �}�e���A���̕��ˌ��𐅐F�ɂ���
	mat.MatD3D.Emissive = XCOL_CYAN;

	// �}�e���A����Ԃ�
	return mat;
}

//************************************************************
//	2�������W�̍\���̃����o�֐�
//************************************************************
//============================================================
//	���Z�q�̃I�[�o�[���[�h (��r���Z�q ==)
//============================================================
bool POSGRID2::operator==(const POSGRID2& grid) const
{
	if (grid.x == x && grid.y == y)
	{ // ������W�����ׂē����ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (��r���Z�q !=)
//============================================================
bool POSGRID2::operator!=(const POSGRID2& grid) const
{
	if (grid.x != x || grid.y != y)
	{ // ������W����ł��Ⴄ�ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q +)
//============================================================
POSGRID2 POSGRID2::operator+(const POSGRID2& grid) const
{
	POSGRID2 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x += grid.x;
	tempGrid.y += grid.y;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q -)
//============================================================
POSGRID2 POSGRID2::operator-(const POSGRID2& grid) const
{
	POSGRID2 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x -= grid.x;
	tempGrid.y -= grid.y;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (��Z���Z�q *)
//============================================================
POSGRID2 POSGRID2::operator*(const int nVal) const
{
	POSGRID2 tempGrid = *this;	// ��Z���ʂ̑���p

	// �����̐������W����Z
	tempGrid.x *= nVal;
	tempGrid.y *= nVal;

	// ��Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q /)
//============================================================
POSGRID2 POSGRID2::operator/(const int nVal) const
{
	POSGRID2 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x /= nVal;
	tempGrid.y /= nVal;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}

//************************************************************
//	3�������W�̍\���̃����o�֐�
//************************************************************
//============================================================
//	���Z�q�̃I�[�o�[���[�h (��r���Z�q ==)
//============================================================
bool POSGRID3::operator==(const POSGRID3& grid) const
{
	if (grid.x == x && grid.y == y && grid.z == z)
	{ // ������W�����ׂē����ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (��r���Z�q !=)
//============================================================
bool POSGRID3::operator!=(const POSGRID3& grid) const
{
	if (grid.x != x || grid.y != y || grid.z != z)
	{ // ������W����ł��Ⴄ�ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q +)
//============================================================
POSGRID3 POSGRID3::operator+(const POSGRID3& grid) const
{
	POSGRID3 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x += grid.x;
	tempGrid.y += grid.y;
	tempGrid.z += grid.z;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q -)
//============================================================
POSGRID3 POSGRID3::operator-(const POSGRID3& grid) const
{
	POSGRID3 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x -= grid.x;
	tempGrid.y -= grid.y;
	tempGrid.z -= grid.z;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (��Z���Z�q *)
//============================================================
POSGRID3 POSGRID3::operator*(const int nVal) const
{
	POSGRID3 tempGrid = *this;	// ��Z���ʂ̑���p

	// �����̐������W����Z
	tempGrid.x *= nVal;
	tempGrid.y *= nVal;
	tempGrid.z *= nVal;

	// ��Z���ʂ�Ԃ�
	return tempGrid;
}

//============================================================
//	���Z�q�̃I�[�o�[���[�h (���Z���Z�q /)
//============================================================
POSGRID3 POSGRID3::operator/(const int nVal) const
{
	POSGRID3 tempGrid = *this;	// ���Z���ʂ̑���p

	// �����̐������W�����Z
	tempGrid.x /= nVal;
	tempGrid.y /= nVal;
	tempGrid.z /= nVal;

	// ���Z���ʂ�Ԃ�
	return tempGrid;
}
