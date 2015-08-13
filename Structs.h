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



#define FRAME_TIME .0016

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
};

struct Texture{
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* ptextureResView = nullptr;
	ID3D11SamplerState* psamplerState = nullptr;
	std::wstring* path;
};

struct ShipTexture{
	Texture* shipText;
	Texture* shipNormal;
};


struct Point{
	Point(){}
	Point(double xx, double yy){
		x = xx;
		y = yy;
	};
	double x;
	double y;
};

struct Rect{
	float l;
	float t;
	float r;
	float b;
};

union RectU{
	Rect r;	//ltrb
	float f[4]; 
	//Point p[2] = {(0,0),(0,0)};
};

struct Vec3{
	Vec3(){}
	Vec3(float xx, float yy, float zz){
		x = xx;
		y = yy;
		z = zz;
	}
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

static Vec3 tUnitVec(Vec3* vec){
	float mag = vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
	mag = sqrtf(mag);
	Vec3 unit = *vec / mag;
	return unit;
}

static float vecMagSqr(Vec3* vec){
	return  vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
}

static float vecMag(Vec3* vec){
	float magsqr = vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
	return sqrtf(magsqr);
}

static float getDistance(const Vec3* p1, const Vec3* p2){
	Vec3 diff = *const_cast<Vec3*>(p1) - *const_cast<Vec3*>(p2);
	return vecMag(&diff);
}

static Point solveQuadratic(double a, double b, double c){
	double d = (b*b) - (4 * a*c);
	double det = sqrt(d);
	double res1 = (-b + det) / (2 * a);
	double res2 = (-b - det) / (2 * a);
	Point p(res1, res2);
	return p;
}