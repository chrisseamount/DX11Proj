#ifndef TEST_OBJECT_H_INCLUDED
#define TEST_OBJECT_H_INCLUDED

#include "DrawableBase.h"

template<class T>
class TestObject : public DrawableBase<T>
{
public:
	TestObject(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist)
		:
		r(rdist(rng)),
		droll(ddist(rng)),
		dpitch(ddist(rng)),
		dyaw(ddist(rng)),
		dphi(odist(rng)),
		dtheta(odist(rng)),
		dchi(odist(rng)),
		chi(adist(rng)),
		theta(adist(rng)),
		phi(adist(rng))
	{}

	~TestObject() = default;

	TestObject(const TestObject& other) = default;
	TestObject(TestObject&& other) = default;
	TestObject& operator=(const TestObject& other) = default;
	TestObject& operator=(TestObject&& other) = default;

public:
	void Update(float dt) noexcept
	{
		roll += droll * dt;
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		theta += dtheta * dt;
		phi += dphi * dt;
		chi += dchi * dt;
		/*r = 0.0f;

		roll = 0.0f;
		pitch = 0.0f;
		yaw = 0.0f;
		theta = 0.0f;
		phi = 0.0f;
		chi = 0.0f;*/
	}

	DirectX::XMMATRIX GetTransformXM() const noexcept
	{
		namespace dx = DirectX;
		return dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			dx::XMMatrixTranslation(r, 0.0f, 0.0f) *
			dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
	}

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

#endif // !TEST_OBJECT_H_INCLUDED
