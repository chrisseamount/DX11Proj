#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include "..//Graphics.h"
#include<DirectXMath.h>


class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;

public:
	Drawable() = default;
	virtual ~Drawable() = default;

	Drawable(const Drawable& other) = delete;
	Drawable(Drawable&& other) = default;
	Drawable& operator=(const Drawable& other) = default;
	Drawable& operator=(Drawable&& other) = default;

public:
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	void Draw(Graphics& gfx) const noexcept;
	virtual void Update(float dt) noexcept = 0;

protected:
	void AddBind(std::unique_ptr<Bindable> bind) noexcept;
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept;

private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
	const class IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;

};

#endif // !DRAWABLE_H_INCLUDED
