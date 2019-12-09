#ifndef TRANSFORM_CBUF_H_INCLUDED
#define TRANSFORM_CBUF_H_INCLUDED

#include "ConstantBuffers.h"
#include "..//Drawable/Drawable.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
private:
	struct Transforms
	{
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX model;
	};

public:
	TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot = 0u);
	~TransformCbuf() = default;

	TransformCbuf(const TransformCbuf& other) = default;
	TransformCbuf(TransformCbuf&& other) = default;
	TransformCbuf& operator=(const TransformCbuf& other) = default;
	TransformCbuf& operator=(TransformCbuf&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable& parent;


};

#endif // !TRANSFORM_CBUF_H_INCLUDED