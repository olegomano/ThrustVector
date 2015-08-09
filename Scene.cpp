#include "Scene.h"

const int shipAmount = 2;
Ship ships[shipAmount] = { Ship(), Ship(L"ships/F5S1.png", L"ships/F5S1.png", &Vec3(4,4,0)) };


Scene::Scene(){
	
}

void Scene::createScene(TextureManager* texture, ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	std::wstring txtName = L"ships/F5S1.png";
	texture->createTexture(&txtName);
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
	return ships;

}


Scene::~Scene()
{
}
