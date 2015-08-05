#include "TextureManager.h"
#define SHIPFOLDER "ships"



std::map<wchar_t*, Texture> textureMap;
TextureManager::TextureManager()
{
}

void TextureManager::createTexture(wchar_t* name){
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	Texture newTexture;
	
	pDevice->CreateSamplerState(&sampDesc, &newTexture.psamplerState);
	DirectX::CreateWICTextureFromFile(pDevice, name, (ID3D11Resource**)&newTexture.texture, &newTexture.ptextureResView, 0);
	newTexture.path = name;

	textureMap[name] = newTexture;
}

void TextureManager::createShipTexture(ShipTexture* shipTxt){
	createTexture(shipTxt->shipText->path);
	createTexture(shipTxt->shipNormal->path);
	shipTxt->shipText = getTexture(shipTxt->shipText->path);
	shipTxt->shipNormal = getTexture(shipTxt->shipNormal->path);
}

Texture* TextureManager::getTexture(wchar_t* path){
	return &textureMap[path];
}






TextureManager::~TextureManager()
{
	
}
