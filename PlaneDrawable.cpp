#include "PlaneDrawable.h"


struct bufferData{
	DirectX::XMFLOAT3 vert;
	float uv[2];
};

bool alloced = false;
ID3D11Buffer* pPlaneVertexBuffer = nullptr;
bufferData vertices[6];
ID3D11Buffer* getPlaneVertexBuffer(ID3D11Device* pd3dDevice){
	if (!alloced){
		
		vertices[0] = { DirectX::XMFLOAT3(-.5f, -.5f, 0.0f),{ 0, 1 }  }; //lb
		vertices[1] = { DirectX::XMFLOAT3(-.5f, .5f, 0.0f) ,{ 0, 0 }  }; //lt
		vertices[2] = { DirectX::XMFLOAT3(.5f, .5f, 0.0f)  ,{ 1, 0 }  }; //rt
			
		vertices[3] = { DirectX::XMFLOAT3(.5f, .5f, 0.0f),  { 1, 0 }  }; // rt
		vertices[4] = { DirectX::XMFLOAT3(.5f, -.5f, 0.0f), { 1, 1 }  }; // rb
		vertices[5] = { DirectX::XMFLOAT3(-.5f, -.5f, 0.0f),{ 0, 1 }  };//lb
		
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(bufferData)*6;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		pd3dDevice->CreateBuffer(&bd, &InitData, &pPlaneVertexBuffer);
		alloced = true;
	}
	return pPlaneVertexBuffer;
}


void PlaneDrawable::create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	DrawableBase::create(pd3dDevice, context, shader);
	pVertexBuffer = getPlaneVertexBuffer(pd3dDevice);
	stride = sizeof(bufferData);
	offset = 0;
}

/*
PlaneDrawable::PlaneDrawable()
{
	uvCoords[0] = 0; uvCoords[1] = 1; //lb
	uvCoords[2] = 0; uvCoords[3] = 0; //lt
	uvCoords[4] = 1; uvCoords[5] = 0, //rt

	uvCoords[6] = 0; uvCoords[7] = 1; //lb
	uvCoords[8] = 1; uvCoords[9] = 0; //rt
	uvCoords[10] = 1; uvCoords[11] = 1; //rb

}
*/
void PlaneDrawable::draw(float dt){
	
	cbModelData updateData;
	updateData.modelMat = mMatrix;
	for (int i = 0; i < 4; i++){
		updateData.scale[i] = scale[i];
	}
	
	ID3D11BlendState* d3dBlendState;
	D3D11_BLEND_DESC omDesc;
	ZeroMemory(&omDesc,	sizeof(D3D11_BLEND_DESC));
	omDesc.RenderTarget[0].BlendEnable = true;
	omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	pd3dDevice->CreateBlendState(&omDesc, &d3dBlendState);
	
	context->OMSetBlendState(d3dBlendState, 0, 0xffffffff);
	context->UpdateSubresource(shader->pCbModelMatBuffer, 0, nullptr, &updateData, 0, 0);
	context->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(shader->pVertexLayout);

	context->VSSetConstantBuffers(0, 1, &shader->pCbModelMatBuffer);
	context->VSSetConstantBuffers(1, 1, &shader->pCbCameraBuffer);

	context->VSSetShader(shader->pVertexShader, nullptr, 0);
	context->PSSetShader(shader->pPixelShader, nullptr, 0);
	
	context->PSSetShaderResources(0,1,&txt->ptextureResView);
	context->PSSetSamplers(0,1,&txt->psamplerState);

	context->Draw(6, 0);
}





PlaneDrawable::~PlaneDrawable()
{
}
