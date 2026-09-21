#include <clap/Builder/Arg.hpp>
#include <clap/Parser/ArgMatches.hpp>
#include <clap/Builder/Command.hpp>
#include <clap/Parser/ArgMatcher.hpp>

#include <ranges>
#include <string>
#include <vector>

using clap::builder::Command;
using clap::builder::Arg;

namespace
{
std::vector<std::string> get_arguments_from_cmd(const Command& cmd)
{
	constexpr auto f = [](const Arg& arg) { return arg.get_id(); };
	auto view = std::views::transform(cmd.get_arguments(), f);
	return std::ranges::to<std::vector>(view);
}
} // namespace

namespace clap::parser::detail
{
ArgMatcher::ArgMatcher(const Command& cmd)
	: matches {ArgMatches::create(get_arguments_from_cmd(cmd))}
{
}
} // namespace clap::detail::parser