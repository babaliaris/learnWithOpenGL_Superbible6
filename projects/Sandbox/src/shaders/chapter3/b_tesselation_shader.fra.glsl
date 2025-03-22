#version 430 core


in TES_OUT {
    vec4 color;
}data_in;


out vec4 color;

void main(void)
{
    color = data_in.color;
}