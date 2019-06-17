// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Game.h
//
// overview		���߃w�b�_
//
// date			2019/06/17
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ���d�C���N���[�h�̖h�~ ===================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"
#include "SimpleMath.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Model.h"

// �N���X�̑O���錾 =========================================================
class DebugCamera;
class FollowCamera;
class GridFloor;
class Map;
class Player;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
// <�Q�[���N���X> ----------------------------------------------------------
class Game : public DX::IDeviceNotify
{
	private:
		// �N���X�萔�̐錾

		// �J�����̒萔
		static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

		// �����o�ϐ�

		// Device resources.
		std::unique_ptr<DX::DeviceResources>    m_device_resources;

		// Rendering loop timer.
		DX::StepTimer                           m_timer;

		// �ˉe�s��
		DirectX::SimpleMath::Matrix				m_projection;

		// �}�E�X
		std::unique_ptr<DirectX::Mouse>			m_mouse;

		// �L�[�{�[�h
		std::unique_ptr<DirectX::Keyboard>		m_keyboard;

		// �f�o�b�O�J����
		DebugCamera*							m_debug_camera;

		// �t�H���[�J����
		FollowCamera*							m_follow_camera;

		// �O���b�h��
		std::unique_ptr<GridFloor>				m_grid_floor;

		// �R�����X�e�[�g
		std::unique_ptr<DirectX::CommonStates>	m_state;

		// ���f��
		std::unique_ptr<DirectX::Model>			m_floormodel;

		// �v���C���[
		std::unique_ptr<Player>					m_player;

		// �}�b�v
		std::unique_ptr<Map>					m_map;

	public:
		// �R���X�g���N�^
		Game() noexcept(false);
		// �f�X�g���N�^
		~Game();
	
		// Initialization and management
		void Initialize(HWND window, int width, int height);
	
		// Basic game loop
		void Tick();
	
		// IDeviceNotify
		virtual void OnDeviceLost() override;
		virtual void OnDeviceRestored() override;
	
		// Messages
		void OnActivated();
		void OnDeactivated();
		void OnSuspending();
		void OnResuming();
		void OnWindowMoved();
		void OnWindowSizeChanged(int width, int height);
	
		// Properties
		void GetDefaultSize(int& width, int& height) const;
	
	private:
	
		void Update(DX::StepTimer const& timer);
		void Render();
	
		void Clear();
	
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
	
		void setState();
};