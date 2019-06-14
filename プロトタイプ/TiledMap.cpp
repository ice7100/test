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
#include "TiledMap.h"

#include <fstream>
#include <sstream>
#include <string>

// メンバ関数の定義 =========================================================
// -------------------------------------------------------------------------
// overview		コンストラクタ
//
// argument		なし
// -------------------------------------------------------------------------
TiledMap::TiledMap()
{

}

// -------------------------------------------------------------------------
// overview		csvデータの読み込み
//
// argument		filename マップデータのファイル名
//
// return		読み込みに成功した時にtrueを返す
// -------------------------------------------------------------------------
bool TiledMap::LoadMapData(const char* filename)
{
	// ファイルを開く
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return false;
	}

	// ストリームから入力された文字列
	std::string line;

	// csvデータを開く
	if (ifs.is_open())
	{
		// 行列を確保
		m_mapdata.resize(m_row);
		for (int i = 0; i < m_row; i++)
		{
			m_mapdata[i].resize(m_column);
		}
		// csvファイルからデータを読み込む
		for (int i = 0; i < m_column; i++)
		{
			for (int j = 0; j < m_row; j++)
			{
				getline(ifs, line, ',');
				m_mapdata[i][j] = stoi(line);
			}
		}
		// csvデータを閉じる
		ifs.close();
	}

	return true;
}