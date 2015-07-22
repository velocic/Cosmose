#version 330
uniform sampler2D tex;
in vec2 fragmentUVCoordinate;
in vec4 fragmentColorModifier;
out vec4 finalColor;

void main()
{
    //Doing nothing with fragmentColorModifier for now
    finalColor = texture(tex, fragmentUVCoordinate);
}
