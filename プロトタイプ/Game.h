//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"
#include "SimpleMath.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Model.h"
#include "Player.h"

class DebugCamera;
//class FollowCamera;
class GridFloor;
class Map;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:
	// �J�����̒萔
	static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

	// �v���C���[�̒萔
//	static const float PLAYER_VEL;

	Game() noexcept(false);
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

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix				m_projection;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_pMouse;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>		m_pKeyboard;

	// �f�o�b�O�J����
//	DebugCamera*							m_debug_camera;

	// �t�H���[�J����
	FollowCamera*							m_follow_camera;

	// �O���b�h��
	std::unique_ptr<GridFloor>				m_grid_floor;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	// ���f��
//	std::unique_ptr<DirectX::Model>			m_Skydoommodel;
	std::unique_ptr<DirectX::Model>			m_Floormodel;

	std::unique_ptr<Player>					m_player;

	std::unique_ptr<Map>					m_map;

};