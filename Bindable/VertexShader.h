#ifndef VERTEX_SHADER_H_INCLUDED
#define VERTEX_SHADER_H_INCLUDED

#include"Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::wstring& path);
	~VertexShader() = default;

	VertexShader(const VertexShader& other) = default;
	VertexShader(VertexShader&& other) = default;
	VertexShader& operator=(const VertexShader& other) = default;
	VertexShader& operator=(VertexShader&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;
	ID3DBlob* GetByteCode() const noexcept;

protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;

};

#endif // !VERTEX_SHADER_H_INCLUDED