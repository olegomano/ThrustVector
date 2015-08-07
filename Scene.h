#pragma once
#include "Structs.h"
#include "TextureManager.h"
#include <vector>
#include <string>
#include <winstring.h>
#include "Ship.h"
#include "DrawableBase.h"
#include "HitBoxBase.h"
#include "PhysObjBase.h"
class Scene
{
public:
	Scene();
	void createScene(TextureManager* manager, ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);
	Ship* getPlayerShip();
	std::vector<DrawableBase*>* getDrawList(){ return &drawableList; };
	std::vector<HitBox*>*	    getHitboxList(){ return &hitboxList; };
	std::vector<PhysObjBase*>*  getPhysObjList(){ return &physObjList; };
	std::vector<Ship*>*			getShipList(){ return &shipList; };
	void					    registerObject();
	~Scene();
protected:
	TextureManager*			   sceneTextures;
	std::vector<DrawableBase*> drawableList;
	std::vector<HitBox*>	   hitboxList;
	std::vector<PhysObjBase*>  physObjList;
	std::vector<Ship*>	       shipList;
};

