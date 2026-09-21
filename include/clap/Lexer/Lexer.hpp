#pragma once

#include <clap/Util/Concepts.hpp>
#include <clap/Util/Util.hpp>

#include <boost/optional.hpp>

#include <cassert>
#include <functional>
#include <generator>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

namespace clap::lexer
{
struct LongFlag
{
	std::string_view name;
	std::optional<std::string_view> arg;
};

class ShortFlags
{
public:
	static ShortFlags create(std::string_view inner) { return ShortFlags {inner}; }

	std::optional<char> next_flag()
	{
		if (next_index >= inner.size())
		{
			return {};
		}

		auto c = inner[next_index];
		next_index++;
		return c;
	}

	std::optional<std::string_view> next_value()
	{
		if (next_index >= inner.size())
		{
			return {};
		}

		return inner.substr(next_index);
	}
private:
	std::string_view inner;
	std::size_t next_index = 0;

	ShortFlags(std::string_view inner) : inner {inner} {};
};

class ParsedArg
{
public:
	static ParsedArg create(std::string_view inner) { return ParsedArg {inner}; }

	std::string_view to_value() const { return inner; }

	std::optional<LongFlag> to_long() const;

	std::optional<ShortFlags> to_short() const;

	bool is_empty() const { return inner.empty(); }

	bool is_stdio() const { return inner == "-"; }

	bool is_escape() const { return inner == "--"; }

	bool is_long() const { return inner.starts_with("--") && !is_escape(); }

	bool is_short() const
	{
		return inner.starts_with("-") && !is_stdio() && !inner.starts_with("--");
	}
private:
	std::string_view inner;

	ParsedArg(std::string_view inner) : inner {inner} {}
};

struct ArgCursor
{
	std::size_t cursor = 0;

	static ArgCursor create() { return ArgCursor {}; }
};

class RawArgs
{
public:
	static RawArgs create(concepts::ranges::RangeTo<std::string> auto&& args)
	{
		return RawArgs {args};
	}

	ArgCursor cursor() const { return ArgCursor::create(); }

	std::optional<ParsedArg> next(ArgCursor& cursor) const
	{
		auto raw = next_raw(cursor);
		if (raw)
		{
			return std::make_optional(ParsedArg::create(*raw));
		}

		return std::nullopt;
	}

	std::optional<std::string_view> next_raw(ArgCursor& cursor) const
	{
		auto raw = ::clap::detail::util::container::try_get(items, cursor.cursor);
		cursor.cursor += 1;
		constexpr auto f = [](auto& str) { return std::string_view {str}; };
		return ::clap::detail::util::optional::transform_std(raw, f);
	}
private:
	std::vector<std::string> items;

	RawArgs(concepts::ranges::RangeTo<std::string> auto&& args)
		: items {std::from_range, std::forward<decltype(args)>(args)}
	{
	}
};
} // namespace clap::lexer