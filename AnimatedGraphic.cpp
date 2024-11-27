#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject()
{

}

void AnimatedGraphic::Load(std::unique_ptr<LoaderParams> const& pParams)
{
    ShooterObject::Load(std::move(pParams));
    m_animSpeed = pParams->GetAnimSpeed();
}

void AnimatedGraphic::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}