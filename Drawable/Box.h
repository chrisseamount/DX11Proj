#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "TestObject.h"

class Box : public TestObject<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& bdist,
		DirectX::XMFLOAT3 material);

	Box(const Box& other) = default;
	Box(Box&& other) = default;
	Box& operator=(const Box& other) = default;
	Box& operator=(Box&& other) = default;

public:
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	DirectX::XMFLOAT3X3 mt;

};

#endif // !BOX_H_INCLUDED
