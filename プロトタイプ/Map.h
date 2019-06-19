// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.h
//
// overview		マップデータを用意するヘッダ
//
// date			2019/06/12
//
// author		志賀龍之介
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// 多重インクルードの防止 ===================================================
#pragma once

// ヘッダファイルの読み込み =================================================
#include <vector>
#include "SimpleMath.h"
#include "GeometricPrimitive.h"
#include <WICTextureLoader.h>

// クラスの前方宣言 =========================================================
class DebugCamera;
class FollowCamera;
class TiledMap;

// <マップクラス> ----------------------------------------------------------
class Map
{
	private:
		// クラス定数の宣言
		static const float SIZE;

		// メンバ変数の宣言
		
		// モデル
		std::unique_ptr<DirectX::GeometricPrimitive>				  m_wallmodel;
		// テクスチャ
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
		// タイルドマップ
		std::unique_ptr<TiledMap>									  m_tiledmap;

	// メンバ関数の宣言
	public:
		// コンストラクタ
		Map();
		// デストラクタ
		~Map();

		// 操作
		void Initialize(ID3D11Device1* device, ID3D11DeviceContext* context);
		void Render(DebugCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Render(FollowCamera* camera, DirectX::SimpleMath::Matrix projection);
};
