#version 430 core
layout(vertices = 3) out;


in VER_OUT {
    vec4 color;
}data_in[];

out TCS_OUT {
    vec4 color;
}data_out[];


void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 5;
        gl_TessLevelOuter[0] = 5;
        gl_TessLevelOuter[1] = 5;
        gl_TessLevelOuter[2] = 5;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    data_out[gl_InvocationID].color = data_in[gl_InvocationID].color;
}