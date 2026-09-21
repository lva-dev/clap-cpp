#include <clap/Error/Error.hpp>
#include <clap/Lexer/Lexer.hpp>
#include <clap/Parser/ArgMatcher.hpp>
#include <clap/Parser/Parser.hpp>

#include <optional>
#include <print>
#include <string_view>

using clap::parser::detail::ParseResult;
using clap::parser::detail::ArgMatcher;

namespace clap::parser
{
std::expected<void, Error> Parser::get_matches_with(ArgMatcher& matcher,
	lexer::RawArgs& raw_args,
	lexer::ArgCursor args_cursor)
{
	auto argOpt = raw_args.next(args_cursor);

	bool found_escape = false;

	for (; argOpt.has_value(); argOpt = raw_args.next(args_cursor))
	{
		auto& arg = *argOpt;
		std::println(stderr, "[DEBUG]: {}", arg.to_value());

		if (!found_escape)
		{
			if (arg.is_escape())
			{
				found_escape = true;
				continue;
			}
			if (auto short_arg = arg.to_short(); short_arg.has_value())
			{
				auto parse_result = parse_short_arg(matcher, *short_arg);
				continue;
			}
			else if (auto long_arg = arg.to_long(); long_arg.has_value())
			{
				auto parse_result = parse_long_arg(matcher, *long_arg);
				continue;
			}
			else
			{
			}
		}
	}

	return {};
}

ParseResult Parser::parse_short_arg(ArgMatcher& matcher,
	lexer::ShortFlags short_arg)
{
	return ParseResult::NoMatchingArg {""};
}

ParseResult Parser::parse_long_arg(ArgMatcher& matcher, lexer::LongFlag& long_arg)
{
	return ParseResult::NoMatchingArg {std::string {long_arg.name}};
}
} // namespace clap::parser