// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.h
//
// overview		�}�b�v�f�[�^��p�ӂ���w�b�_
//
// date			2019/06/12
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ���d�C���N���[�h�̖h�~ ===================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include <memory>

#include "Model.h"
#include "SimpleMath.h"
#include "Effects.h"
#include "Keyboard.h"
#include "CommonStates.h"
#include "Collision.h"

// �N���X�̑O���錾 =========================================================
class DebugCamera;
class FollowCamera;
class TiledMap;

// <�v���C���[�N���X> ------------------------------------------------------
class Player
{
	private:
	// �N���X�萔�̐錾

		// �v���C���[�̑��x
		static const float PLAYER_VEL;
		static const float RADIUS;

	// �����o�ϐ��̐錾

		DirectX::Keyboard::KeyboardStateTracker m_key_tracker;

		// �v���C���[���f��
		std::unique_ptr<DirectX::Model>			m_player_model;

		// �}�g���b�N�X
		DirectX::SimpleMath::Matrix				m_player_matrix;

		// �v���C���[pos
		DirectX::SimpleMath::Vector3			m_player_pos;

		// �v���C���[vel
		DirectX::SimpleMath::Vector3			m_player_vel;

		// BOX
		Box										m_player_box;

	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Player();
		// �f�X�g���N�^
		~Player();

		// ����
		void Initialize(ID3D11Device1* device, DirectX::EffectFactory* factory);
		void Update();
		void Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, DebugCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, FollowCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Finalize();

		// �v���C���[pos�̃Q�b�^�[
		DirectX::SimpleMath::Vector3 GetPlayerPos()
		{
			return m_player_pos;
		}

		// Box�̃Q�b�^�[
		Box GetBox()
		{
			return m_player_box;
		}
};
