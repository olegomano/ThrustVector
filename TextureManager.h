#pragma once
#include <map>
#include "Structs.h"
#include "WICTextureLoader\WICTextureLoader.h"
#include <string>
#include <d3d11.h>
class TextureManager
{
public:
	TextureManager();
	void createManager(ID3D11Device* pd3dDevice, ID3D11DeviceContext* context){
		pDevice = pd3dDevice;
		pContext = context;
	};
	HRESULT createTexture(std::wstring* name);
	Texture* getTexture(std::wstring* name);
	void createShipTexture(ShipTexture* shipTxt);
	static TextureManager* getManager();
	~TextureManager();
private:
	Texture* txtList;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pContext;
};

