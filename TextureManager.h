#pragma once
#include <map>
#include "Structs.h"
#include "WICTextureLoader\WICTextureLoader.h"
#include <string>
class TextureManager
{
public:
	TextureManager();
	void createManager(ID3D11Device* pd3dDevice){
		pDevice = pd3dDevice;
	};
	HRESULT createTexture(std::wstring* name);
	Texture* getTexture(std::wstring* name);
	void createShipTexture(ShipTexture* shipTxt);
	
	~TextureManager();
private:
	Texture* txtList;
	ID3D11Device* pDevice;
};

