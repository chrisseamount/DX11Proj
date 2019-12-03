#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include<exception>
#include<string>

class Exceptions : public std::exception
{
public:
	Exceptions(int line, const char* file) noexcept;
	~Exceptions() = default;

	Exceptions(const Exceptions& other) = default;
	Exceptions(Exceptions&& other) = default;
	Exceptions& operator=(const Exceptions& other) = default;
	Exceptions& operator=(Exceptions&& other) = default;

	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	int _line;
	std::string _file;

protected:
	mutable std::string whatBuffer;

};


#endif // !EXCEPTIONS_H_INCLUDED
