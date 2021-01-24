#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 posWorldspace;
in vec3 eyeDirectionCameraspace;
in vec3 lightDirectionCameraspace;
in vec3 normalCameraspace;


// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform vec4 diffuseColour;
uniform vec4 ambientColour;
uniform vec4 specularColour;

const vec3 ambientLightColour = vec3(1.0, 1.0, 1.0);
const vec3 diffuseLightColour = vec3(1.0, 1.0, 1.0);
const vec3 specularLightColour = vec3(1.0, 1.0, 1.0);

void main(){
	
	//Material properties

	vec3 textureVal = texture( textureSampler, UV).rgb;

	vec3 N = normalize( normalCameraspace );
	vec3 L = normalize( lightDirectionCameraspace );

	//Diffuse component light direction
	float costheta = clamp( dot(N, L), 0, 1);

	vec3 E = normalize( eyeDirectionCameraspace );
	vec3 R = reflect(-L, N);

	float cosalpha = clamp( dot( E, R), 0, 1);

	vec3 diffuseComponent = diffuseLightColour * diffuseColour.rgb * textureVal * costheta;
	vec3 ambientComponent = ambientLightColour * ambientColour.rgb * textureVal;
	vec3 specularComponent = specularLightColour * specularColour.rgb * pow(cosalpha, 6.0);



    color.rgb = diffuseComponent.rgb + ambientComponent.rgb + specularComponent.rgb;
    color.a = 1.0;
    
}
