#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class SceneNode
{
    private:
        //rotation; quaternions? euler matrix?
        unsigned int nodeID;
        std::vector<std::shared_ptr> childSceneNodes;
        std::shared_ptr<SceneNode> parentSceneNode;
        glm::vec2 scaleVector;
        glm::vec2 translationVector;

    public:
        SceneNode();
        ~SceneNode();
};

#endif
