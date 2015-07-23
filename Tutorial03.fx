cbuffer cbModelData{
	matrix modelMat;
	float4 scale;
	float2 uv;
};

cbuffer cbCamera{
	matrix camMat;
	float4 perspectiveData;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
	return mul(modelMat,Pos);
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
    return float4( 1.0f, .5f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
}
