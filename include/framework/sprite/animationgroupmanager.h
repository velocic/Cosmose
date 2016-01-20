#ifndef ANIMATIONGROUPMANAGER_H
#define ANIMATIONGROUPMANAGER_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <framework/sprite/animationgroup.h>
#include <utilities/tinyxml2.h>

namespace Framework
{
    namespace Sprite
    {
        class AnimationGroupManager
        {
            private:
                std::unordered_map<std::string, std::shared_ptr<AnimationGroup>> animationGroups;
                AnimationMetaData parseAnimationMetaData(tinyxml2::XMLElement* animationRootElement);
                SpriteTextureCoordinates parseAnimationCellData(tinyxml2::XMLElement* spriteElement, unsigned int textureAtlasWidth, unsigned int textureAtlasHeight);
            public:
                std::weak_ptr<AnimationGroup> getAnimationGroup(std::string filePath);
                bool createAnimationGroupFromXMLFile(std::string filePath);
        };
    }
}

#endif
