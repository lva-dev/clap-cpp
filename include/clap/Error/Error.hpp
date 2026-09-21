#pragma once

#include <format>

namespace clap::error
{
class Error
{
};
} // namespace clap::error

namespace clap
{
using error::Error;
}

template<> struct std::formatter<clap::error::Error>
{
	template<class ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template<class FormatContext>
	FormatContext::iterator format(const clap::Error&, FormatContext& ctx) const
	{
		return std::format_to(ctx.out(), "{}", "clap error");
	}
};