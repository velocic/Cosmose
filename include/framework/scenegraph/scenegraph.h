#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <framework/scenegraph/scenenode.h>

#include <memory>
#include <unordered_map>

class SceneGraph
{
    private:
        SceneNode rootSceneNode;
        std::unordered_map<int, std::unique_ptr<SceneNode>> sceneNodes;
    public:
        SceneGraph();
        SceneNode& getRootSceneNode() const;
        SceneNode& getSceneNodeByID(unsigned int nodeID) const;
};

#endif
