// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.cpp
//
// overview		�}�b�v�f�[�^��p�ӂ���\�[�X
//
// date			2019/06/12
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include "pch.h"
#include "TiledMap.h"

#include <fstream>
#include <sstream>
#include <string>

// �����o�֐��̒�` =========================================================
// -------------------------------------------------------------------------
// overview		�R���X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
TiledMap::TiledMap()
{

}

// -------------------------------------------------------------------------
// overview		csv�f�[�^�̓ǂݍ���
//
// argument		filename �}�b�v�f�[�^�̃t�@�C����
//
// return		�ǂݍ��݂ɐ�����������true��Ԃ�
// -------------------------------------------------------------------------
bool TiledMap::LoadMapData(const char* filename)
{
	// �t�@�C�����J��
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return false;
	}

	// �X�g���[��������͂��ꂽ������
	std::string line;

	// csv�f�[�^���J��
	if (ifs.is_open())
	{
		// �s����m��
		m_mapdata.resize(m_row);
		for (int i = 0; i < m_row; i++)
		{
			m_mapdata[i].resize(m_column);
		}
		// csv�t�@�C������f�[�^��ǂݍ���
		for (int i = 0; i < m_column; i++)
		{
			for (int j = 0; j < m_row; j++)
			{
				getline(ifs, line, ',');
				m_mapdata[i][j] = stoi(line);
			}
		}
		// csv�f�[�^�����
		ifs.close();
	}

	return true;
}