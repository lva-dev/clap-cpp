#pragma once

#include <clap/Builder/Command.hpp>
#include <clap/Error/Error.hpp>
#include <clap/Lexer/Lexer.hpp>
#include <clap/Parser/ArgMatcher.hpp>
#include <clap/Parser/ParseResult.hpp>
#include <clap/Util/Util.hpp>

#include <expected>
#include <functional>
#include <string>
#include <utility>

namespace clap::detail::parser
{
class ArgMatcher;
}

namespace clap::parser
{

class Parser
{
public:
	static Parser create(std::reference_wrapper<const builder::Command> cmd)
	{
		return Parser {cmd};
	}

	std::expected<void, Error> get_matches_with(detail::ArgMatcher& matcher,
		lexer::RawArgs& raw_args,
		lexer::ArgCursor args_cursor);
private:
	std::reference_wrapper<const builder::Command> cmd;

	Parser(std::reference_wrapper<const builder::Command> cmd) : cmd {cmd} {}

	detail::ParseResult parse_short_arg(detail::ArgMatcher& matcher, lexer::ShortFlags short_arg);
	detail::ParseResult parse_long_arg(detail::ArgMatcher& matcher, lexer::LongFlag& long_arg);
};
} // namespace clap::parser