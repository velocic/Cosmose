#version 330
uniform sampler2D tex;
in vec2 fragmentUVCoordinate;
out vec4 finalColor;

void main()
{
    finalColor = texture(tex, fragmentUVCoordinate);
}
