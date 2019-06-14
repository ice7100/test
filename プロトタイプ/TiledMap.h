// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			TiledMap.h
//
// overview		�}�b�v�f�[�^��p�ӂ���w�b�_
//
// date			2019/06/12
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// ���d�C���N���[�h�̖h�~ ===================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include <vector>

// <�^�C���h�}�b�v�N���X> --------------------------------------------------
class TiledMap
{
	private:
		// �N���X�萔�̐錾
		const int m_row = 25;
		const int m_column = m_row;

		// �����o�ϐ��̐錾

		// �}�b�v�f�[�^
		std::vector<std::vector<int>> m_mapdata;

	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		TiledMap();
		
		// ����

		// csv�f�[�^�̓ǂݍ���
		bool LoadMapData(const char* filename);
		
		// row�̃Q�b�^�[
		int GetRow()
		{
			return m_row;
		}

		// column�̃Q�b�^�[
		int GetColumn()
		{
			return m_column;
		}

		// �}�b�v�f�[�^�̃Q�b�^�[
		int GetNumber(int _row, int _column)
		{
			return m_mapdata[_row][_column];
		}
};

