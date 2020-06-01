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

	void SpawnerBase::LoadCSV(en_ObjectType objType) {
		int SelectStage = GameManager::GetInstance().GetSelectStageNum();

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		wstring csvFilePths;

		if (objType == en_ObjectType::en_Wave) {
			csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.stageStr[SelectStage] + L".csv";
		}
		else if (objType == en_ObjectType::en_Item) {
			csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.itemStr[SelectStage] + L".csv";
		}

		CsvFile LoadCsvFile;
		m_gameStageCs.SetFileName(csvFilePths);
		m_gameStageCs.ReadCsv();
		auto& lineVec = m_gameStageCs.GetCsvVec();
		for (size_t i = 0; i < lineVec.size(); i++) {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, lineVec[i], L',');
			ReadCSVLine(tokens, objType);
			//for (size_t j = 0; j < tokens.size(); j++) {
			//	float num = stof(tokens[j]);
			//	m_createPosX.push_back(num);
			//}
		};
		//GetComponent<Transform>()->GetPosition();
	}

	void SpawnerBase::ReadCSVLine(vector<wstring> csvLine, en_ObjectType objType) {
		if (objType == en_ObjectType::en_Wave) {
			for (size_t j = 0; j < csvLine.size(); j++) {
				int waveTypeNum = stof(csvLine[j]);
				float num = stof(csvLine[j + 1]);
				m_waveTypeNum.push_back(waveTypeNum);
				m_createPosX.push_back(num);
				j++;
			}
		}
		else if (objType == en_ObjectType::en_Item) {
			for (size_t j = 0; j < csvLine.size(); j++) {
				float posX = stof(csvLine[j]);
				float posY = stof(csvLine[j + 1]);
				m_createPosX.push_back(posX);
				m_createPosY.push_back(posY);
				j++;
			}
		}
	}

}