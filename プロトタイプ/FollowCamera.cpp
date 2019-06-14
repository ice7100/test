#include "pch.h"
#include "FollowCamera.h"


FollowCamera::FollowCamera()
{

}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Initialize(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	m_eye = eye;
	m_target = target;
	m_up = up;
	
}

void FollowCamera::Update()
{
	m_eye += (m_refeye - m_eye) * 0.05f;
	m_target += (m_reftarget - m_target) * 0.05f;
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}
