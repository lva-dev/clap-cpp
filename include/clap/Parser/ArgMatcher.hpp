#pragma once

#include <clap/Parser/ArgMatches.hpp>
#include <clap/Builder/Command.hpp>

namespace clap::parser::detail
{
class ArgMatcher
{
public:
	static ArgMatcher create(const builder::Command& cmd) { return ArgMatcher {cmd}; }

	ArgMatches into_matches() && { return std::move(matches); }
private:
	ArgMatches matches;

	ArgMatcher(const builder::Command& cmd);
};
} // namespace clap::detail::parser