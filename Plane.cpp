#include "Plane.h"


Plane::Plane(){
	modelMatrix = DirectX::XMMatrixIdentity();
	for (int i = 0; i < 4; i++){
		scale[i] = 1;
	}
}

HRESULT Plane::allocBuffers(ID3D11Device* pd3dDevice){
	HRESULT hr = S_OK;
	//unsigned short indecies[] = {0,1,2,0,2,3};
	DirectX::XMFLOAT3 vertices[] =
	{
		DirectX::XMFLOAT3(-.5f,-.5f, 0.0f), //lb
		DirectX::XMFLOAT3(-.5f, .5f, 0.0f), //lt
		DirectX::XMFLOAT3( .5f, .5f, 0.0f), //rt

		DirectX::XMFLOAT3(-.5f, -.5f, 0.0f), //lb
		DirectX::XMFLOAT3( .5f,  .5f, 0.0f), //rt
		DirectX::XMFLOAT3( .5f, -.5f, 0.0f), //rb
	};


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DirectX::XMFLOAT3) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	stride = sizeof(DirectX::XMFLOAT3);
	offset = 0;
	return hr;

}

void Plane::setShader(Shader s){
	shader = s;
}


void Plane::rotateAboutCenter(float x, float y, float z){
	DirectX::XMMATRIX rotateX = DirectX::XMMatrixRotationX(x);
	DirectX::XMMATRIX rotateY = DirectX::XMMatrixRotationY(y);
	DirectX::XMMATRIX rotateZ = DirectX::XMMatrixRotationZ(z);

	DirectX::XMMATRIX displace = DirectX::XMMatrixTranslation(modelMatrix.r[3].m128_f32[0], modelMatrix.r[3].m128_f32[1], modelMatrix.r[3].m128_f32[2]);
	DirectX::XMMATRIX displaceB = DirectX::XMMatrixTranslation(-modelMatrix.r[3].m128_f32[0], -modelMatrix.r[3].m128_f32[1], -modelMatrix.r[3].m128_f32[2]);

	modelMatrix *= displaceB;
	modelMatrix *= rotateX;
	modelMatrix *= rotateY;
	modelMatrix *= rotateZ;
	modelMatrix *= displace;
}


void Plane::draw(ID3D11DeviceContext*  context) {
	
	cbModelData updateData;
	updateData.modelMat = modelMatrix;
	for (int i = 0; i < 4; i++){
		updateData.scale[i] = scale[i];
	}

	context->UpdateSubresource(shader.pCbModelMatBuffer, 0, nullptr, &updateData, 0, 0);
	context->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(shader.pVertexLayout);

	context->VSSetConstantBuffers(0, 1, &shader.pCbModelMatBuffer);
	context->VSSetConstantBuffers(1, 1, &shader.pCbCameraBuffer);
	
	context->VSSetShader(shader.pVertexShader, nullptr, 0);
	context->PSSetShader(shader.pPixelShader, nullptr, 0);
	context->Draw(6, 0);
}

Plane::~Plane(){

}
