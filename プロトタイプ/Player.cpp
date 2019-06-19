// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Player.cpp
//
// overview		プレイヤーに関してのソース
//
// date			2019/06/14
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ヘッダファイルの読み込み =================================================
#include "pch.h"
#include "Player.h"
#include "DebugCamera.h"
#include "FollowCamera.h"

// 名前空間の定義 ===========================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// クラス定数の定義 =========================================================
const float Player::PLAYER_VEL = 0.3f;
const float Player::RADIUS = 0.98f;

// メンバ関数の定義 =========================================================
// -------------------------------------------------------------------------
// overview		コンストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Player::Player()
{

}

// -------------------------------------------------------------------------
// overview		デストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Player::~Player()
{

}

// -------------------------------------------------------------------------
// overview		プレイヤーの初期化処理
//
// argument		device デバイスリソーシーズのデバイス
// argument		factory エフェクトファクトリー
//
// return		なし
// -------------------------------------------------------------------------
void Player::Initialize(ID3D11Device1* device, EffectFactory* factory)
{
	// ファイルを指定してモデルデータを読み込む
	m_player_model = DirectX::Model::CreateFromCMO(
		device, L"Resources/Models/Player.cmo",
		*factory);

	// プレイヤーposの初期化
	m_player_pos = Vector3();

	// プレイヤーvelの初期化
	m_player_vel = Vector3(PLAYER_VEL, 0.0f, PLAYER_VEL);

	m_player_box.center = m_player_pos;
	m_player_box.radius = DirectX::SimpleMath::Vector3(RADIUS, RADIUS, RADIUS);
}

// -------------------------------------------------------------------------
// overview		プレイヤー更新処理
//
// argument		なし
//
// return		なし
// -------------------------------------------------------------------------
void Player::Update()
{
	DirectX::Keyboard::State keystate = DirectX::Keyboard::Get().GetState();
	m_key_tracker.Update(keystate);

	if (keystate.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(VK_LEFT)))
	{
		m_player_pos.x = m_player_pos.x - m_player_vel.x;
	}
	if (keystate.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(VK_RIGHT)))
	{
		m_player_pos.x = m_player_pos.x + m_player_vel.x;
	}
	if (keystate.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(VK_UP)))
	{
		m_player_pos.z = m_player_pos.z - m_player_vel.z;
	}
	if (keystate.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(VK_DOWN)))
	{
		m_player_pos.z = m_player_pos.z + m_player_vel.z;
	}

	m_player_matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_player_pos);

	m_player_box.center = m_player_pos;
}

// -------------------------------------------------------------------------
// overview		プレイヤーの描画処理
//
// argument		context デバイスリソーシーズのコンテクスト
// argument		state コモンステート
// argument		camera デバッグカメラ
// argument		projection マトリックス
//
// return		なし
// -------------------------------------------------------------------------
void Player::Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, DebugCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	m_player_model->Draw(context, state, m_player_matrix, camera->getViewMatrix(), projection);
}

// -------------------------------------------------------------------------
// overview		プレイヤーの描画処理
//
// argument		context デバイスリソーシーズのコンテクスト
// argument		state コモンステート
// argument		camera フォローカメラ
// argument		projection マトリックス
//
// return		なし
// -------------------------------------------------------------------------
void Player::Render(ID3D11DeviceContext* context, CommonStates& state, FollowCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	m_player_model->Draw(context, state, m_player_matrix, camera->getViewMatrix(), projection);
}

// -------------------------------------------------------------------------
// overview		プレイヤーの後始末
//
// argument		なし
//
// return		なし
// -------------------------------------------------------------------------
void Player::Finalize()
{
	m_player_model.reset();
}
