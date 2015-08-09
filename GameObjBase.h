#pragma once
#define DRAWABLE_TYPE (1 << 1)
#define PHYSOBJ_TYPE  (1 << 2)
#define HITBOX_TYPE   (1 << 3)
#define SHIP_TYPE     (1 << 4)
#define FORCEGEN_TYPE (1 << 6)
class GameObjBase{
public:
	int getType(){
		return type;
	}
protected:
	int type = 0;
private:

};