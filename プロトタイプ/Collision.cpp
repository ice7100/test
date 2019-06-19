// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Collsion.cpp
//
// overview		当たり判定用のソース
//
// date			2019/06/19
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ヘッダファイルの読み込み =================================================
#include "pch.h"
#include "Collision.h"

// メンバ関数の定義 =========================================================
// -------------------------------------------------------------------------
// overview		コンストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Collision::Collision()
{

}

// -------------------------------------------------------------------------
// overview		デストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Collision::~Collision()
{

}

// -------------------------------------------------------------------------
// overview		箱同士の当たり判定
//
// argument		boxA 1つ目のboxの値
// argument		boxB 2つ目のboxの値
//
// return		当たっていたらtrueを返す
// -------------------------------------------------------------------------
bool DetectCollisionBoxToBox(Box boxA, Box boxB)
{
	if (fabs(boxA.center.x - boxB.center.x) > (boxA.radius.x + boxB.radius.x)) return false;
	if (fabs(boxA.center.y - boxB.center.y) > (boxA.radius.y + boxB.radius.y)) return false;
	if (fabs(boxA.center.z - boxB.center.z) > (boxA.radius.z + boxB.radius.z)) return false;

	return true;
}

// -------------------------------------------------------------------------
// overview		球同士の当たり判定
//
// argument		sphereA 1つ目のsphereの値
// argument		sphereB 2つ目のsphereの値
//
// return		先生に聞く
// -------------------------------------------------------------------------
bool DetectCollisionSphereToSphere(Sphere sphereA, Sphere sphereB)
{
	DirectX::SimpleMath::Vector3 distance1 = sphereA.center - sphereB.center;
	float distance2 = distance1.Dot(distance1);
	float radiusSum = sphereA.radius + sphereA.radius;
	return distance2 <= radiusSum * radiusSum;
}