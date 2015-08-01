#pragma once
#include <d3d11_1.h>
#include "Structs.h"
#include "Ship.h"
#include "Plane.h"
#include "PhysObj.h"
#include "Camera.h"
#include "Planet.h"
#include "PlaneDrawable.h"

class Game
{
public:
	Game();
	HRESULT		  init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, int w, int h);
	void		  onFrame(ID3D11DeviceContext*  context);
	void		  mouseMoved(Click* c);
	void		  leftCD(Click* c);
	void		  leftCU(Click* c);
	void		  rightCU(Click* c);
	void		  rightCD(Click* c);
	~Game();
private:
	int			  screenW;
	int			  screenH;
	Shader		  shader;
	Camera   	  camera;
	SYSTEMTIME 	  prevFrame;
	void		  toWorld(Click* c, Vec3* out);
};

