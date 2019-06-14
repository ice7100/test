#pragma once

#include "SimpleMath.h"

class FollowCamera
{

public:
	FollowCamera();
	~FollowCamera();

	void Initialize(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up);
	void Update();

	// デバッグカメラの位置設定
	void setEyePosition(DirectX::SimpleMath::Vector3 eye)
	{
		m_eye = eye;
	}

	// デバッグカメラの位置設定
	void setRefEyePosition(DirectX::SimpleMath::Vector3 eye)
	{
		m_refeye = eye;
	}

	// デバッグカメラの注視点設定
	void setTargetPosition(DirectX::SimpleMath::Vector3 target)
	{
		m_target = target;
	}

	// デバッグカメラの注視点設定
	void setRefTargetPosition(DirectX::SimpleMath::Vector3 target)
	{
		m_reftarget = target;
	}

	// ビュー行列取得
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	// デバッグカメラの位置取得
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}

	// デバッグカメラの注視点取得
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

private:

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	DirectX::SimpleMath::Vector3 m_refeye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_reftarget;

	DirectX::SimpleMath::Vector3 m_up;
};

