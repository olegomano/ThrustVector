#pragma once
#include "Structs.h"
class TextureManager
{
public:
	TextureManager(int maxTexture);
	void createTexture(int id, wchar_t* path);
	~TextureManager();
private:
	Texture* txtList;
};

