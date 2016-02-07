#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class SceneNode
{
    private:
        unsigned int nodeID;
        std::vector<glm::mat4> childMatrices;
        std::vector<std::shared_ptr> childSceneNodes;
        std::shared_ptr<SceneNode> parentSceneNode;
        std::unique_ptr<glm::mat4> worldMatrix;

    public:
        SceneNode(unsigned int nodeID, std::shared_ptr<SceneNode> parentSceneNode);
        void transform(glm::mat4 transformMatrix);
        glm::mat4 &attachChildMatrix();
};

#endif
