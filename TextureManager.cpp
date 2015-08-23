#include "TextureManager.h"
#define SHIPFOLDER "ships"


std::map<std::wstring, Texture*> textureMap;

static TextureManager manager;
TextureManager* TextureManager::getManager(){
	return &manager;
}

TextureManager::TextureManager()
{
}

HRESULT TextureManager::createTexture(std::wstring* name){
	HRESULT result;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	Texture* newTexture = new Texture();
	result = pDevice->CreateSamplerState(&sampDesc, &newTexture->psamplerState);
	assert(result == S_OK);
	result = DirectX::CreateWICTextureFromFile(pDevice, name->c_str(), (ID3D11Resource**)&newTexture->texture, &newTexture->ptextureResView, 0);
	assert(result == S_OK);
	newTexture->path = new std::wstring(*name);
	textureMap[*name] = newTexture;
	TM_PRINTF("Created Texture: ");
	TM_PRINTF(std::string(name->begin(), name->end()).c_str());
	TM_PRINTF("\n");

	return result;
}

void TextureManager::createShipTexture(ShipTexture* shipTxt){
	createTexture(shipTxt->shipText->path);
	createTexture(shipTxt->shipNormal->path);
	shipTxt->shipText = getTexture(shipTxt->shipText->path);
	shipTxt->shipNormal = getTexture(shipTxt->shipNormal->path);
}

Texture* TextureManager::getTexture(std::wstring* path){
	return textureMap[*path];
}






TextureManager::~TextureManager()
{

}
