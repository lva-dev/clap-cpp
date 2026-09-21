#include <clap/Clap.hpp>

#include <expected>
#include <print>
#include <string>

int main(int argc, char **argv)
{
    // clang-format off
	auto cmd = clap::Command::create("abcd")
        .arg(clap::Arg::create("a").short_('a'))
        .arg(clap::Arg::create("b").long_("boo"))
        .arg(clap::Arg::create("c").short_('c').long_("coo"))
        .arg(clap::Arg::create("d").short_('d').long_("doo"));

	auto matches = cmd.get_matches(argc, argv);
	if (!matches.has_value())
	{
		std::println(stderr, "error: {}", matches.error());
		return 1;
	}

	std::println("a: {}", matches->get_flag("a"));
	std::println("b: {}", matches->get_flag("b"));
	std::println("c: {}", matches->get_flag("c"));
	std::println("d: {}", matches->get_flag("d"));
}