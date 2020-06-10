/*!
@file UnlockStageUI.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UnlockStageUI::UnlockStageUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex) :
		ImageUI(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{
		m_SE = { nullptr, nullptr };
		m_isPlaySE = { false, false };

		m_isPlayAnim = false;
		m_animTimer = 0;
		m_animEndTime = 1.5f;

		m_nextAnimeTime = {0.0f, 2.0f, 3.5f};
		m_stageImageName = { 
			L"StageImage2.png",
			L"StageImage3.png",
			L"StageImage4.png" 
		};

		m_stageNumImageName = {
			L"Stage2.png",
			L"Stage3.png",
			L"Stage4.png"
		};
	}

	void UnlockStageUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
		CreateUI();

		auto drawPtr = GetComponent<PCTSpriteDraw>();
		drawPtr->SetDrawActive(false);
	}

	void UnlockStageUI::OnUpdate() {
		AnimUI();

		if (m_isPlayAnim) {
			auto delta = App::GetApp()->GetElapsedTime();
			m_animTimer += delta;
		}

		UnLockAnim();
	}

	void UnlockStageUI::OnDestroy() {

	}

	void UnlockStageUI::CreateUI() {
		auto& manager = GameManager::GetInstance();
		m_lockUI = GetStage()->AddGameObject<ImageUI>(Vec3(0.0f), Vec3(128.0f, 128.0, 1.0f), Vec2(250.0f, 250.0f), float(7.0f), L"Lock.png");

		auto setNum = manager.GetClearStageNum();
		wstring setStageImageTex = L"";
		wstring setStageNumImageTex = L"";
		if (setNum <= m_stageImageName.size() - 1) {
			setStageImageTex = m_stageImageName[setNum];
			setStageNumImageTex = m_stageNumImageName[setNum];
		}
		else {
			setStageImageTex = m_stageImageName[0];
			setStageNumImageTex = m_stageNumImageName[0];
		}

		m_stageImageUI = GetStage()->AddGameObject<ImageUI>(Vec3(0.0f), Vec3(640.0f, 400.0f, 1.0f), Vec2(0.0f, -15.0f), float(7.0f), setStageImageTex);
		m_stageNumUI = GetStage()->AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(0.0f, 230.0f), float(7.0f), setStageNumImageTex);
		m_UnlockBackUI = GetStage()->AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1400.0f, 1150.0f, 1.0f), Vec2(-5.0f, 100.0f), float(6.0f), L"StageBG.png");

		//UIを非表示にする
		auto drawPtr = m_lockUI->GetComponent<PCTSpriteDraw>();
		drawPtr->SetDrawActive(false);
		m_stageImageUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		m_stageNumUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		m_UnlockBackUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);

	}

	void UnlockStageUI::UnLockAnim() {
		if (m_animTimer > m_nextAnimeTime[0]) {
			PlaySE(0, L"se_maoudamashii_onepoint16.wav", 0.7f);

			if (!m_isVisibleUI) {
				m_lockUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
				m_stageImageUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
				m_stageNumUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
				m_UnlockBackUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
				m_isVisibleUI = true;
			}
		}

		if (m_animTimer > m_nextAnimeTime[1]) {
			m_lockUI->ChangeImage(L"UnLock.png");
			PlaySE(1, L"se_maoudamashii_se_sound20.wav", 1.0f);
		}

		if (m_animTimer > m_nextAnimeTime[2]) {
			m_lockUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_stageImageUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_stageNumUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_UnlockBackUI->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_isPlayAnim = false;
			m_isEndAnim = true;
		}
	}

	void UnlockStageUI::AnimUI() {
		auto drawPtr = GetComponent<PCTSpriteDraw>();

	};

	void UnlockStageUI::PlayAnim() {
		m_isPlayAnim = true;
	}

	void UnlockStageUI::PlaySE(int seNum, wstring seName, float seVol) {
		if (m_isPlaySE[seNum] == false) {
			auto audioManager = App::GetApp()->GetXAudio2Manager();
			m_SE[seNum] = audioManager->Start(seName, 0, seVol);
			m_isPlaySE[seNum] = true;
		}
	}

}