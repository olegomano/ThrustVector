#include "Scene.h"

const int shipAmount = 2;
Ship ships[shipAmount] = { Ship(), Ship(L"ships/F5S1.png", L"ships/F5S1.png", &Vec3(1,1,0)) };


Scene::Scene()
{
	
}

void Scene::createScene(TextureManager* texture, ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	std::wstring txtName = L"ships/F5S1.png";
	texture->createTexture(&txtName);
	for (int i = 0; i < shipAmount; i++){
		ships[i].create(pd3dDevice,context,shader);
		ships[i].setTexture(texture->getTexture(&txtName));
		drawableList.push_back(&ships[i]);
		physObjList.push_back(&ships[i]);
		shipList.push_back(&ships[i]);
	}
	
}

Ship* Scene::getPlayerShip(){
	return ships;

}


Scene::~Scene()
{
}
