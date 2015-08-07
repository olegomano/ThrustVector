#pragma once
#define DRAWABLE_TYPE (0 << 1)
#define PHYSOBJ_TYPE  (0 << 2)
#define HITBOX_TYPE   (0 << 3)
#define SHIP_TYPE     (0 << 4)
#define FORCEGEN_TYPE (0 << 6)
class GameObjBase{
public:
	int getType(){
		return type;
	}
protected:
	int type = 0;
private:

};