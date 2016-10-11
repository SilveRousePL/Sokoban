#ifndef ARTIFACT_HPP_
#define ARTIFACT_HPP_

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

class Artifact
    :public sf::Sprite
{
public:
    Artifact(float x, float y, ResourceManager * manager);
    ~Artifact();

    void move(sf::Vector2f& offset);

    void Update();

    void SetTrigger(bool t);

private:
    bool trigger_;

    ResourceManager * ptr_manager_;

};

#endif // ARTIFACT_HPP_
