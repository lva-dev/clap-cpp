#include <clap/Lexer/Lexer.hpp> // for LongFlag, ShortFlags, ParsedArg
#include <clap/Util/Debug.hpp>	// for debug_assert
#include <clap/Util/Util.hpp>	// for strip_prefix, split_once

#include <optional>	   // for optional
#include <string_view> // for basic_string_view, string_view
#include <utility>	   // for pair

using clap::debug::debug_assert;

namespace clap::lexer
{
std::optional<LongFlag> ParsedArg::to_long() const
{
	auto remainder = ::clap::detail::util::str::strip_prefix(inner, "--");
	if (!remainder)
	{
		return {};
	}

	if (remainder->empty())
	{
		debug::debug_assert([this]() { return this->is_escape(); });
		return {};
	}

	auto split_result = ::clap::detail::util::str::split_once(*remainder, "=");
	if (split_result)
	{
		return LongFlag {
			.name = split_result->first,
			.arg = split_result->second,
		};
	}
	else
	{
		return LongFlag {
			.name = *remainder,
			.arg = {},
		};
	}
}

std::optional<ShortFlags> ParsedArg::to_short() const
{
	auto remainder = ::clap::detail::util::str::strip_prefix(inner, "-");
	if (!remainder)
	{
		return {};
	}
	else if (remainder->starts_with('-'))
	{
		return {};
	}
	else if (remainder->empty())
	{
		debug::debug_assert([this]() { return this->is_stdio(); });
		return {};
	}

	return ShortFlags::create(*remainder);
}
} // namespace clap::lexer