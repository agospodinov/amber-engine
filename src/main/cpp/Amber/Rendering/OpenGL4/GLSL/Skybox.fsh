#version 130

uniform samplerCube mdl_CubeTexture;
in vec3 fwd_TexCoord;
out vec4 out_FragColor;

void main(void)
{
    out_FragColor = textureCube(mdl_CubeTexture, fwd_TexCoord);
}
