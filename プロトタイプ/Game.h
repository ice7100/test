// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Game.h
//
// overview		がめヘッダ
//
// date			2019/06/17
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// 多重インクルードの防止 ===================================================
#pragma once

// ヘッダファイルの読み込み =================================================
#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"
#include "SimpleMath.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Model.h"

// クラスの前方宣言 =========================================================
class DebugCamera;
class FollowCamera;
class GridFloor;
class Map;
class Player;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
// <ゲームクラス> ----------------------------------------------------------
class Game : public DX::IDeviceNotify
{
	private:
		// クラス定数の宣言

		// カメラの定数
		static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

		// メンバ変数

		// Device resources.
		std::unique_ptr<DX::DeviceResources>    m_device_resources;

		// Rendering loop timer.
		DX::StepTimer                           m_timer;

		// 射影行列
		DirectX::SimpleMath::Matrix				m_projection;

		// マウス
		std::unique_ptr<DirectX::Mouse>			m_mouse;

		// キーボード
		std::unique_ptr<DirectX::Keyboard>		m_keyboard;

		// デバッグカメラ
		DebugCamera*							m_debug_camera;

		// フォローカメラ
		FollowCamera*							m_follow_camera;

		// グリッド床
		std::unique_ptr<GridFloor>				m_grid_floor;

		// コモンステート
		std::unique_ptr<DirectX::CommonStates>	m_state;

		// モデル
		std::unique_ptr<DirectX::Model>			m_floormodel;

		// プレイヤー
		std::unique_ptr<Player>					m_player;

		// マップ
		std::unique_ptr<Map>					m_map;

	public:
		// コンストラクタ
		Game() noexcept(false);
		// デストラクタ
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