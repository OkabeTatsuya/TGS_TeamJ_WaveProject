/*!
@file SpawnerBase.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpawnerBase::SpawnerBase(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{
	}

	SpawnerBase::~SpawnerBase() {

	}

	void SpawnerBase::LoadCSV() {
		int SelectStage = GameManager::GetInstance().GetSelectStageNum();

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		auto csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.stageStr[SelectStage] + L".csv";
		CsvFile LoadCsvFile;
		m_gameStageCs.SetFileName(csvFilePths);
		m_gameStageCs.ReadCsv();
		auto& lineVec = m_gameStageCs.GetCsvVec();
		for (size_t i = 0; i < lineVec.size(); i++) {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, lineVec[i], L',');
			for (size_t j = 0; j < tokens.size(); j++) {
				float num = stof(tokens[j]);
				m_createPos.push_back(num);
			}
		};

		GetComponent<Transform>()->GetPosition();
	}
}