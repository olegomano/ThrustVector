#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>



struct Shader{
	ID3D11VertexShader*     pVertexShader = nullptr;
	ID3D11PixelShader*      pPixelShader = nullptr;
	ID3D11Buffer*			pCbModelMatBuffer = nullptr;
	ID3D11Buffer*			pCbCameraBuffer = nullptr;
	ID3D11InputLayout*      pVertexLayout = nullptr;
};

struct cbCamera{
	DirectX::XMMATRIX		camMat;
	float		            perpspectiveData[4];
};

struct cbModelData{
	DirectX::XMMATRIX	    modelMat;
	float				    scale[4];
	float                   uv[2];
};

struct Click{
	float x;
	float y;
};

struct Vec3{
	float x = 0;
	float y = 0;
	float z = 0;

	inline Vec3 operator+(Vec3 f1){
		Vec3 f;
		f.x = x + (f1).x;
		f.y = y + (f1).y;
		f.z = z + (f1).z;
		return f;
	}

	inline Vec3 operator-(Vec3 f1){
		Vec3 f;
		f.x = x - (f1).x;
		f.y = y - (f1).y;
		f.z = z - (f1).z;
		return f;
	}

	inline void operator++(){
		x++;
		y++;
		z++;
	}

	inline Vec3 operator*(Vec3 f){
		Vec3 nV;
		nV.x = x * (f).x;
		nV.y = y * (f).y;
		nV.z = z * (f).z;
		return nV;
	}

	inline Vec3 operator*(float f){
		Vec3 nV;
		nV.x = x * f;
		nV.y = y * f;
		nV.z = z * f;
		return nV;
	}

	inline Vec3 operator/(float f){
		Vec3 nV;
		nV.x = x / f;
		nV.y = y / f;
		nV.z = z / f;
		return nV;
	}
};


