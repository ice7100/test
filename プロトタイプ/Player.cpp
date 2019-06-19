// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //
// file			Player.cpp
//
// overview		�v���C���[�Ɋւ��Ẵ\�[�X
//
// date			2019/06/14
//
// author		�u�ꗴ�V��
// -!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!- //

// �w�b�_�t�@�C���̓ǂݍ��� =================================================
#include "pch.h"
#include "Player.h"
#include "DebugCamera.h"
#include "FollowCamera.h"

// ���O��Ԃ̒�` ===========================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �N���X�萔�̒�` =========================================================
const float Player::PLAYER_VEL = 0.3f;
const float Player::RADIUS = 0.98f;

// �����o�֐��̒�` =========================================================
// -------------------------------------------------------------------------
// overview		�R���X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Player::Player()
{

}

// -------------------------------------------------------------------------
// overview		�f�X�g���N�^
//
// argument		�Ȃ�
// -------------------------------------------------------------------------
Player::~Player()
{

}

// -------------------------------------------------------------------------
// overview		�v���C���[�̏���������
//
// argument		device �f�o�C�X���\�[�V�[�Y�̃f�o�C�X
// argument		factory �G�t�F�N�g�t�@�N�g���[
//
// return		�Ȃ�
// -------------------------------------------------------------------------
void Player::Initialize(ID3D11Device1* device, EffectFactory* factory)
{
	// �t�@�C�����w�肵�ă��f���f�[�^��ǂݍ���
	m_player_model = DirectX::Model::CreateFromCMO(
		device, L"Resources/Models/Player.cmo",
		*factory);

	// �v���C���[pos�̏�����
	m_player_pos = Vector3();

	// �v���C���[vel�̏�����
	m_player_vel = Vector3(PLAYER_VEL, 0.0f, PLAYER_VEL);

	m_player_box.center = m_player_pos;
	m_player_box.radius = DirectX::SimpleMath::Vector3(RADIUS, RADIUS, RADIUS);
}

// -------------------------------------------------------------------------
// overview		�v���C���[�X�V����
//
// argument		�Ȃ�
//
// return		�Ȃ�
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
// overview		�v���C���[�̕`�揈��
//
// argument		context �f�o�C�X���\�[�V�[�Y�̃R���e�N�X�g
// argument		state �R�����X�e�[�g
// argument		camera �f�o�b�O�J����
// argument		projection �}�g���b�N�X
//
// return		�Ȃ�
// -------------------------------------------------------------------------
void Player::Render(ID3D11DeviceContext* context, DirectX::CommonStates& state, DebugCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	m_player_model->Draw(context, state, m_player_matrix, camera->getViewMatrix(), projection);
}

// -------------------------------------------------------------------------
// overview		�v���C���[�̕`�揈��
//
// argument		context �f�o�C�X���\�[�V�[�Y�̃R���e�N�X�g
// argument		state �R�����X�e�[�g
// argument		camera �t�H���[�J����
// argument		projection �}�g���b�N�X
//
// return		�Ȃ�
// -------------------------------------------------------------------------
void Player::Render(ID3D11DeviceContext* context, CommonStates& state, FollowCamera* camera, DirectX::SimpleMath::Matrix projection)
{
	m_player_model->Draw(context, state, m_player_matrix, camera->getViewMatrix(), projection);
}

// -------------------------------------------------------------------------
// overview		�v���C���[�̌�n��
//
// argument		�Ȃ�
//
// return		�Ȃ�
// -------------------------------------------------------------------------
void Player::Finalize()
{
	m_player_model.reset();
}
