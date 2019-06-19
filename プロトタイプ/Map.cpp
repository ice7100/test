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
#include "Map.h"
#include "DebugCamera.h"
#include "FollowCamera.h"
#include "TiledMap.h"

// ���O��Ԃ̒�` ===========================================================
using namespace DirectX;

// �N���X�萔�̒�` =========================================================
const float Map::SIZE = 5.0f;

// �����o�֐��̒�` =========================================================
// -------------------------------------------------------------------------
// overview		�R���X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Map::Map()
{
	m_tiledmap = std::make_unique<TiledMap>();
}

// -------------------------------------------------------------------------
// overview		�f�X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Map::~Map()
{

}

// -------------------------------------------------------------------------
// overview		�}�b�v�̏���������
//
// argument		device �f�o�C�X���\�[�V�[�Y�̃f�o�C�X
// argument		context �f�o�C�X���\�[�V�[�Y�̃R���e�N�X�g
//
// return		�Ȃ�
// -------------------------------------------------------------------------
void Map::Initialize(ID3D11Device1* device, ID3D11DeviceContext* context)
{
	// �e�N�X�`���̃��[�h

	// ���f���̍쐬
	m_wallmodel = GeometricPrimitive::CreateBox(context, DirectX::SimpleMath::Vector3(SIZE, 8.f, SIZE));

	m_tiledmap->LoadMapData("mapchip.csv");

	m_texture.resize(2);
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/concrete.png", nullptr, m_texture[0].GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/substance.png", nullptr, m_texture[1].GetAddressOf());
}

// -------------------------------------------------------------------------
// overview		�}�b�v�̕`�揈��
//
// argument		camera �f�o�b�O�J����
// argument		projection �ˉe�s��
//
// return		�Ȃ�
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

			float x = j * SIZE - 60.f;
			float z = i * SIZE - 60.f;

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
// overview		�}�b�v�̕`�揈��
//
// argument		camera �t�H���[�J����
// argument		projection �ˉe�s��
//
// return		�Ȃ�
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

			float x = j * SIZE - 60.f;
			float z = i * SIZE - 60.f;

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