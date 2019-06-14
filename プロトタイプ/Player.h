// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.h
//
// overview		マップデータを用意するヘッダ
//
// date			2019/06/12
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// マクロの定義 =============================================================
#ifndef PLAYER
#define PLAYER

// ヘッダファイルの読み込み =================================================
#include <memory>

#include "Model.h"
#include "SimpleMath.h"
#include "Effects.h"
#include "Keyboard.h"
#include "DebugCamera.h"
#include "FollowCamera.h"
#include "CommonStates.h"

// <プレイヤークラス> ------------------------------------------------------
class Player
{
	private:
	// クラス定数の宣言

		// プレイヤーの速度
		static const float PLAYER_VEL;

	// メンバ変数の宣言

		DirectX::Keyboard::KeyboardStateTracker m_key_tracker;

		// プレイヤーモデル
		std::unique_ptr<DirectX::Model>		m_player_model;

		// マトリックス
		DirectX::SimpleMath::Matrix			m_player_matrix;

		// プレイヤーpos
		DirectX::SimpleMath::Vector3		m_player_pos;

		// プレイヤーvel
		DirectX::SimpleMath::Vector3		m_player_vel;

	// メンバ関数の宣言
	public:
		// コンストラクタ
		Player();
		// デストラクタ
		~Player();

		// 操作
		void Initialize(ID3D11Device1* device, DirectX::EffectFactory* factory);
		void Update();
		void Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, DebugCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, FollowCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Finalize();

		// プレイヤーposのゲッター
		DirectX::SimpleMath::Vector3 GetPlayerPos()
		{
			return m_player_pos;
		}
};
#endif	// PLAYER