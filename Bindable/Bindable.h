#ifndef BINDABLE_H_INCLUDED
#define BINDABLE_H_INCLUDED

#include "../Graphics.h"

class Bindable
{
public:
	Bindable() = default;
	~Bindable() = default;

	Bindable(const Bindable& other) = default;
	Bindable(Bindable&& other) = default;
	Bindable& operator=(const Bindable& other) = default;
	Bindable& operator=(Bindable&& other) = default;

public:
	virtual void Bind(Graphics& gfx) noexcept = 0;

protected:
	static ID3D11DeviceContext* GetContext(Graphics& gfx) noexcept;
	static ID3D11Device* GetDevice(Graphics& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(Graphics& gfx);


};

#endif // !BINDABLE_H_INCLUDED
