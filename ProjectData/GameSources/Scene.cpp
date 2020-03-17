
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
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
			// ������FILE_ATTRIBUTE_DIRECTORY�Ȃ�
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// �f�B���N�g�������擾
				wstring ditectoryName = win32fd.cFileName;
				// �V�����t�H���_�̏ꏊ
				wstring newDateDir = dir + ditectoryName + L"/";
				if (ditectoryName.find(L".")) {
					// ���̒�������
					FindFile(newDateDir);
				}
			}
			else {
				wstring fileName = win32fd.cFileName;

				auto exe = fileName.substr(fileName.find(L"."), fileName.length());

				//�摜�t�@�C���������ꍇ
				if (exe == L".png" || exe == L".tga" || exe == L".jpg") {
					// �t�@�C���̏ꏊ
					wstring strTexture = dir + fileName;
					// �e�N�X�`���[��o�^
					App::GetApp()->RegisterTexture(fileName, strTexture);
				}

				if (exe == L".wav") {
					wstring OpenWav = dir + fileName;

					App::GetApp()->RegisterWav(fileName, OpenWav);
				}
			}
		} while (FindNextFile(hFind, &win32fd));

		// �㏈��
		FindClose(hFind);

	}


	void Scene::OnCreate(){
		try {
			CreateResourses();
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���

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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToResulfStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<ResultStage>();
		}
	}

	//�X�e�[�W�ړ�����
	void Scene::LoadStage(wstring stageName) {
		PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), stageName);
	}

}
//end basecross
