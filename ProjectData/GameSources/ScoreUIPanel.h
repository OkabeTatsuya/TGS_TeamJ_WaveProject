/*!
@file Character.h
@brief �X�R�AUI���܂Ƃ߂�p�l��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUIPanel: public UIBase {
    private:
        //�����ʒu
        float m_initPosX;
        //�\������UI�̌���
         const int m_count;
        //�\������UI�B
        vector<shared_ptr<ScoreUI>> m_scoreUIs;
        //�v���C���[�̏�ɕ\�����邩�ۂ�
        bool m_isScorePlusUI;
        //�v���C���[�̏�ɕ\������ۂ̕\�����ԏ��
        float m_maxScorePlusDrawTime;
        //���݂̃v���C���[�̏�ɕ\�����Ă��鎞��
        float m_currentScorePlusDrawTime;
        //�X�R�A�v���XUI�\���t���O
        bool m_isScorePlusUIActive;
		//���̐����Ԃ̋󔒂𒲐����邽�߂̔{��
		float m_addPosMagnification;
        //�\������X�R�A�̌����F��
        bool m_isFirstNumber;
        //�ŏ��̌���
        int m_firstNumberDigit;
        //�\������X�R�A
        int m_score;
        //���l�߂���}�X��
        int m_adjustLeftPosCount;
        //�E�l�߃t���O
        bool m_isAdjustRight;
    public:
        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count,
            bool isPlyaerPlusScore);

        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count,
            bool isPlyaerPlusScore,
            bool isAdjustRight);


        virtual void OnCreate() override;
        virtual void OnUpdate() override;

        //�X�R�A�\��
        void ScoreDraw(int score);
        //�X�R�A�A�b�v���̕\��
        void ScorePlusDraw();
        //�X�R�A�A�b�v���̃v���C���[�̃|�W�V�����Ƃ̑��Ί֌W
        void AdjustPosition(Vec3 playerPos);
        //�\�������Ǘ�
        void ScoreCountJudge(int score);
        //���l�ߏ���
        void AdjustLeftPosition();
    };
}
//end basecross
