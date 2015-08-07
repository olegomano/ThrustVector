#include "Game.h"
#define MILLISECONDS /1000
#define WINKEY_X 88
#define WINKEY_Z 90
#define CAMERA_SPEED .0125
#define FRAME_TIME .016

extern HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
using namespace std;

struct mouseStatus{
	bool lClick = false;
	bool rClick = false;
	Point pos;
};

mouseStatus mouse;
Game::Game(){

}


void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);
void compileShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* s);
 
HRESULT Game::init(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, int w, int h){
	screenH = h;
	screenW = w;
	textureManager.createManager(pd3dDevice);
	compileShader(pd3dDevice,context,&shader);
	initObjects(pd3dDevice,context,&shader);
	currentScene.createScene(&textureManager, pd3dDevice, context, &shader);
	return S_OK;
}



void compileShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* s){
	ID3DBlob* pVSBlob = nullptr;
	CompileShaderFromFile(L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob);
	pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &s->pVertexShader);
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &s->pVertexLayout);
	pVSBlob->Release();
	
	ID3DBlob* pPSBlob = nullptr;
	CompileShaderFromFile(L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob);
	pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &s->pPixelShader);
	pPSBlob->Release();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(cbCamera);
	pd3dDevice->CreateBuffer(&bd, nullptr, &s->pCbCameraBuffer);

	bd.ByteWidth = sizeof(cbModelData);
	pd3dDevice->CreateBuffer(&bd, nullptr, &s->pCbModelMatBuffer);
}


void initObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){

}

void Game::onKeyPressed(WPARAM key){
	switch (key){
		case VK_LEFT:
			camera.displace(CAMERA_SPEED, 0, 0);
			break;
		case VK_RIGHT:
			camera.displace(-CAMERA_SPEED, 0, 0);
			break;
		case VK_UP:
			camera.displace(0, -CAMERA_SPEED, 0);
			break;
		case VK_DOWN:
			camera.displace(0, CAMERA_SPEED, 0);
			break;
		case WINKEY_X:
			if (camera.getOrigin()->m128_f32[2] <= 1){
				return;
			}
			camera.displace(0, 0, -.25f);
			break;
		case WINKEY_Z:
			camera.displace(0, 0, .25f);
			break;

	}
}

void Game::onFrame(ID3D11DeviceContext*  context){
	if (mouse.lClick && mouse.rClick){

	}
	else if (mouse.lClick){
		Vec3 mouseInWorld;
		toWorld(&mouse.pos, &mouseInWorld);
		Vec3 force = (mouseInWorld - *currentScene.getPlayerShip()->getPosition()) / 100;
		currentScene.getPlayerShip()->applyForce(&force);
	}
	else if (mouse.rClick){

	}
	cbCamera camUpdate;
	camera.fillOutCb(&camUpdate);
	context->UpdateSubresource(shader.pCbCameraBuffer, 0, nullptr, &camUpdate, 0, 0);
	vector<PhysObjBase*>*  physList = currentScene.getPhysObjList();
	vector<DrawableBase*>* drawList = currentScene.getDrawList();
	vector<Ship*>*		   shipList = currentScene.getShipList();

	for (int i = 0; i < physList->size(); i++){
		(*physList)[i]->calculateVelocity(FRAME_TIME);
		(*physList)[i]->resetFrame();
	}

	for (int i = 0; i < shipList->size(); i++){
		Vec3 displace = (*shipList)[i]->getVelocity() * FRAME_TIME;
		(*shipList)[i]->displace(displace.x, displace.y, displace.z);
	}

	for (int i = 0; i < drawList->size(); i++){
		(*drawList)[i]->draw(FRAME_TIME);
	}
}

void Game::toWorld(const Point* c, Vec3* out){
	Point scConvert;
	scConvert.x = ( (c->x / screenW) - .5f)*2;
	scConvert.y = ( .5f - (c->y / screenH)) * 2;
	
	float camDist = ((Vec3*)camera.getOrigin())->z;
	float focus = camera.getFocusDistance();

	out->x = (scConvert.x / focus)*(focus + camDist);
	out->y = (scConvert.y / focus)*(focus + camDist);
	out->z = 0;

	out->x -= camera.getOrigin()->m128_f32[0];
	out->y -= camera.getOrigin()->m128_f32[1];

}


void Game::mouseMoved(Point* c){

};

void Game::leftCD(Point* c){
	mouse.lClick = true;
	mouse.pos = *c;
};

void Game::leftCU(Point* c){
	mouse.lClick = false;
	mouse.pos = *c;
};

void Game::rightCU(Point* c){
	mouse.rClick = false;
	mouse.pos = *c;
};

void Game::rightCD(Point* c){
	mouse.rClick = true;
	mouse.pos = *c;
};


Game::~Game()
{

}
