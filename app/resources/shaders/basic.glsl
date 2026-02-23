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
    TexCoords = vec2(aTexCoords.x, 1.0 - aTexCoords.y);

    gl_Position = P * V * M * vec4(aPos, 1.0);
}

//#shader fragment

#version  330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D DiffuseTexture;

//uniform vec3 LightPos;
//uniform vec3 ViewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shi;
};

struct DirLight {
    vec3 dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 pos;
    vec3 clq;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform Material material;
uniform bool blin;

vec3 DirLightCalculation(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 L = normalize(-light.dir);
    float diff = max(dot(normal, L), 0.0f);
    vec3 R = reflect(-L, normal);
    float spec = 0.0f;


    if (blin) {
        vec3 H = normalize(L + viewDir);
        spec = pow(max(dot(viewDir, H), 0.0f), material.shi);
    } else {
        spec = pow(max(dot(viewDir, R), 0.0f), material.shi);
    }

    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = spec * light.specular;

    return ambient + diffuse + specular;
}

vec3 PointLightCalculation(PointLight light, vec3 normal, vec3 viewDir,  vec3 fragPos) {
    vec3 L = normalize(light.pos - fragPos);
    float diff = max(dot(normal, L), 0.0f);
    vec3 R = reflect(-L, normal);
    float spec = 0.0f;

    if (blin) {
        vec3 H = normalize(L + viewDir);
        spec = pow(max(dot(H, normal), 0.0f), material.shi);
    } else {
        spec = pow(max(dot(viewDir, R), 0.0f), material.shi);
    }

    float d = length(light.pos - fragPos);
    float att = 1.0f / (light.clq.x + light.clq.y * d + light.clq.z * d * d);

    vec3 ambient = att * light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = att * light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = att * light.specular * spec * texture(material.specular, TexCoords).rgb;

    return ambient + diffuse + specular;
}

void main() {
//    vec3 color = texture(DiffuseTexture, TexCoords).rgb;

    // ambient
//    vec3 ambient = 0.2 * color;
//
//    // diffuse
    vec3 N = normalize(Normal);
//    vec3 L = normalize(LightPos - FragPos);
//    float diff = max(dot(N, L), 0.0f);
//    vec3 diffuse = diff * color;
//
//    // specular
    vec3 V = normalize(ViewPos - FragPos);
//    vec3 R = reflect(-L, N);
//    float spec = pow(max(dot(V, R), 0.0f), 32);
//    vec3 specular = spec * vec3(0.5);
//
//    vec3 result = ambient + diffuse + specular;

    vec3 result = DirLightCalculation(dirLight, N, V);
    result += PointLightCalculation(pointLight, N, V, FragPos);

    FragColor = vec4(result, 1.0);
}