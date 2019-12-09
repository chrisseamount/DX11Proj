#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "TestObject.h"

class Cylinder : public TestObject<Cylinder>
{
public:
	Cylinder(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& bdist,
		std::uniform_int_distribution<int>& tdist);

	~Cylinder() = default;

	Cylinder(const Cylinder& other) = default;
	Cylinder(Cylinder&& other) = default;
	Cylinder& operator=(const Cylinder& other) = default;
	Cylinder& operator=(Cylinder&& other) = default;
};

#endif // !CYLINDER_H_INCLUDED
