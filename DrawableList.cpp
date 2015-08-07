#include "DrawableBase.h"

using namespace std;
vector<DrawableBase*>* allDrawables = new vector<DrawableBase*>();
int drawableCount = 0;
DrawableBase::DrawableBase(){
	allDrawables->push_back(this);
	drawableCount++;
}

vector<DrawableBase*>* DrawableBase::getDrawableList(){
	return allDrawables;
}
