#version 330
layout (location = 0) in vec2 vertex;
layout (location = 1) in mat4 modelMatrix;
layout (location = 5) in vec4 colorModifier;
out vec2 fragmentUVCoordinate;
out vec4 fragmentColorModifier;

void main()
{
    fragmentUVCoordinate = vertex;
    vec4 expandedVertex = vec4(vertex, 0, 1);
    gl_Position = modelMatrix * expandedVertex;
}
