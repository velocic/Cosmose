#include <framework/scenegraph/scenegraph.h>

std::size_t Framework::SceneGraph::createSceneNode()
{
    std::size_t nodeID = sceneNodes.size();

    sceneNodes.insert(
        {
            nodeID,
            std::unique_ptr<SceneNode>(new SceneNode),
            rootSceneNode
        }
    );

    rootSceneNode.attachChildNode(sceneNodes.find(nodeID)->get());

    return nodeID;
}

std::size_t Framework::SceneGraph::createSceneNode(std::size_t parentNodeID)
{
    std::size_t childNodeID = sceneNodes.size();

    sceneNodes.insert(
        {
            childNodeID,
            std::unique_ptr<SceneNode>(new SceneNode),
            rootSceneNode
        }
    );

    (*sceneNodes.find(parentNodeID))->attachChildNode(
        sceneNodes.find(childNodeID)->get()
    );

    return childNodeID;
}

SceneNode &Framework::SceneGraph::getRootSceneNode() const
{
    return rootSceneNode;
}

SceneNode &Framework::SceneGraph::getSceneNodeByID(std::size_t nodeID) const
{
    return **(sceneNodes.find(nodeID));
}