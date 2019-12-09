#ifndef PYRAMID_H_INCLUDED
#define PYRAMID_H_INCLUDED

#include "DrawableBase.h"

class Pyramid : public DrawableBase<Pyramid>
{
public:
	Pyramid(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);

	Pyramid(const Pyramid& other) = default;
	Pyramid(Pyramid&& other) = default;
	Pyramid& operator=(const Pyramid& other) = default;
	Pyramid& operator=(Pyramid&& other) = default;

public:
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;


};

#endif // !PYRAMID_H_INCLUDED
