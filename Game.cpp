#include "Game.h"
#define MILLISECONDS /1000;
extern HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

struct mouseStatus{
	bool lClick = false;
	bool rClick = false;
	Click pos;
};

mouseStatus mouse;

Game::Game(){

}


void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);

HRESULT Game::init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, int w, int h){
	screenH = h;
	screenW = w;
	
	HRESULT hr = S_OK;
	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &shader.pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),pVSBlob->GetBufferSize(), &shader.pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &shader.pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;
	
	

	//create const buffers
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(cbCamera);
	hr = pd3dDevice->CreateBuffer(&bd, nullptr, &shader.pCbCameraBuffer);

	bd.ByteWidth = sizeof(cbModelData);
	hr = pd3dDevice->CreateBuffer(&bd, nullptr, &shader.pCbModelMatBuffer);
	if (FAILED(hr))
		return hr;
	
	
	
	if (FAILED(hr))
		return hr;
	if (FAILED(hr))
		return hr;
	initObjects(pd3dDevice,context,&shader);
	return hr;
}

PlaneDrawable p;
void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	p.create(pd3dDevice,context,shader);
}

Shader compileShader(){
	Shader s;
	return s;
}


void Game::onFrame(ID3D11DeviceContext*  context){
	if (mouse.lClick && mouse.rClick){

	}
	else if (mouse.lClick){
		Vec3 mouseInWorld;
		toWorld(&mouse.pos, &mouseInWorld);
	}
	else if (mouse.rClick){
	
	}
	cbCamera camUpdate;
	camera.fillOutCb(&camUpdate);
	context->UpdateSubresource(shader.pCbCameraBuffer, 0, nullptr, &camUpdate, 0, 0);
	p.draw(9);
}

void Game::toWorld(Click* c, Vec3* out){
	Click scConvert;
	scConvert.x = ( (c->x / screenW) - .5f)*2;
	scConvert.y = ( .5f - (c->y / screenH)) * 2;
	
	float camDist = ((Vec3*)camera.getPosition())->z;
	float focus = camera.getFocusDistance();

	out->x = (scConvert.x / focus)*(focus + camDist);
	out->y = (scConvert.y / focus)*(focus + camDist);
	out->z = 0;
}


void Game::mouseMoved(Click* c){

};

void Game::leftCD(Click* c){
	mouse.lClick = true;
	mouse.pos = *c;
};

void Game::leftCU(Click* c){
	mouse.lClick = false;
	mouse.pos = *c;
};

void Game::rightCU(Click* c){
	mouse.rClick = true;
	mouse.pos = *c;
};

void Game::rightCD(Click* c){
	mouse.rClick = false;
	mouse.pos = *c;
};


Game::~Game()
{

}
