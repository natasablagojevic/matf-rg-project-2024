//#shader vertex
#version  330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
    FragPos = vec3(M * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoords = aTexCoords;

    gl_Position = P * V * M * vec4(aPos, 1.0);
}

//#shader fragment

#version  330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D DiffuseTexture;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main() {
    vec3 color = texture(DiffuseTexture, TexCoords).rgb;

    // ambient
    vec3 ambient = 0.2 * color;

    // diffuse
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightPos - FragPos);
    float diff = max(dot(N, L), 0.0f);
    vec3 diffuse = diff * color;

    // specular
    vec3 V = normalize(ViewPos - FragPos);
    vec3 R = reflect(-L, N);
    float spec = pow(max(dot(V, R), 0.0f), 32);
    vec3 specular = spec * vec3(0.5);

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}