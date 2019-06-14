//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "DebugCamera.h"
//#include "FollowCamera.h"
#include "GridFloor.h"
#include "Map.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

const DirectX::SimpleMath::Vector3 Game::TARGET_TO_EYE_VEC(0.0f, 20.0f, 20.0f);

//const float Game::PLAYER_VEL = 0.3f;

Game::Game() noexcept(false)
	: //m_debug_camera(nullptr)
	  m_follow_camera(nullptr)
	, m_grid_floor(nullptr)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
//	if (m_debug_camera != nullptr)
//	{
//		delete m_debug_camera;
//		m_debug_camera = nullptr;
//	}
	if (m_follow_camera != nullptr)
	{
		delete m_follow_camera;
		m_follow_camera = nullptr;
	}
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// �}�E�X�̍쐬
	m_pMouse = std::make_unique<Mouse>();
	m_pMouse->SetWindow(window);

	// �L�[�{�[�h�̍쐬
	m_pKeyboard = std::make_unique<Keyboard>();

	// �f�o�b�O�J�����̍쐬
//	m_debug_camera = new DebugCamera();

	// �t�H���[�J�����̍쐬
	m_follow_camera = new FollowCamera();

	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// �R�����X�e�[�g�̍쐬
	m_pState = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());

	// �O���b�h���̍쐬
	m_grid_floor = std::make_unique<GridFloor>(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(), m_pState.get(), 10.0f, 10);

	// �G�t�F�N�g�t�@�N�g���̍쐬
	EffectFactory* factory = new EffectFactory(m_deviceResources->GetD3DDevice());

	// �v���C���[�̍쐬
	m_player = std::make_unique<Player>();

	// �}�b�v�̍쐬
	m_map = std::make_unique<Map>();

	// =========================================================== //

	// �e�N�X�`���̓ǂݍ���
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^��ǂݍ���
	m_Floormodel = DirectX::Model::CreateFromCMO(
		m_deviceResources->GetD3DDevice(),
		L"Resources/Models/floor.cmo",
		*factory
	);

	m_player->Initialize(m_deviceResources->GetD3DDevice(), factory);

	delete factory;

	DirectX::SimpleMath::Vector3 eye(Game::TARGET_TO_EYE_VEC);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_follow_camera->Initialize(eye, target, up);

	m_map->Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	// �v���C���[�̍X�V
	m_player->Update();

	m_follow_camera->setRefTargetPosition(m_player->GetPlayerPos());
	m_follow_camera->setRefEyePosition(m_player->GetPlayerPos() + Game::TARGET_TO_EYE_VEC);

//	m_debug_camera->update();
	m_follow_camera->Update();

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	context;

	DirectX::SimpleMath::Matrix world;

	// ���f���̕`��
//	m_Floormodel->Draw(context, *m_pState.get(), world, m_debug_camera->getViewMatrix(), m_projection);	// ��
	m_Floormodel->Draw(context, *m_pState.get(), world, m_follow_camera->getViewMatrix(), m_projection);	// ��

//	m_player->Render(context, *m_pState.get(), m_debug_camera, m_projection);
	m_player->Render(context, *m_pState.get(), m_follow_camera, m_projection);

//	m_map->Render(m_debug_camera, m_projection);
	m_map->Render(m_follow_camera, m_projection);

	// �O���b�h���̕`��
//	m_grid_floor->draw(context, m_debug_camera->getViewMatrix(), m_projection);
	m_grid_floor->draw(context, m_follow_camera->getViewMatrix(), m_projection);

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 800;
	height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f
	);

}

void Game::setState()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	// �J�����O���Ȃ� 
	context->OMSetBlendState(m_pState->AlphaBlend(), Colors::Black, 0xFFFFFFFF);
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	m_Floormodel.reset();

	m_player->Finalize();
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
