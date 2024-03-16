/* WITHOUT NORMAL MAP: */

// uniform sampler2D texture;
// uniform vec2 lightPos;

// void main(void)
// {
//     vec2 uv = gl_FragCoord.xy; // current position
//     vec4 color = texture2D(texture, gl_TexCoord[0].xy); // color of the current position
//     float d = distance(uv, vec2(lightPos.x, lightPos.y - 50.0)); // distance from the current position to the light

//     gl_FragColor = vec4(color.r, color.g, color.b, 70.0 / d); // final color
// }


/* WITH NORMAL MAP: */

uniform sampler2D texture; // color map
uniform sampler2D normalMap; // normal map
uniform vec2 lightPos; // light position

void main(void)
{
    vec3 crntPos = vec3(gl_FragCoord.xy, 0.0); // current position
    vec3 lightPos = vec3(lightPos, 70.0); // light position
    vec3 lightVec = (lightPos - crntPos); // vector from the current position to the light
    // intensity of the light w/ respect to the distance
    float d = length(lightVec); // distance from the current position to the light
    float intern = 100.0 / d; // intensity of the light
    // ambient lighting
    float ambient = 0.5;
    // Normals are mapped from the range [0, 1] to [-1, 1]
    vec3 normal = normalize(texture2D(normalMap, gl_TexCoord[0].xy).rgb * 2.0 - 1.0); // normalizing the normal map
    vec3 lightDir = normalize(lightVec); // normalizing the light direction
    float diffuse = max(dot(normal, lightDir), 0.0); // diffuse lighting
    gl_FragColor = (texture2D(texture, gl_TexCoord[0].xy) * (diffuse * intern + ambient)); // final color
}