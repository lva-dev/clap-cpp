#include <clap/Parser/ArgMatches.hpp>  // for ArgMatches
#include <clap/Builder/Command.hpp>
#include <clap/Lexer/Lexer.hpp>		 // for ArgCursor, RawArgs
#include <clap/Parser/ArgMatcher.hpp> // for ArgMatcher
#include <clap/Parser/Parser.hpp>	 // for Parser
#include <clap/Error/Error.hpp>					 // for Error

#include <expected>	  // for expected, unexpected
#include <functional> // for reference_wrapper
#include <utility>

namespace clap
{
std::expected<parser::ArgMatches, Error> builder::Command::get_matches(
	lexer::RawArgs& raw_args)
{
	auto args_cursor = raw_args.cursor();
	auto parser = parser::Parser::create(*this);
	auto matcher = parser::detail::ArgMatcher::create(*this);
	auto result = parser.get_matches_with(matcher, raw_args, args_cursor);
	if (!result)
	{
		return std::unexpected {std::move(result.error())};
	}

	return std::move(matcher).into_matches();
}
} // namespace clap