#ifndef VERTEX_BUFFER_H_INCLUDED
#define VERTEX_BUFFER_H_INCLUDED
#include "Bindable.h"
#include "..//Macros/GraphicsThrowMacros.h"

class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		INFOMAN(gfx);

		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = UINT(sizeof(V)*vertices.size());
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));

		// bind vertex buffer to pipeline
		
	}

	~VertexBuffer() = default;

	VertexBuffer(const VertexBuffer& other) = default;
	VertexBuffer(VertexBuffer&& other) = default;
	VertexBuffer& operator=(const VertexBuffer& other) = default;
	VertexBuffer& operator=(VertexBuffer&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	const UINT stride;


};

#endif // !VERTEX_BUFFER_H_INCLUDED