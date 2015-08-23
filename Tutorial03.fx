cbuffer cbModelData : register( b0 ){
	matrix modelMat;
	float4 scale;
};

cbuffer cbCamera : register ( b1 ){
	matrix camMat;
	float4 perspectiveData; // near, far, focus
};

struct VS_INPUT{
	float4 Pos : POSITION; 
	float2 uv : UVCOORD;
};



struct VS_OUTPUT{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

Texture2D g_Texture;
SamplerState g_samplerState;

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input)
{
	VS_OUTPUT output;
	float4 scaledPos;
	for (int i = 0; i < 4; i++){
		scaledPos[i] = input.Pos[i] * scale[i];
	}
	float4 worldPos = mul(modelMat,scaledPos);
	float4 camSpace = mul(camMat,worldPos);
	float4 finalPos = camSpace;
	finalPos[0] = (perspectiveData[2] * finalPos[0]) / (finalPos[2] + perspectiveData[2]);
	finalPos[1] = (perspectiveData[2] * finalPos[1]) / (finalPos[2] + perspectiveData[2]);
	finalPos[2] = finalPos[2] / perspectiveData[1];
	
	output.pos = finalPos;
	output.uv = input.uv;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	return g_Texture.Sample(g_samplerState,input.uv);    // Yellow, with Alpha = 1
}
