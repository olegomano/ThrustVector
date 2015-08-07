#include "HitBoxBase.h"
using namespace std;

static vector<HitBox*>* hitboxList = new vector <HitBox*>();
int amount = 0;
HitBox::HitBox(){
	//getHiboxList()->push_back(this);

	amount++;
}

HitBox::~HitBox(){

}

vector<HitBox*>* HitBox::getHiboxList(){
	return hitboxList;
}