#include "Scene.h"


int sum(int num){
	int res = 0;
	for (int i = num; i > 0; i--, num--){
		res += num;
	}
	return res;
}
const int trisH = 5;
const int shipAmount = sum(trisH);
Ship* ships = new Ship[shipAmount + 1];


Scene::Scene(){
	
}

void Scene::createScene(TextureManager* texture, ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	std::wstring txtName = L"ships/F5S1.png";
	texture->createTexture(&txtName);
	int count = 0;
	int h = 3;
	for (int i = 0; i <= trisH; i++){
		float startX = -h * (i / 2.0);
		float startY = i * h;
		for (int b = 0; b < i; b++){
			ships[count++] = Ship(txtName.c_str(), txtName.c_str(), &Vec3{ startX + b*h, startY, 1 });
		}
	}
	ships[shipAmount - 1] = Ship(txtName.c_str(), txtName.c_str(), &Vec3{0,-2,1 });

	for (int i = 0; i < shipAmount; i++){
		ships[i].create(pd3dDevice,context,shader);
		ships[i].setTexture(texture->getTexture(&txtName));
		ships[i].mulScale(3, 3, 1);
		registerObject(&ships[i]);
	}
	
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
	return &ships[shipAmount -1];

}


Scene::~Scene()
{
}
