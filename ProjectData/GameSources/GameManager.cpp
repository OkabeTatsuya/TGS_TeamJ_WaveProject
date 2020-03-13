/*!
@file GameManager.cpp
@brief ゲームを管理するオブジェクト
*/

#include "stdafx.h"
#include "Project.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace basecross {
	GameManager::GameManager(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{
		m_maxStartTime = 1.0f;
		m_startTimeCount = 0.0f;
		m_isFrastStop = true;
		m_isGameEnd = false;
	}

	void GameManager::OnCreate() {
		GetStage()->SetSharedGameObject(L"GameManager", GetThis<GameManager>());
		//ReadGameData();

		//デバッグ用のスプライトをつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}

	void GameManager::OnUpdate() {
		if (m_isFrastStop) {
			FrastTimeCount();
			return;
		}

		LoadResultStage();

		//DebugHander();
	}

	void GameManager::OnUpdate2() {
		//デバッグ用の文字列表示処理
		//DebugString();
	}


	void GameManager::FrastTimeCount() {
		if (m_startTimeCount < m_maxStartTime) {
			auto delta = App::GetApp()->GetElapsedTime();
			m_startTimeCount += delta;
			return;
		}
		else {
			m_isFrastStop = false;
		}
	}

	void GameManager::LoadResultStage() {
		if (m_isGameEnd) {
			SaveGameData();
			App::GetApp()->GetScene<Scene>()->LoadStage(L"ToResulfStage");
		}
	}

	void GameManager::SaveGameData() {
		float fa = 500000000;
		ofstream fout;

		//FILE* fp;
		fout.open("file.fa", ios::binary | ios::out | ios::trunc);
		//fopen_s(&fp, "data.fa", "wb");

		if (!fout) {
			cout << "セーブできませ―――ン！！";
		}
		for (int i = 0; i < 1; i++) {

			//fwrite(&fa, sizeof(fa), 1, fp);

			fout.write((char *)&fa, sizeof(int));
		}
		//fclose(fp);

		fout.close();
	}

	void GameManager::ReadGameData() {
		char outfile[] = "file.fa";

		ifstream fin(outfile, ios::in | ios::binary);

		if (!fin) {
			cout << "ファイルが読み込めませ―――ん！！";
			fin.close();
			return;
		}

		while (!fin.eof()) {
			//fin.seekg(1*sizeof(float));
			fin.read((char *)&m_saveNum, sizeof(int));
		}
		fin.close();
	}

	void GameManager::DebugHander() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				m_isGameEnd = true;
			}
		}
	}


	//デバッグ用の文字列表示処理
	void GameManager::DebugString() {
		//文字列表示
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\n";

		//auto pos = GetComponent<Transform>()->GetPosition();
		//wstring positionStr(L"Position:\t");
		//positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		//positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		//positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		//wstring gravStr(L"GravityVelocoty:\t");
		//auto gravVelocity = GetComponent<Gravity>()->GetGravityVelocity();
		//gravStr += L"X=" + Util::FloatToWStr(gravVelocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		//gravStr += L"Y=" + Util::FloatToWStr(gravVelocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		//gravStr += L"Z=" + Util::FloatToWStr(gravVelocity.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring saveData(L"SaveData:\t");
		saveData += Util::FloatToWStr(m_saveNum, 6, Util::FloatModify::Fixed);

		wstring str = fpsStr + saveData;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);





	}

}