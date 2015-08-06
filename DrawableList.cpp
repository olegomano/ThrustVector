#include "DrawableBase.h"

using namespace std;
vector<DrawableBase*> allDrawables(1);
int drawableCount = 0;
DrawableBase::DrawableBase(){
	allDrawables.push_back(this);
	drawableCount++;
}

vector<DrawableBase*>* DrawableBase::getDrawableList(){
	return &allDrawables;
}
