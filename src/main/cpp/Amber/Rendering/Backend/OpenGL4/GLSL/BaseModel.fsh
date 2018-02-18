#version 130

uniform sampler2D mdl_Diffuse;
in vec2 fwd_TexCoords;
out vec4 out_FragColor;

void main(void)
{
    out_FragColor = texture2D(mdl_Diffuse, vec2(fwd_TexCoords.s, 1.0 - fwd_TexCoords.t));
}
