#include <framework/sprite/animationgroupmanager.h>

std::weak_ptr<AnimationGroup> Framework::Sprite::AnimationGroupManager::getAnimationGroup(std::string filePath)
{
}

void Framework::Sprite::AnimationGroupManager::createAnimationGroupFromXMLFile(std::string filePath)
{
    TiXmlDocument spriteSheetMetaData(filePath);
    bool loadSuccessful = spriteSheetMetaData.LoadFile();

    if (!loadSuccessful) {
        return;
    }

    std::unordered_map<std::string, std::vector<SpriteTextureCoordinates>> animations;
    std::unordered_map<std::string, AnimationMetaData> animationData;

    TiXmlElement* root = spriteSheetMetaData.FirstChildElement("TextureAtlas");
    unsigned int textureAtlasWidth = root->UnsignedAttribute("width");
    unsigned int textureAtlasHeight = root->UnsignedAttribute("height");

    std::string animationName;

    //Parse each animation out of the texture atlas
    for (auto animation = root.FirstChildElement("animation"); animation != NULL; animation = animation->NextSiblingElement("animation")) {

        animationName = animation->Attribute("name");
        std::vector<SpriteTextureCoordinates> animationCellContainer;

        parseAnimationMetaData(animation);

        animationData.insert(std::make_pair(animationName, animationData));
        animations.insert(std::make_pair(animationName, animationCellContainer));

        //Parse each animation cell associated with the current animation
        for (auto sprite = animation.FirstChildElement("sprite"); sprite != NULL; sprite = sprite->NextSiblingElement("sprite")) {
            animations.find(animationName)->second.push_back(
                parseAnimationCellData(
                    sprite,
                    textureAtlasWidth,
                    textureAtlasHeight
                )
            );
        }
    }

    //finally, construct an AnimationGroup object, and pass it "animations" and "animationData",
    //allowing it to use std::move to take ownership of those maps
    std::shared_ptr animationGroupPtr(
        new AnimationGroup(
            std::move(animations),
            std::move(animationData)
        )
    );

    animationGroups.insert(
        std::make_pair<std::string, std::shared_ptr<AnimationGroup>>(
            animationName,
            animationGroupPtr
        )
    );
}

AnimationMetaData Framework::Sprite::AnimationGroupManager::parseAnimationMetaData(tinyxml2::XMLElement* animationRootElement)
{
    AnimationMetaData parsedData;
    parsedData.framesBetweenAnimationCells = animationRootElement->UnsignedAttribute("framesBetweenCells");
    parsedData.animationCellCount = animationRootElement->UnsignedAttribute("cellCount");

    return parsedData;
}

SpriteTextureCoordinates Framework::Sprite::AnimationGroupManager::parseAnimationCellData(tinyxml2::XMLElement* spriteElement, unsigned int textureAtlasWidth, unsigned int textureAtlasHeight)
{
    //note: need to convert from absolute pixel coordinates (stored in the xml) to UV coordinates
    //(which are between 0 and 1)
    unsigned int x;
    unsigned int y;
    unsigned int spriteWidth;
    unsigned int spriteHeight;

    //need to figure out which order to use these 4 coordinate points
    //also, may need to reconcile coordinate systems between TexturePacker and OpenGL UV Coords
    //x, y
    //x+width, y
    //x, y+width
    //x+width, y+width
    SpriteTextureCoordinates coordinates;
    textureCoordinate1 = glm::vec2(); 
    textureCoordinate2 = glm::vec2(); 
    textureCoordinate3 = glm::vec2();
    textureCoordinate4 = glm::vec2();

    return coordinates;
}
