#ifndef POINT_LIGHT_H_INCLUDED
#define POINT_LIGHT_H_INCLUDED

#include "Graphics.h"
#include "Drawable/SolidSphere.h"
#include "Bindable/ConstantBuffers.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.5f);
	~PointLight() = default;

	PointLight(const PointLight& other) = default;
	PointLight(PointLight&& other) = default;
	PointLight& operator=(const PointLight& other) = default;
	PointLight& operator=(PointLight&& other) = default;

public:
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
	void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);
	void Bind(Graphics& gfx,DirectX::FXMMATRIX view) const noexcept;

private:
	struct PointLightCBuf
	{
		alignas(16)DirectX::XMFLOAT3 pos;
		alignas(16)DirectX::XMFLOAT3 ambient;
		alignas(16)DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};

private:
	PointLightCBuf cbData;
	mutable SolidSphere mesh;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;

};

#endif // !POINT_LIGHT_H_INCLUDED
