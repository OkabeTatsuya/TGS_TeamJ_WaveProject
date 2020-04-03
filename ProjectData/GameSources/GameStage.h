/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//BGMの再生
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		bool m_isPause;

		//�ｿｽQ�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽn�ｿｽﾟゑｿｽO�ｿｽﾌ硬�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//�ｿｽQ�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽN�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ使�ｿｽ�ｿｽ
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		bool m_isFadeIn;

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		//消除時
		virtual void OnDestroy()override;

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();

	};


}
//end basecross

