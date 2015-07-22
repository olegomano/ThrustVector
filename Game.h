#pragma once
#include "Structs.h"
#include "Plane.h"
class Game
{
public:
	Game();
	HRESULT init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context);
	void onFrame(ID3D11DeviceContext*  context);
	~Game();
private:
	Shader shader;
};

