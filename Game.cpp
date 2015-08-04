#include "Game.h"
#define MILLISECONDS /1000
#define WINKEY_X 88
#define WINKEY_Z 90
#define CAMERA_SPEED .0125
#define FRAME_TIME .016
extern HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

struct mouseStatus{
	bool lClick = false;
	bool rClick = false;
	Point pos;
};

Ship p;
mouseStatus mouse;
Texture tstTexture;
Game::Game(){

}


void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);
void compileShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* s);
HRESULT loadTextures(ID3D11Device* pd3dDevice, Texture* txt);
void createTexture(ID3D11Device* pd3dDevice, ID3D11Texture2D* tex, int w, int h);

HRESULT Game::init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, int w, int h){
	screenH = h;
	screenW = w;
	compileShader(pd3dDevice,context,&shader);
	loadTextures(pd3dDevice, &tstTexture);
	initObjects(pd3dDevice,context,&shader);
	return S_OK;
}



void compileShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* s){
	ID3DBlob* pVSBlob = nullptr;
	CompileShaderFromFile(L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob);
	pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &s->pVertexShader);
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &s->pVertexLayout);
	pVSBlob->Release();
	
	ID3DBlob* pPSBlob = nullptr;
	CompileShaderFromFile(L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob);
	pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &s->pPixelShader);
	pPSBlob->Release();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(cbCamera);
	pd3dDevice->CreateBuffer(&bd, nullptr, &s->pCbCameraBuffer);

	bd.ByteWidth = sizeof(cbModelData);
	pd3dDevice->CreateBuffer(&bd, nullptr, &s->pCbModelMatBuffer);
}


static int data[256 * 256];
HRESULT loadTextures(ID3D11Device* pd3dDevice, Texture* txt){
	for (int i = 0; i < 256 * 256; i++){
		if (i % 2 == 0){
			data[i] = 0xFF0000FF;
		}
		else{
			data[i] = 0x0000FFFF;
		}
	}

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = 256;
	desc.Height = 256;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = static_cast<UINT>(256 * sizeof(int));
	initData.SysMemSlicePitch = static_cast<UINT>(0);

	HRESULT result;
	result = pd3dDevice->CreateTexture2D(&desc, &initData, &txt->texture);
	
	
	result = pd3dDevice->CreateShaderResourceView(txt->texture, nullptr,&txt->ptextureResView);
		

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;


	result = pd3dDevice->CreateSamplerState(&sampDesc, &txt->psamplerState);
	return result;
}


void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	p.create(pd3dDevice, context, shader);
	p.setScale(5, 5, 1);
	p.setTexture(&tstTexture);
}

void Game::onKeyPressed(WPARAM key){
	switch (key){
		case VK_LEFT:
			camera.displace(CAMERA_SPEED, 0, 0);
			break;
		case VK_RIGHT:
			camera.displace(-CAMERA_SPEED, 0, 0);
			break;
		case VK_UP:
			camera.displace(0, -CAMERA_SPEED, 0);
			break;
		case VK_DOWN:
			camera.displace(0, CAMERA_SPEED, 0);
			break;
		case WINKEY_X:
			if (camera.getOrigin()->m128_f32[2] <= 1){
				return;
			}
			camera.displace(0, 0, -.25f);
			break;
		case WINKEY_Z:
			camera.displace(0, 0, .25f);
			break;

	}
}

void Game::onFrame(ID3D11DeviceContext*  context){
	if (mouse.lClick && mouse.rClick){
		
	}
	else if (mouse.lClick){
		Vec3 mouseInWorld;
		toWorld(&mouse.pos, &mouseInWorld);
		Vec3 force = (mouseInWorld - *p.getPosition() ) / 100;
		p.applyForce(&force);
	}
	else if (mouse.rClick){
		p.setPosition(0, 0, 0);
	}
	cbCamera camUpdate;
	camera.fillOutCb(&camUpdate);
	context->UpdateSubresource(shader.pCbCameraBuffer, 0, nullptr, &camUpdate, 0, 0);
	
	p.calculateVelocity(FRAME_TIME);
	Vec3 displace = p.getVelocity() * FRAME_TIME;
	p.displace(displace.x,displace.y,displace.z);
	p.draw(FRAME_TIME);
	p.resetFrame();
}

void Game::toWorld(const Point* c, Vec3* out){
	Point scConvert;
	scConvert.x = ( (c->x / screenW) - .5f)*2;
	scConvert.y = ( .5f - (c->y / screenH)) * 2;
	
	float camDist = ((Vec3*)camera.getOrigin())->z;
	float focus = camera.getFocusDistance();

	out->x = (scConvert.x / focus)*(focus + camDist);
	out->y = (scConvert.y / focus)*(focus + camDist);
	out->z = 0;
}


void Game::mouseMoved(Point* c){

};

void Game::leftCD(Point* c){
	mouse.lClick = true;
	mouse.pos = *c;
};

void Game::leftCU(Point* c){
	mouse.lClick = false;
	mouse.pos = *c;
};

void Game::rightCU(Point* c){
	mouse.rClick = false;
	mouse.pos = *c;
};

void Game::rightCD(Point* c){
	mouse.rClick = true;
	mouse.pos = *c;
};


Game::~Game()
{

}
