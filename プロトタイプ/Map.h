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
#include "SimpleMath.h"
#include "GeometricPrimitive.h"
#include <WICTextureLoader.h>

// �N���X�̑O���錾 =========================================================
class DebugCamera;
class FollowCamera;
class TiledMap;

// <�}�b�v�N���X> ----------------------------------------------------------
class Map
{
	private:
		// �N���X�萔�̐錾
		static const float SIZE;

		// �����o�ϐ��̐錾
		
		// ���f��
		std::unique_ptr<DirectX::GeometricPrimitive>				  m_wallmodel;
		// �e�N�X�`��
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
		// �^�C���h�}�b�v
		std::unique_ptr<TiledMap>									  m_tiledmap;

	// �����o�֐��̐錾
	public:
		// �R���X�g���N�^
		Map();
		// �f�X�g���N�^
		~Map();

		// ����
		void Initialize(ID3D11Device1* device, ID3D11DeviceContext* context);
		void Render(DebugCamera* camera, DirectX::SimpleMath::Matrix projection);
		void Render(FollowCamera* camera, DirectX::SimpleMath::Matrix projection);
};
