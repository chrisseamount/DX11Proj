#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <queue>
#include <bitset>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};

	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int __x;
		int __y;

	public:
		Event() noexcept :type(Type::Invalid), leftIsPressed(false),rightIsPressed(false),__x(0),__y(0) {}
		Event(Type type, const Mouse& parent) noexcept :type(type), leftIsPressed(parent.leftIsPressed),
			rightIsPressed(parent.rightIsPressed),
			__x(parent._x), __y(parent._y)
		{}

		~Event() = default;

		Event(const Event& other) = default;
		Event(Event&& other) = default;
		Event& operator=(const Event& other) = default;
		Event& operator=(Event&& other) = default;

		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		
		Type GetType() const noexcept
		{
			return type;
		}

		std::pair<int, int> GetPos() const noexcept
		{
			return{ __x,__y };
		}

		int GetPosX() const noexcept
		{
			return __x;
		}

		int GetPostY() const noexcept
		{
			return __y;
		}

		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}

		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}
	};

public:
	Mouse() = default;
	~Mouse() = default;

	Mouse(const Mouse& other) = delete;
	Mouse(Mouse&& other) = delete;
	Mouse& operator=(const Mouse& other) = delete;
	Mouse& operator=(Mouse&& other) = delete;

	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPostY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	Event Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;


private:
	void OnMouseMove(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
	void OnWheelDelta(int x, int y, int delta) noexcept;

private:
	static constexpr unsigned int bufferSize = 16u;
	int _x;
	int _y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	int wheelDeltaCarry = 0;
	std::queue<Event> buffer;

};


#endif // !MOUSE_H_INCLUDED