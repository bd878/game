#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : AnimatedObject()
{

}

void AnimatedGraphic::Load(std::unique_ptr<LoaderParams> const& pParams)
{
    AnimatedObject::Load(std::move(pParams));
    m_animSpeed = pParams->GetAnimSpeed();
}

void AnimatedGraphic::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}