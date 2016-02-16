#include <framework/scenegraph/scenenode.h>
#include <glm/gtc/matrix_transform.hpp>

void Framework::SceneGraph::attachChildMatrix(glm::mat4 &childMatrix)
{
}

void Framework::SceneGraph::attachChildNode(SceneNode *childNode)
{
}

const glm::mat4 &Framework::SceneGraph::getWorldMatrix()
{
    return worldMatrix;
}

void Framework::SceneGraph::transform(const glm::mat4 &transformMatrix)
{
    worldMatrix *= transformMatrix;
    //decompose the translate, rotate, scale and store them?
}

void Framework::SceneGraph::translate(const glm::vec2 &translation)
{
    worldMatrix = glm::translate(worldMatrix, glm::vec3(translation, 0));
}

void Framework::SceneGraph::rotate(const glm::fquat &rotation)
{
}

void Framework::SceneGraph::scale(const glm::vec2 &scale)
{
}
