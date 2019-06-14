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

// <タイルドマップクラス> --------------------------------------------------
class TiledMap
{
	private:
		// クラス定数の宣言
		const int m_row = 25;
		const int m_column = m_row;

		// メンバ変数の宣言

		// マップデータ
		std::vector<std::vector<int>> m_mapdata;

	// メンバ関数の宣言
	public:
		// コンストラクタ
		TiledMap();
		
		// 操作

		// csvデータの読み込み
		bool LoadMapData(const char* filename);
		
		// rowのゲッター
		int GetRow()
		{
			return m_row;
		}

		// columnのゲッター
		int GetColumn()
		{
			return m_column;
		}

		// マップデータのゲッター
		int GetNumber(int _row, int _column)
		{
			return m_mapdata[_row][_column];
		}
};

