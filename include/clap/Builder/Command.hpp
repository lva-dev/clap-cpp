#pragma once

#include <clap/Builder/Arg.hpp>		  // for Arg
#include <clap/Error/Error.hpp>		  // for Error
#include <clap/Lexer/Lexer.hpp>		  // for RawArgs
#include <clap/Parser/ArgMatches.hpp> // for ArgMatches
#include <clap/Util/Concepts.hpp>	  // for RangeTo, ViewOf

#include <cstddef>	// for size_t
#include <expected> // for expected
#include <optional> // for optional
#include <ranges>	// for transform_view, _Transform
#include <span>		// for span
#include <string>	// for basic_string, string
#include <utility>	// for move
#include <vector>	// for vector

namespace clap::builder
{
class Command
{
public:
	static Command create(const std::string& name) { return Command {name}; }

	std::expected<parser::ArgMatches, Error> get_matches(int argc, char **argv)
	{
		auto span = std::span<char *> {argv, static_cast<std::size_t>(argc)}.subspan(1);
		constexpr auto f = [](auto arg) { return std::string {arg}; };
		auto view = span | std::views::transform(f);
		return get_matches(view);
	}

	std::expected<parser::ArgMatches, Error> get_matches(
		concepts::ranges::RangeTo<std::string> auto&& args)
	{
		auto raw_args = lexer::RawArgs::create(args);
		return get_matches(raw_args);
	}

	void add_arg(Arg&& arg) & { args.emplace_back(std::move(arg)); }

	Command arg(Arg&& arg) &&
	{
		add_arg(std::move(arg));
		return std::move(*this);
	}

	void set_version(std::string&& version) & { version_ = std::move(version); }

	Command version(std::string&& version) &&
	{
		set_version(std::move(version));
		return std::move(*this);
	}

	const std::string& get_name() const { return name; }

	auto get_arguments() const -> concepts::ranges::ViewOf<Arg> auto
	{
		return std::views::all(args);
	}
private:
	std::string name;
	std::optional<std::string> version_;
	std::vector<Arg> args;

	Command(std::string name) : name {std::move(name)} {};

	std::expected<parser::ArgMatches, Error> get_matches(lexer::RawArgs& raw_args);
};
} // namespace clap::builder