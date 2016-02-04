#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <framework/scenegraph/scenenode.h>

#include <memory>
#include <unordered_map>

class SceneGraph
{
    private:
        SceneNode rootSceneNode;
        std::unordered_map<int, std::shared_ptr<SceneNode>> sceneNodes;
    public:
        SceneGraph();
        const SceneNode& getRootSceneNode() const;
        std::shared_ptr<SceneNode> getSceneNodeByID(unsigned int nodeID) const;
};

#endif
