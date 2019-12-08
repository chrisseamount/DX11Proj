#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

namespace MyMath
{
	typedef _Vec2<int> Veci3;
	typedef _Vec2<float> Vecf3;
	typedef _Vec2<double> Vecd3;
	
	template<typename T>
	class _Vec2
	{
	public:
		constexpr _Vec2() noexcept = default;
		constexpr _Vec2(T x, T y) noexcept : x(x), y(y) {}

		constexpr const _Vec2& operator+() const noexcept { return *this; }
		constexpr _Vec2 operator-() const noexcept { return _Vec2(-x, -y); };

		constexpr _Vec2& operator+=(const _Vec2& v2) noexcept
		{
			x += v2.x;
			y += v2.y;
			return *this;
		}

		constexpr _Vec2& operator-=(const _Vec2& v2) noexcept
		{
			x -= v2.x;
			y -= v2.y;
			return *this;
		}

		constexpr _Vec2& operator*=(const _Vec2& v2) noexcept
		{
			x *= v2.x;
			y *= v2.y;
			return *this;
		}

		constexpr _Vec2& operator/=(const _Vec2& v2) noexcept
		{
			x /= v2.x;
			y /= v2.y;
			return *this;
		}

		constexpr _Vec2& operator*=(const T& t) noexcept
		{
			x *= t;
			y *= t;
			return *this;
		}

		constexpr _Vec2& operator/=(const T& t) noexcept
		{
			T k = 1.0 / t;

			x *= k;
			y *= k;
			return *this;
		}

		double length() const noexcept
		{
			return sqrt(x * x + y * y);
		}

		constexpr double squared_length() const noexcept
		{
			return x * x + y * y;
		}

		void make_unit_vector() noexcept
		{
			T k = 1.0 / sqrt(x * x + y * y);
			x *= k;
			y *= k;
			z *= k;
		}
	};

	template<typename T>
	constexpr _Vec2<T> operator+(const _Vec2<T>& v1, const _Vec2<T>& v2) noexcept
	{
		return _Vec2<T>(v1.x + v2.x, v1.y + v2.y);
	}

	template<typename T>
	constexpr _Vec2<T> operator-(const _Vec2<T>& v1, const _Vec2<T>& v2) noexcept
	{
		return _Vec2<T>(v1.x - v2.x, v1.y - v2.y);
	}

	template<typename T>
	constexpr _Vec2<T> operator*(const _Vec2<T>& v1, const _Vec2<T>& v2) noexcept
	{
		return _Vec2<T>(v1.x * v2.x, v1.y * v2.y);
	}

	template<typename T>
	constexpr _Vec2<T> operator/(const _Vec2<T>& v1, const _Vec2<T>& v2) noexcept
	{
		return _Vec2<T>(v1.x / v2.x, v1.y / v2.y);
	}

	template<typename T>
	constexpr _Vec2<T> operator*(double t, const _Vec2<T>& v) noexcept
	{
		return _Vec2<T>(v.x * t, v.y * t);
	}

	template<typename T>
	constexpr _Vec2<T> operator/(_Vec2<T> v, double t) noexcept
	{
		return _Vec2<T>(v.x / t, v.y / t);
	}

	template<typename T>
	constexpr _Vec2<T> operator*(const _Vec2<T>& v, double t) noexcept
	{
		return _Vec2<T>(t * v.x, t * v.y);
	}

	template<typename T>
	constexpr double dot(const _Vec2<T>& v1, const _Vec2<T>& v2) noexcept
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template<typename T>
	constexpr _Vec2<T> unit_vector(_Vec2<T> v) noexcept
	{
		return v / v.length();
	}

	};
}

#endif // !VEC2_H_INCLUDED