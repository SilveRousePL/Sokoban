#include "Artifact.hpp"

Artifact::Artifact(float x, float y, ResourceManager * manager)
    :trigger_(false)
{
    setPosition(x, y);
    ptr_manager_ = manager;
}

Artifact::~Artifact()
{
    ptr_manager_ = nullptr;
    delete ptr_manager_;
}

void Artifact::move(sf::Vector2f & offset)
{
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

void Artifact::SetTrigger(bool t)
{
    trigger_ = t;
}

void Artifact::Update()
{
    trigger_ ?
        setTexture(*ptr_manager_->GetTexture(TEXTURE_ID::OBJECT_GLOW))
        :
        setTexture(*ptr_manager_->GetTexture(TEXTURE_ID::OBJECT));
}
