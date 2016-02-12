#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace Framework
{
    namespace SceneGraph
    {
        class SceneNode
        {
            private:
                std::size_t nodeID;
                std::vector<std::unique_ptr<glm::mat4>> childMatrices;
                std::vector<SceneNode *> childSceneNodes;
                SceneNode *parentSceneNode;
                std::unique_ptr<glm::mat4> worldMatrix;

                void attachChildNode(SceneNode *childNode);
            public:
                SceneNode(
                    std::size_t nodeID,
                    SceneNode &parentSceneNode
                )
                :
                    nodeID(nodeID),
                    parentSceneNode(parentSceneNode)
                {}
                void attachChildMatrix(glm::mat4 &childMatrix);
                void attachChildNode(SceneNode *childNode);
                const glm::mat4 &getWorldMatrix();
                void transform(const glm::mat4 &transformMatrix);
                void translate(const glm::vec2 &translation);
                void rotate(const glm::fquat &rotation);
                void scale(const glm::vec2 &scale);
        };
    }
}

#endif
