uniform float time;
uniform sampler2D texture;
uniform sampler2D noise;
uniform sampler2D noise2;

void main(void)
{
    vec2 uv = gl_TexCoord[0].xy; // get the texture coordinates
    float scroll = 0.05;
    float scroll2 = -0.05;
    float distorsion = 0.05; // the amount of distorsion

    vec3 noise_ = texture2D(noise, uv + scroll * time).rgb; // get the noise value
    vec3 noise2_ = texture2D(noise2, uv + scroll2 * time).rgb; // get the second noise value
    vec3 color = texture2D(texture, uv + noise_.y * distorsion + noise2_.xy * distorsion).rgb; // get the color value
    if (noise2_.y * noise_.y > 0.4)
        color.rgb += noise_ * noise2_; // add the noise value to the color value
    gl_FragColor = vec4(color, 1.0); // set the color of the pixel

}