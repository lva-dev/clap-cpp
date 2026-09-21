#pragma once

#include <clap/Util/Concepts.hpp>

#include <exception>
#include <format>
#include <utility>

namespace clap::error
{
class Exception : public std::exception
{
public:
	static Exception create(concepts::ActuallyConvertibleTo<std::string> auto&& message)
	{
		return Exception {std::forward<decltype(message)>(message)};
	}

	template<class... Args>
	static Exception formatted(const std::format_string<Args...> fmt, Args&&...args)
	{
		return Exception::create(std::format(fmt, std::forward<Args>(args)...));
	}

	const char *what() const noexcept override { return msg.c_str(); }
private:
	std::string msg;

	Exception(auto&& msg) : msg {std::forward<decltype(msg)>(msg)} {}
};
} // namespace clap::error::detail