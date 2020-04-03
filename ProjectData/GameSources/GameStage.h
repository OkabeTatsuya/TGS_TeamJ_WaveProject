/*!
@file GameStage.h
@brief ƒQ[ƒ€ƒXƒe[ƒW
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ƒQ[ƒ€ƒXƒe[ƒWƒNƒ‰ƒX
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();

		//BGM‚ÌÄ¶
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		bool m_isPause;

		//ï¿½Qï¿½[ï¿½ï¿½ï¿½ï¿½nï¿½ß‚ï¿½Oï¿½Ìdï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//ï¿½Qï¿½[ï¿½ï¿½ï¿½ï¿½Nï¿½ï¿½ï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Égï¿½ï¿½
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		bool m_isFadeIn;

	public:
		//\’z‚Æ”jŠü
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;

		//Áœ
		virtual void OnDestroy()override;

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();

	};


}
//end basecross

