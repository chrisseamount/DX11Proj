#ifndef ASSIMP_TEST_H_INCLUDED
#define ASSIMP_TEST_H_INCLUDED

#include "TestObject.h"
#include "..//Bindable/ConstantBuffers.h"

class AssimpTest : public TestObject<AssimpTest>
{
public:
	AssimpTest(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		DirectX::XMFLOAT3 material,
		float scale);

	~AssimpTest() = default;

	AssimpTest(const AssimpTest& other) = default;
	AssimpTest(AssimpTest&& other) = default;
	AssimpTest& operator=(const AssimpTest& other) = default;
	AssimpTest& operator=(AssimpTest&& other) = default;
};

#endif // !ASSIMP_TEST_H_INCLUDED
