#ifndef SOLID_SPHERE_H_INCLUDED
#define SOLID_SPHERE_H_INCLUDED

#include "DrawableBase.h"

class SolidSphere : public DrawableBase<SolidSphere>
{
public:
	SolidSphere(Graphics& gfx, float radius);
	~SolidSphere() = default;

	SolidSphere(const SolidSphere& other) = default;
	SolidSphere(SolidSphere&& other) = default;
	SolidSphere& operator=(const SolidSphere& other) = default;
	SolidSphere& operator=(SolidSphere&& other) = default;

public:
	void Update(float dt) noexcept override;
	void SetPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };

};

#endif // !SOLID_SPHERE_H_INCLUDED