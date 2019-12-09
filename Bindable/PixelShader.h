#ifndef PIXEL_SHADER_H_INCLUDED
#define PIXEL_SHADER_H_INCLUDED

#include"Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::wstring& path);
	~PixelShader() = default;

	PixelShader(const PixelShader& other) = default;
	PixelShader(PixelShader&& other) = default;
	PixelShader& operator=(const PixelShader& other) = default;
	PixelShader& operator=(PixelShader&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;

protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

};

#endif // !PIXEL_SHADER_H_INCLUDED