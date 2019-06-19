#pragma once

#include "SimpleMath.h"

class Collision
{
	public:
		Collision();
		~Collision();
};

struct Box
{
	DirectX::SimpleMath::Vector3 center; // ���̒��S
	DirectX::SimpleMath::Vector3 radius; // ���̔��a
};

struct Sphere
{
	DirectX::SimpleMath::Vector3 center; // ���̒��S
	float						 radius; // ���̔��a
};

// �����m�̓����蔻��
bool DetectCollisionBoxToBox(Box boxA, Box boxB);

// �����m�̓����蔻��
bool DetectCollisionSphereToSphere(Sphere sphereA, Sphere sphereB);