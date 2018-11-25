#version 400 core

in vec2 pass_textureCoords;
out vec4 out_Color;

uniform sampler2D textureSampler;

uniform vec4 colorMix;
uniform float mixColor;

void main(void) {

	vec4 color = texture(textureSampler, pass_textureCoords);

	if (color.a < 0.5) {

		discard;

	}

	out_Color = color;

	if (mixColor > 0.5f) {

		out_Color = mix(colorMix, out_Color, 0.5f);

	}

}