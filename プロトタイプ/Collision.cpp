// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Collsion.cpp
//
// overview		�����蔻��p�̃\�[�X
//
// date			2019/06/19
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include "pch.h"
#include "Collision.h"

// �����o�֐��̒�` =========================================================
// -------------------------------------------------------------------------
// overview		�R���X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Collision::Collision()
{

}

// -------------------------------------------------------------------------
// overview		�f�X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Collision::~Collision()
{

}

// -------------------------------------------------------------------------
// overview		�����m�̓����蔻��
//
// argument		boxA 1�ڂ�box�̒l
// argument		boxB 2�ڂ�box�̒l
//
// return		�������Ă�����true��Ԃ�
// -------------------------------------------------------------------------
bool DetectCollisionBoxToBox(Box boxA, Box boxB)
{
	if (fabs(boxA.center.x - boxB.center.x) > (boxA.radius.x + boxB.radius.x)) return false;
	if (fabs(boxA.center.y - boxB.center.y) > (boxA.radius.y + boxB.radius.y)) return false;
	if (fabs(boxA.center.z - boxB.center.z) > (boxA.radius.z + boxB.radius.z)) return false;

	return true;
}

// -------------------------------------------------------------------------
// overview		�����m�̓����蔻��
//
// argument		sphereA 1�ڂ�sphere�̒l
// argument		sphereB 2�ڂ�sphere�̒l
//
// return		�搶�ɕ���
// -------------------------------------------------------------------------
bool DetectCollisionSphereToSphere(Sphere sphereA, Sphere sphereB)
{
	DirectX::SimpleMath::Vector3 distance1 = sphereA.center - sphereB.center;
	float distance2 = distance1.Dot(distance1);
	float radiusSum = sphereA.radius + sphereA.radius;
	return distance2 <= radiusSum * radiusSum;
}