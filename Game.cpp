#include "Game.h"
extern HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

Game::Game()
{

}
Plane tstPlane;
HRESULT Game::init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context){
	
	
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
	bd.ByteWidth = sizeof(Camera);
	hr = pd3dDevice->CreateBuffer(&bd, nullptr, &shader.pCbCameraBuffer);

	bd.ByteWidth = sizeof(cbModelData);
	hr = pd3dDevice->CreateBuffer(&bd, nullptr, &shader.pCbModelMatBuffer);
	if (FAILED(hr))
		return hr;
	
	
	
	if (FAILED(hr))
		return hr;
	hr = tstPlane.allocBuffers(pd3dDevice);
	if (FAILED(hr))
		return hr;
	tstPlane.setShader(shader);
	return hr;
}

void Game::onFrame(ID3D11DeviceContext*  context){
	tstPlane.draw(context);
}


Game::~Game()
{
}
