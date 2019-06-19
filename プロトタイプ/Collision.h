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
	DirectX::SimpleMath::Vector3 center; // ” ‚Ì’†S
	DirectX::SimpleMath::Vector3 radius; // ” ‚Ì”¼Œa
};

struct Sphere
{
	DirectX::SimpleMath::Vector3 center; // ‹…‚Ì’†S
	float						 radius; // ‹…‚Ì”¼Œa
};

// ” “¯m‚Ì“–‚½‚è”»’è
bool DetectCollisionBoxToBox(Box boxA, Box boxB);

// ‹…“¯m‚Ì“–‚½‚è”»’è
bool DetectCollisionSphereToSphere(Sphere sphereA, Sphere sphereB);