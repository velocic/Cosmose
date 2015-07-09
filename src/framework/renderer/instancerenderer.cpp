#include <framework/renderer/instancerenderer.h>

void Framework::Renderer::InstanceRenderer::render(std::vector<Framework::Sprite::BasicSprite> &spriteCollection)
{
}

void Framework::Renderer::InstanceRenderer::sortSpriteCollectionByTexture(
    std::vector<Framework::Sprite::BasicSprite> &spriteCollection
)
{
    std::sort(
        spriteCollection.begin(),
        spriteCollection.end(),
        [](const Framework::Sprite::BasicSprite &sprite1, const Framework::Sprite::BasicSprite &sprite2) {
            return sprite1.getTexture()->getName() < sprite2.getTexture()->getName();
        }
    );
}
