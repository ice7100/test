// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Game.cpp
//
// overview		がめソース
//
// date			2019/06/17
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ヘッダファイルの読み込み =================================================
#include "pch.h"
#include "Game.h"

#include "DebugCamera.h"
#include "FollowCamera.h"
#include "GridFloor.h"
#include "Map.h"
#include "Player.h"

extern void ExitGame();

// 名前空間の定義 ===========================================================
using namespace DirectX;

using Microsoft::WRL::ComPtr;

// クラス定数の定義 =========================================================
const DirectX::SimpleMath::Vector3 Game::TARGET_TO_EYE_VEC(0.0f, 20.0f, 20.0f);

Game::Game() noexcept(false)
	: m_debug_camera(nullptr)
	  //m_follow_camera(nullptr)
	, m_grid_floor(nullptr)
{
	m_device_resources = std::make_unique<DX::DeviceResources>();
	m_device_resources->RegisterDeviceNotify(this);
}

Game::~Game()
{
	if (m_debug_camera != nullptr)
	{
		delete m_debug_camera;
		m_debug_camera = nullptr;
	}
//	if (m_follow_camera != nullptr)
//	{
//		delete m_follow_camera;
//		m_follow_camera = nullptr;
//	}
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// デバッグカメラの作成
	m_debug_camera = new DebugCamera();

	// フォローカメラの作成
//	m_follow_camera = new FollowCamera();

	m_device_resources->SetWindow(window, width, height);

	m_device_resources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_device_resources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// コモンステートの作成
	m_state = std::make_unique<CommonStates>(m_device_resources->GetD3DDevice());

	// グリッド床の作成
	m_grid_floor = std::make_unique<GridFloor>(m_device_resources->GetD3DDevice(), m_device_resources->GetD3DDeviceContext(), m_state.get(), 10.0f, 10);

	// エフェクトファクトリの作成
	EffectFactory* factory = new EffectFactory(m_device_resources->GetD3DDevice());

	// プレイヤーの作成
	m_player = std::make_unique<Player>();

	// マップの作成
	m_map = std::make_unique<Map>();

	// =========================================================== //

	// テクスチャの読み込み
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータを読み込む
	m_floormodel = DirectX::Model::CreateFromCMO(
		m_device_resources->GetD3DDevice(),
		L"Resources/Models/floor.cmo",
		*factory
	);

	m_player->Initialize(m_device_resources->GetD3DDevice(), factory);

	delete factory;

	DirectX::SimpleMath::Vector3 eye(Game::TARGET_TO_EYE_VEC);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

//	m_follow_camera->Initialize(eye, target, up);

	m_map->Initialize(m_device_resources->GetD3DDevice(), m_device_resources->GetD3DDeviceContext());

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

	// プレイヤーの更新
	m_player->Update();

//	m_follow_camera->setRefTargetPosition(m_player->GetPlayerPos());
//	m_follow_camera->setRefEyePosition(m_player->GetPlayerPos() + Game::TARGET_TO_EYE_VEC);

	m_debug_camera->update();
//	m_follow_camera->Update();

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

	m_device_resources->PIXBeginEvent(L"Render");
	auto context = m_device_resources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	context;

	DirectX::SimpleMath::Matrix world;

	// モデルの描画
	m_floormodel->Draw(context, *m_state.get(), world, m_debug_camera->getViewMatrix(), m_projection);
//	m_floormodel->Draw(context, *m_state.get(), world, m_follow_camera->getViewMatrix(), m_projection);

	m_player->Render(context, *m_state.get(), m_debug_camera, m_projection);
//	m_player->Render(context, *m_state.get(), m_follow_camera, m_projection);

	m_map->Render(m_debug_camera, m_projection);
//	m_map->Render(m_follow_camera, m_projection);

	// グリッド床の描画
	m_grid_floor->draw(context, m_debug_camera->getViewMatrix(), m_projection);
//	m_grid_floor->draw(context, m_follow_camera->getViewMatrix(), m_projection);

	m_device_resources->PIXEndEvent();

	// Show the new frame.
	m_device_resources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_device_resources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_device_resources->GetD3DDeviceContext();
	auto renderTarget = m_device_resources->GetRenderTargetView();
	auto depthStencil = m_device_resources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_device_resources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_device_resources->PIXEndEvent();
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
	auto r = m_device_resources->GetOutputSize();
	m_device_resources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_device_resources->WindowSizeChanged(width, height))
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
	auto device = m_device_resources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_device_resources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f
	);

}

void Game::setState()
{
	auto context = m_device_resources->GetD3DDeviceContext();
	// カリングしない 
	context->OMSetBlendState(m_state->AlphaBlend(), Colors::Black, 0xFFFFFFFF);
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	m_floormodel.reset();

	m_player->Finalize();
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
