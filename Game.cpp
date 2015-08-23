#include "Game.h"
#define MILLISECONDS /1000
#define NANOSECONDS /1000000000
#define NANO_TO_MILLIS /1000000
#define FRAMETIME 3.222e7
#define WINKEY_X 88
#define WINKEY_Z 90
#define CAMERA_SPEED .5125
#define PHYS_TIME_STEPS 8

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
	textureManager.createManager(pd3dDevice,context);
	compileShader(pd3dDevice,context,&shader);
	initObjects(pd3dDevice,context,&shader);
	currentScene.createScene(&textureManager, pd3dDevice, context, &shader);
	camera.setFollowObj(currentScene.getPlayerShip());
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
			camera.displace(-CAMERA_SPEED, 0, 0);
			break;
		case VK_RIGHT:
			camera.displace(CAMERA_SPEED, 0, 0);
			break;
		case VK_UP:
			camera.displace(0, CAMERA_SPEED, 0);
			break;
		case VK_DOWN:
			camera.displace(0, -CAMERA_SPEED, 0);
			break;
		case WINKEY_X:
			if (camera.getOrigin()->z >= -.05){
				return;
			}
			camera.displace(0, 0, 1.25f);
			break;
		case WINKEY_Z:
			camera.displace(0, 0, -1.25f);
			break;

	}
}
auto lFrame = std::chrono::high_resolution_clock::now();
bool first = true;

double fpsTime = 0;
int frameCount = 0;

void Game::onFrame(ID3D11DeviceContext*  context){
	auto tFrame = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(tFrame - lFrame).count();
	const double dt = (double)duration NANOSECONDS;
	fpsTime += dt;
	frameCount++;
	if (fpsTime > 1){
		TM_PRINTF("Fps: %d \n",frameCount);
		frameCount = 0;
		fpsTime = 0;
	}

	lFrame = tFrame;
	if (duration > FRAMETIME && !first){
		int lag = 1;
	}
	first = false;
	if (mouse.lClick && mouse.rClick){

	}
	else if (mouse.lClick){
		Vec3 mouseInWorld;
		toWorld(&mouse.pos, &mouseInWorld);
		Vec3 force = (*const_cast<Vec3*>(currentScene.getPlayerShip()->getPosition()) - mouseInWorld) * 3000000.0*PHYS_TIME_STEPS;
		force.x *= -1;
		currentScene.getPlayerShip()->applyForce(&force);
	}
	else if (mouse.rClick){

	}

	
	vector<PhysObjBase*>*  physList = currentScene.getPhysObjList();
	vector<DrawableBase*>* drawList = currentScene.getDrawList();
	vector<Ship*>*		   shipList = currentScene.getShipList();
	vector<ForceGenBase*>* fgenList = currentScene.getForceGenList();

	for (int i = 0; i < PHYS_TIME_STEPS; i++){

		for (unsigned int i = 0; i < fgenList->size(); i++){
			for (unsigned int b = 0; b < physList->size(); b++){
				(*fgenList)[i]->applyForce((*physList)[b]);
			}
		}

		for (unsigned int i = 0; i < physList->size(); i++){
			(*physList)[i]->calculateVelocity(dt / PHYS_TIME_STEPS);
			(*physList)[i]->resetFrame();
		}

		for (unsigned int i = 0; i < shipList->size(); i++){
			(*shipList)[i]->move(dt/PHYS_TIME_STEPS);
		}

		for (unsigned int i = 0; i < physList->size(); i++){
			for (unsigned int b = 0; b < physList->size(); b++){
				if (b != i){
					if ((*physList)[i]->checkCollision((*physList)[b])){
						collisions.push(Collision((*physList)[b], (*physList)[i]));
					}
				}
			}
		}

		for (unsigned int i = 0; i < physList->size(); i++){
			(*physList)[i]->clearCollisionList();
			(*physList)[i]->resetFrame();
		}

		while (!collisions.empty()){
			collisions.top().resolveCollision(dt / PHYS_TIME_STEPS);
			collisions.pop();
		}
	}

	camera.updateCameraPosition(dt);
	cbCamera camUpdate;
	camera.fillOutCb(&camUpdate);
	context->UpdateSubresource(shader.pCbCameraBuffer, 0, nullptr, &camUpdate, 0, 0);

	for (unsigned int i = 0; i < drawList->size(); i++){
		(*drawList)[i]->draw(dt);
	}
	for (unsigned int i = 0; i < physList->size(); i++){
		(*physList)[i]->clearCollisionList();
		(*physList)[i]->resetFrame();
	}
	
	float sleepDuration = (FRAMETIME - duration)NANO_TO_MILLIS;
	if (sleepDuration > 0){
		Sleep(sleepDuration);
	}
	

}

void Game::toWorld(const Point* c, Vec3* out){
	Point scConvert;
	scConvert.x = ( (c->x / screenW)*2) - 1;
	scConvert.y = ( (c->y / screenH)*2) - 1;
	
	double camDist = -camera.getOrigin()->z;
	double focus = camera.getFocusDistance();
	TM_PRINTF("focus/camdist %f %f \n", focus,camDist);
	TM_PRINTF("In Screen Space: %f, %f\n", scConvert.x, scConvert.y);
	TM_PRINTF("Camera Position: %f %f %f \n", camera.getOrigin()->x, camera.getOrigin()->y, camera.getOrigin()->z);
	out->x = ((scConvert.x)*(focus + camDist))/focus;
	out->y = ((scConvert.y)*(focus + camDist))/focus;
	out->z = 0;

	out->x += camera.getOrigin()->x;
	out->y += camera.getOrigin()->y;
	TM_PRINTF("Converted Screen To World: %f, %f, %f %f \n", c->x,c->y,out->x,out->y);
	double distanceTCam = getDistance(out, camera.getOrigin());
	TM_PRINTF("Distnace from click to camera: %f \n", distanceTCam);
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
