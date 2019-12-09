#ifndef TOPOLOGY_H_INCLUDED
#define TOPOLOGY_H_INCLUDED

#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	~Topology() = default;

	Topology(const Topology& other) = default;
	Topology(Topology&& other) = default;
	Topology& operator=(const Topology& other) = default;
	Topology& operator=(Topology&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;

protected:
	D3D11_PRIMITIVE_TOPOLOGY type;

};

#endif // !TOPOLOGY_H_INCLUDED