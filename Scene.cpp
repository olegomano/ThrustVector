#include "Scene.h"


int sum(int num){
	int res = 0;
	for (int i = num; i > 0; i--, num--){
		res += num;
	}
	return res;
}
const int trisH = 10;
const int shipAmount =  sum(trisH);
Ship** ships = new Ship*[shipAmount];


Scene::Scene(){
	
}

void Scene::createScene(TextureManager* texture, ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	std::wstring txtName = L"ships/F5S4.png";
	std::wstring playerShip = L"ships/F5S2.png";
	std::wstring planetTexture = L"planets/spr_planet01.png";
	texture->createTexture(&txtName);
	texture->createTexture(&playerShip);
	texture->createTexture(&planetTexture);
	
	int count = 0;
	int h = 6;
	for (int i = 0; i <= trisH; i++){
		float startX = -h * (i / 2.0);
		float startY = i * h;
		for (int b = 0; b < i; b++){
			ships[count++] = new Ship(txtName.c_str(), txtName.c_str(), &Vec3{ startX + b*h, startY, 0 });
		}
	}
	
	ships[shipAmount - 1] = new Ship(txtName.c_str(), txtName.c_str(), &Vec3{0,-2,0 });
	for (int i = 0; i < shipAmount; i++){
		ships[i]->create(pd3dDevice,context,shader);
		ships[i]->setTexture(txtName);
		ships[i]->mulScale(1, 1, 1);
		registerObject(ships[i]);
	}
	getPlayerShip()->setTexture(playerShip);

	Planet* p = new Planet(&Vec3(100,0,0));
	p->create(pd3dDevice, context, shader);
	p->setTexture(planetTexture);
	p->mulScale(35, 35, 1);
	registerObject(p);


	Planet* p2 = new Planet(&Vec3(-100, 0, 0));
	p2->create(pd3dDevice, context, shader);
	p2->setTexture(planetTexture);
	p2->mulScale(35, 35, 1);
	registerObject(p2);

	Planet* p3 = new Planet(&Vec3(0, 100, 0));
	p3->create(pd3dDevice, context, shader);
	p3->setTexture(planetTexture);
	p3->mulScale(15, 15, 1);
	//registerObject(p3);
	
}

void Scene::registerObject(Planet* p){
	planetList.push_back(p);
	forceGeneratorList.push_back(p);
	drawableList.push_back(p);
	gameObjectList.push_back(p);
	physObjList.push_back(p);
}

void Scene::registerObject(Ship* s){
	drawableList.push_back(s);
	physObjList.push_back(s);
	shipList.push_back(s);
	gameObjectList.push_back(s);
}


void Scene::registerObject(PhysObjBase* p){
	physObjList.push_back(p);
}

Ship* Scene::getPlayerShip(){
	return ships[shipAmount -1];

}


Scene::~Scene()
{
}
