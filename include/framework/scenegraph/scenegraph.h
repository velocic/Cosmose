#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <framework/scenegraph/scenenode.h>

#include <memory>
#include <unordered_map>

namespace Framework
{
    namespace SceneGraph
    {
        class SceneGraph
        {
            private:
                SceneNode rootSceneNode;
                std::unordered_map<std::size_t, std::unique_ptr<SceneNode>> sceneNodes;

                friend SceneNode::attachChildNode(SceneNode *childNode);
            public:
                //Create a scene node at the root level, and get a handle to it
                std::size_t createSceneNode();

                //Create a scene node attached to the node with the associated nodeID
                std::size_t createSceneNode(std::size_t nodeID);

                SceneNode &getRootSceneNode() const;
                SceneNode &getSceneNodeByID(std::size_t nodeID) const;
        };
    }
}


#endif
