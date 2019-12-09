#ifndef INPUT_LAYOUT_H_INCLUDED
#define INPUT_LAYOUT_H_INCLUDED

#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode);
	~InputLayout() = default;

	InputLayout(const InputLayout& other) = default;
	InputLayout(InputLayout&& other) = default;
	InputLayout& operator=(const InputLayout& other) = default;
	InputLayout& operator=(InputLayout&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

};

#endif // !INPUT_LAYOUT_H_INCLUDED