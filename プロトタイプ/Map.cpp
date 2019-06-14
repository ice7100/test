// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.cpp
//
// overview		マップデータを用意するソース
//
// date			2019/06/12
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ヘッダファイルの読み込み =================================================
#include "pch.h"
#include "Map.h"

// 名前空間の定義 ===========================================================
using namespace DirectX;

// クラス定数の定義 =========================================================
const float Map::SIZE = 5.0f;

// メンバ関数の定義 =========================================================
// -------------------------------------------------------------------------
// overview		コンストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Map::Map()
{
	m_tiledmap = std::make_unique<TiledMap>();
}

// -------------------------------------------------------------------------
// overview		デストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
Map::~Map()
{

}

// -------------------------------------------------------------------------
// overview		マップの初期化処理
//
// argument		device デバイスリソーシーズのデバイス
// argument		context デバイスリソーシーズのコンテクスト
//
// return		なし
// -------------------------------------------------------------------------
void Map::Initialize(ID3D11Device1* device, ID3D11DeviceContext* context)
{
	m_texture.resize(2);
	// テクスチャのロード

	// モデルの作成
	m_wallmodel = GeometricPrimitive::CreateBox(context, DirectX::SimpleMath::Vector3(SIZE, 8.f, SIZE));

	m_tiledmap->LoadMapData("mapchip.csv");

	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/concrete.png", nullptr, m_texture[0].GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/substance.png", nullptr, m_texture[1].GetAddressOf());
}

// -------------------------------------------------------------------------
// overview		マップの描画処理
//
// argument		camera デバッグカメラ
// argument		projection 射影行列
//
// return		なし
// -------------------------------------------------------------------------
void Map::Render(DebugCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	const int row = m_tiledmap->GetRow();
	const int column = m_tiledmap->GetColumn();
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int tileId = m_tiledmap->GetNumber(i, j);
			ID3D11ShaderResourceView* shaderResourceView = m_texture[tileId].Get();

			float x = j * SIZE - 12.f;
			float z = i * SIZE - 12.f;

			DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
			world *= DirectX::SimpleMath::Matrix::CreateTranslation(x, 4.f, z);

			DirectX::SimpleMath::Matrix cameraMatrix = camera->getViewMatrix();

			if (tileId == 1)
			{
				m_wallmodel->Draw(world, cameraMatrix, projection, Colors::White, shaderResourceView);
			}
		}
	}
}

// -------------------------------------------------------------------------
// overview		マップの描画処理
//
// argument		camera フォローカメラ
// argument		projection 射影行列
//
// return		なし
// -------------------------------------------------------------------------
void Map::Render(FollowCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	const int row = m_tiledmap->GetRow();
	const int column = m_tiledmap->GetColumn();
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int tileId = m_tiledmap->GetNumber(i, j);
			ID3D11ShaderResourceView* shaderResourceView = m_texture[tileId].Get();

			float x = j * SIZE - 12.f;
			float z = i * SIZE - 12.f;

			DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
			world *= DirectX::SimpleMath::Matrix::CreateTranslation(x, 4.f, z);

			DirectX::SimpleMath::Matrix cameraMatrix = camera->getViewMatrix();

			if (tileId == 1)
			{
				m_wallmodel->Draw(world, cameraMatrix, projection, Colors::White, shaderResourceView);
			}
		}
	}
}

// -------------------------------------------------------------------------
// overview		マップの描画処理
//
// argument		grid_x ポジションX
// argument		grid_y ポジションY
//
// return		通れるならtrueを返す
// -------------------------------------------------------------------------
//bool Map::IsPassable(float grid_x, float grid_z)
//{
//	return false;
//}
