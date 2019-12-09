#ifndef INDEX_BUFFER_H_INCLUDED
#define INDEX_BUFFER_H_INCLUDED

#include"Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	~IndexBuffer() = default;

	IndexBuffer(const IndexBuffer& other) = default;
	IndexBuffer(IndexBuffer&& other) = default;
	IndexBuffer& operator=(const IndexBuffer& other) = default;
	IndexBuffer& operator=(IndexBuffer&& other) = default;

public:
	void Bind(Graphics& gfx) noexcept override;
	UINT GetCount() const noexcept;

protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};

#endif // !INDEX_BUFFER_H_INCLUDED