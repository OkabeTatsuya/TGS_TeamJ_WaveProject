
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	void Scene::CreateResourses() {
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		FindFile(dataDir);
		//FindFile(mediaDir + L"Sound/SE/");
		//FindFile(mediaDir + L"Sound/BGM/");
		FindFile(mediaDir + L"Image/");
	}

	void Scene::FindFile(wstring dir) {
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;

		wstring newdir = dir + L"*.*";
		const wchar_t *dirExtension = newdir.c_str();

		hFind = FindFirstFile(dirExtension, &win32fd);

		do {
			// 属性がFILE_ATTRIBUTE_DIRECTORYなら
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// ディレクトリ名を取得
				wstring ditectoryName = win32fd.cFileName;
				// 新しいフォルダの場所
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// その中を検索
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//画像ファイルだった場合
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// ファイルの場所
					wstring strTexture = dir + fileName;
					// テクスチャーを登録
					App::GetApp()->RegisterTexture(fileName, strTexture);
				}

				if (exe == L".wav") {
					wstring OpenWav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, OpenWav);
				}
			}
		} while (FindNextFile(hFind, &win32fd));

		// 後処理
		FindClose(hFind);

	}


	void Scene::OnCreate(){
		try {
			CreateResourses();
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる

			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}



	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToResulfStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<ResultStage>();
		}
	}

	//ステージ移動処理
	void Scene::LoadStage(wstring stageName) {
		PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), stageName);
	}

}
//end basecross
