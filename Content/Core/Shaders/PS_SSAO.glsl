/**
* This work is distributed under the General Public License,
* see LICENSE for details
*
* @author Gwenna�l ARBONA
**/

/*-------------------------------------------------
	Config
/*-----------------------------------------------*/

#version 150

uniform vec3 cCamPosition;
uniform mat4 cProj;

uniform sampler2D sSceneNormal;
uniform sampler2D sSceneDepth;
uniform sampler2D sTextureNoise;
uniform sampler2D sTextureKernel;

uniform int cKernelSize;
uniform float cRadius;
uniform float cPower;


/*-------------------------------------------------
	Input / Output
/*-----------------------------------------------*/

in vec2 vUv0;
in vec3 vRay;

out vec4 pPixel;


/*-------------------------------------------------
	Helpers
/*-----------------------------------------------*/

float packColor(vec3 color)
{
    return color.r + color.g * 256.0 + color.b * 256.0 * 256.0;
}

float getDepth(vec2 coords)
{
	return packColor(texture2D(sSceneDepth, coords).rgb);
}

vec4 ssao(in mat3 system, in vec3 center)
{
	float occlusion = 0.0;

	for (int i = 0; i < cKernelSize; ++i)
	{
		vec3 samplePos = system * texture2D(sTextureKernel, vec2(i, 0)).rgb;
		samplePos = samplePos * cRadius + center;

		samplePos = center;//DEBUG
		vec4 coords = cProj * vec4(samplePos, 1.0);

		coords.xy = coords.xy * 20;//DEBUG

		coords.xy = (coords.xy + 1) / 2;
		coords.xy = clamp(coords.xy, vec2(0, 0), vec2(1, 1));
		coords.y = 1 - coords.y;
		
		return vec4(coords.x, coords.y, 0, 1);
		//return vec4(coords.x - vUv0.x, coords.y - vUv0.y, 0, 1);
		
		//float sampleDepth = getDepth(coords.xy);
		//return vec4(sampleDepth) * 10;
		
		//float rangeCheck= abs(origin.z - sampleDepth) < uRadius ? 1.0 : 0.0;
		//float rangeCheck = smoothstep(0.0, 1.0, cRadius / abs(center.z - sampleDepth));
		//occlusion += rangeCheck * step(sampleDepth, samplePos.z);
		//occlusion += (sampleDepth <= samplePos.z ? 1.0 : 0.0) * rangeCheck;
		//return vec4((samplePos.z / 20 - sampleDepth));
	}
	
	occlusion = 1.0 - (occlusion / float(cKernelSize));
	return vec4(pow(occlusion, cPower));
}


/*-------------------------------------------------
	Shader
/*-----------------------------------------------*/

void main()
{
	// Noise
	vec2 screenSize = vec2(textureSize(sSceneDepth, 0));
	vec2 rotCoords = vUv0 * screenSize / vec2(textureSize(sTextureNoise, 0));
	vec3 rotationVector = 2.0 * texture2D(sTextureNoise, rotCoords).xyz - 1.0;
	
	// World position
	float originDepth = texture2D(sSceneNormal, vUv0).a;
	vec3 viewPos = vRay * originDepth;
	vec4 worldPos = inverse(cProj) * vec4(viewPos, 1);
	
	// Normal system
	vec3 normal = texture2D(sSceneNormal, vUv0).rgb;
	vec3 tangent = normalize(rotationVector - normal * dot(rotationVector, normal));
	vec3 bitangent = cross(tangent, normal);
	mat3 system = mat3(tangent, bitangent, normal);
	
	// Calculation
	pPixel = ssao(system, vec3(worldPos));
	pPixel = worldPos;
}
