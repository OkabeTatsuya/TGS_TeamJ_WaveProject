/*!
@file Character.h
@brief “®‚­”g‚Ì“–‚½‚è”»’è
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class WaveCollision : public ObjectBase {
    public:
		WaveCollision(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position
            );

		virtual void OnCreate() override;
        virtual void OnUpdate() override;
        void Stop();

		//”g‚ª¶¬‚³‚ê‚½‚Æ‚«ƒRƒŠƒWƒ‡ƒ“‚ğ‹N‚±‚·
        void AwakeCollision();
	};
}
//end basecross
