#pragma once
#include <map>
#include "Structs.h"
#include "WICTextureLoader\WICTextureLoader.h"
class TextureManager
{
public:
	TextureManager();
	void createManager(ID3D11Device* pd3dDevice){
		pDevice = pd3dDevice;
	};
	void createTexture(wchar_t* name);
	Texture* getTexture(wchar_t* name);
	void createShipTexture(ShipTexture* shipTxt);
	
	~TextureManager();
private:
	Texture* txtList;
	ID3D11Device* pDevice;
};

