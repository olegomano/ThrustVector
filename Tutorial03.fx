cbuffer cbModelData : register( b0 ){
	matrix modelMat;
	float4 scale;
	float2 uv;
};

cbuffer cbCamera : register ( b1 ){
	matrix camMat;
	float4 perspectiveData; // near, far, focus
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
	float4 worldPos = mul(modelMat, Pos);
	float4 camSpace = mul(camMat, worldPos);
	float4 finalPos = camSpace;
	finalPos[0] = (perspectiveData[2] * finalPos[0]) / (finalPos[2] + perspectiveData[2]);
	finalPos[1] = (perspectiveData[2] * finalPos[1]) / (finalPos[2] + perspectiveData[2]);
	finalPos[2] = finalPos[2] / perspectiveData[1];
	return finalPos;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0f, .5f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
}
