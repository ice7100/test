#pragma once

#include "SimpleMath.h"

class FollowCamera
{

public:
	FollowCamera();
	~FollowCamera();

	void Initialize(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up);
	void Update();

	// �f�o�b�O�J�����̈ʒu�ݒ�
	void setEyePosition(DirectX::SimpleMath::Vector3 eye)
	{
		m_eye = eye;
	}

	// �f�o�b�O�J�����̈ʒu�ݒ�
	void setRefEyePosition(DirectX::SimpleMath::Vector3 eye)
	{
		m_refeye = eye;
	}

	// �f�o�b�O�J�����̒����_�ݒ�
	void setTargetPosition(DirectX::SimpleMath::Vector3 target)
	{
		m_target = target;
	}

	// �f�o�b�O�J�����̒����_�ݒ�
	void setRefTargetPosition(DirectX::SimpleMath::Vector3 target)
	{
		m_reftarget = target;
	}

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_view;
	}

	// �f�o�b�O�J�����̈ʒu�擾
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}

	// �f�o�b�O�J�����̒����_�擾
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}

private:

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	DirectX::SimpleMath::Vector3 m_refeye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_reftarget;

	DirectX::SimpleMath::Vector3 m_up;
};

