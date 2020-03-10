/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
        bool m_isJump;
        Vec3 m_initRotation;
    public:
        Player(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnCollisionEnter(shared_ptr<GameObject>& gameobject) override;
        void Jump();
        void HighJump();
        void LowJump();
        void Initialize();
    };

}
//end basecross

