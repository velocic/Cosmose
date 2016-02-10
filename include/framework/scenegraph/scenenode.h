#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class SceneNode
{
    private:
        std::size_t nodeID;
        std::vector<std::unique_ptr<glm::mat4>> childMatrices;
        std::vector<SceneNode *> childSceneNodes;
        SceneNode &parentSceneNode;
        std::unique_ptr<glm::mat4> worldMatrix;

        void attachChildNode(SceneNode *childNode);
    public:
        SceneNode(std::size_t nodeID, SceneNode &parentSceneNode)
            : nodeID(nodeID),
              parentSceneNode(parentSceneNode)
        {}
        void attachChildMatrix(glm::mat4 &childMatrix);
        void transform(glm::mat4 &transformMatrix);
};

#endif
