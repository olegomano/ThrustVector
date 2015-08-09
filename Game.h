#pragma once
#include <d3d11_1.h>
#include "Structs.h"
#include "PlaneDrawable.h"
#include "Ship.h"
#include "Camera.h"
#include "WICTextureLoader\WICTextureLoader.h"
#include "TextureManager.h"
#include <vector>
#include "Scene.h"


class Game
{
public:
	Game();
	HRESULT		   init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, int w, int h);
	void		   onFrame(ID3D11DeviceContext*  context);
	void		   mouseMoved(Point* c);
	void		   leftCD(Point* c);
	void		   leftCU(Point* c);
	void		   rightCU(Point* c);
	void		   rightCD(Point* c);
	void		   onKeyPressed(WPARAM key);
	~Game();
private:
	int			   screenW;
	int			   screenH;
	Shader		   shader;
	Camera   	   camera;
	TextureManager textureManager;
	Scene		   currentScene;
	void		   toWorld(const Point* c, Vec3* out);
};

