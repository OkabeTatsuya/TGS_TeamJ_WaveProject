/*!
@file WaveSpawner.h
@brief �Q�[�����Ǘ�����I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum WaveType {
		en_waveS,
		en_waveM,
		en_waveL
	};

	struct WaveState
	{
		Vec3 Rot;
		vector<Vec3> Sca;
		vector<Vec3> Pos;
		int Layer;
		vector<wstring> Tex;
	};

	class WaveSpawner : public SpawnerBase {
		WaveState m_waveState;

		//�g��ۑ�
		//[�g�̎��][�g�̌�]
		vector<vector<shared_ptr<Wave>>>m_waveObject;

		//���O�ɐ�������I�u�W�F�N�g�̌�
		vector<int> m_defaultObjectNum;
		//���������I�u�W�F�N�g�̌�
		int m_spawnCount;
		//�I�u�W�F�N�g�̐������鎞��
		float m_spawnTimer = 0.0f;
		//��ʊO��X���W
		float m_offScreen;
		//�X�|�i�[���~�߂�t���O
		bool m_isStopSpawn;
		//�r�b�O�E�F�[�u�����p�̃^�C�}�[
		float m_createBigWaveTimer;
		//�r�b�O�E�F�[�u�𐶐����鎞��
		float m_maxWaitingTime;
		//�r�b�O�E�G�[�u���������ꂽ�t���O
		bool m_isCreateBigWave;

	public:
		WaveSpawner(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		float GetSpawnTimer() { return m_spawnTimer; }
		float GetMaxCreatePosX() { return m_createPosX.back(); }

		//�v�[�����O����I�u�W�F�N�g�̍쐬
		void CreateObject();

		//�I�u�W�F�N�g���ʂ�
		void VisibleObject(int waveTypeNum);

		//�I�u�W�F�N�g�𐶐�����
		void SpawnObject();

		//�X�y�V�����^�C���̔g�𐶐�����
		void CreateBigWave();

		void EndCreateObject();
	};
}