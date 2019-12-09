#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "DrawableBase.h"

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist, 
		std::uniform_real_distribution<float>& odist, 
		std::uniform_real_distribution<float>& rdist);

	Box(const Box& other) = delete;
	Box(Box&& other) = default;
	Box& operator=(const Box& other) = default;
	Box& operator=(Box&& other) = default;

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

#endif // !BOX_H_INCLUDED
