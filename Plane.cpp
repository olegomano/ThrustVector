#include "Plane.h"


Plane::Plane(){
	modelMatrix = DirectX::XMMatrixIdentity();
}

HRESULT Plane::allocBuffers(ID3D11Device* pd3dDevice){
	HRESULT hr = S_OK;
	//unsigned short indecies[] = {0,1,2,0,2,3};
	DirectX::XMFLOAT3 vertices[] =
	{
		DirectX::XMFLOAT3(-.5f,-.5f, 0.5f), //lb
		DirectX::XMFLOAT3(-.5f, .5f, 0.5f), //lt
		DirectX::XMFLOAT3( .5f, .5f, 0.5f), //rt

		DirectX::XMFLOAT3(-.5f, -.5f, 0.5f), //lb
		DirectX::XMFLOAT3( .5f,  .5f, 0.5f), //rt
		DirectX::XMFLOAT3( .5f, -.5f, 0.5f), //rb
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


inline DirectX::XMVECTOR* Plane::getRight(){
	return &modelMatrix.r[0];
}

inline DirectX::XMVECTOR* Plane::getUp(){
	return &modelMatrix.r[1];
}

inline DirectX::XMVECTOR* Plane::getNormal(){
	return &modelMatrix.r[2];
}

inline DirectX::XMVECTOR* Plane::getOrigin(){
	return &modelMatrix.r[3];
}



void Plane::draw(ID3D11DeviceContext*  context, float dt) {
	//f = m*a;
	//V 
	Vec3 displace;
	calculateDisplace(.016f,&displace);
	cbModelData updateData;
	updateData.modelMat = modelMatrix * DirectX::XMMatrixTranslation(displace.x,displace.y,displace.z);
	
	context->UpdateSubresource(shader.pCbModelMatBuffer, 0, nullptr, &updateData, 0, 0);
	context->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(shader.pVertexLayout);

	context->VSSetConstantBuffers(0, 1, &shader.pCbModelMatBuffer);
	context->VSSetConstantBuffers(1, 1, &shader.pCbCameraBuffer);

	context->VSSetShader(shader.pVertexShader, nullptr, 0);
	context->PSSetShader(shader.pPixelShader, nullptr, 0);
	context->Draw(6, 0);

	modelMatrix.r;
}

Plane::~Plane(){

}
