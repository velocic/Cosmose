#include <framework/sprite/animationgroupmanager.h>

std::weak_ptr<Framework::Sprite::AnimationGroup> Framework::Sprite::AnimationGroupManager::getAnimationGroup(std::string filePath)
{
    return std::weak_ptr<AnimationGroup>(animationGroups.find(filePath)->second);
}

bool Framework::Sprite::AnimationGroupManager::createAnimationGroupFromXMLFile(std::string filePath)
{
    tinyxml2::XMLDocument spriteSheetMetaData;
    auto loadSuccessful = spriteSheetMetaData.LoadFile(filePath.c_str());

    if (loadSuccessful != tinyxml2::XML_SUCCESS)
    {
        return false;
    }

    std::unordered_map<std::string, std::vector<SpriteTextureCoordinates>> animations;
    std::unordered_map<std::string, AnimationMetaData> animationData;

    tinyxml2::XMLElement* root = spriteSheetMetaData.FirstChildElement("TextureAtlas");
    unsigned int textureAtlasWidth = root->UnsignedAttribute("width");
    unsigned int textureAtlasHeight = root->UnsignedAttribute("height");

    std::string animationName;

    //Parse each animation of the texture atlas from the XML file
    for (auto animation = root->FirstChildElement("animation"); animation != NULL; animation = animation->NextSiblingElement("animation")) {

        animationName = animation->Attribute("name");
        std::vector<SpriteTextureCoordinates> animationCellContainer;

        AnimationMetaData parsedMetaData = parseAnimationMetaData(animation);

        animationData.insert(std::make_pair(animationName, parsedMetaData));
        animations.insert(std::make_pair(animationName, animationCellContainer));

        //Parse each animation cell associated with the current animation
        for (auto sprite = animation->FirstChildElement("sprite"); sprite != NULL; sprite = sprite->NextSiblingElement("sprite")) {
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
    std::shared_ptr<AnimationGroup> animationGroupPtr(
        new AnimationGroup(
            std::move(animations),
            std::move(animationData)
        )
    );

    animationGroups.insert(
        std::make_pair(
            filePath,
            animationGroupPtr
        )
    );

    return true;
}

Framework::Sprite::AnimationMetaData Framework::Sprite::AnimationGroupManager::parseAnimationMetaData(tinyxml2::XMLElement* animationRootElement)
{
    AnimationMetaData parsedData;
    parsedData.framesBetweenAnimationCells = animationRootElement->UnsignedAttribute("framesBetweenCells");
    parsedData.animationCellCount = animationRootElement->UnsignedAttribute("cellCount");

    return parsedData;
}

Framework::Sprite::SpriteTextureCoordinates Framework::Sprite::AnimationGroupManager::parseAnimationCellData(tinyxml2::XMLElement* spriteElement, unsigned int textureAtlasWidth, unsigned int textureAtlasHeight)
{
    //note: need to convert from absolute pixel coordinates (stored in the xml) to UV coordinates
    //(which are between 0 and 1)
    unsigned int x = spriteElement->UnsignedAttribute("x");
    unsigned int y = spriteElement->UnsignedAttribute("y");
    unsigned int spriteWidth = spriteElement->UnsignedAttribute("w");
    unsigned int spriteHeight = spriteElement->UnsignedAttribute("h");

    glm::vec2 NDCBottomLeftCoord(x / textureAtlasWidth, y / textureAtlasHeight);
    glm::vec2 NDCBottomRightCoord((x + spriteWidth) / textureAtlasWidth, y / textureAtlasHeight);
    glm::vec2 NDCTopLeftCoord(x / textureAtlasWidth, (y + spriteHeight) / textureAtlasHeight);
    glm::vec2 NDCTopRightCoord((x + spriteWidth) / textureAtlasWidth, (y + spriteHeight) / textureAtlasHeight);

    //need to figure out which order to use these 4 coordinate points
    //also, may need to reconcile coordinate systems between TexturePacker and OpenGL UV Coords
    //x, y
    //x+width, y
    //x, y+width
    //x+width, y+width
    SpriteTextureCoordinates coordinates;
    coordinates.textureCoordinate1 = NDCBottomLeftCoord; 
    coordinates.textureCoordinate2 = NDCBottomRightCoord; 
    coordinates.textureCoordinate3 = NDCTopLeftCoord;
    coordinates.textureCoordinate4 = NDCTopRightCoord;

    return coordinates;
}
