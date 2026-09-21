#include <clap/Util/EnumBase.hpp>

#include <string>
#include <variant>

namespace clap::parser::detail
{
namespace parse_result_variants
{
	struct Opt
	{
		std::string id;
	};

    struct ValuesDone
    {
    };

	struct UnneededAttachedValue
	{
	};

	struct MaybeHyphenValue
	{
	};

	struct NoMatchingArg
	{
		std::string arg;
	};
}; // namespace parse_result_variants

using ParseResultBase = ::clap::detail::util::EnumBase<parse_result_variants::Opt,
    parse_result_variants::ValuesDone,
	parse_result_variants::UnneededAttachedValue,
	parse_result_variants::MaybeHyphenValue,
	parse_result_variants::NoMatchingArg>;

class ParseResult : public ParseResultBase
{
public:
	using Opt = parse_result_variants::Opt;
    using ValuesDone = parse_result_variants::ValuesDone;
	using UnneededAttachedValue = parse_result_variants::UnneededAttachedValue;
	using MaybeHyphenValue = parse_result_variants::MaybeHyphenValue;
	using NoMatchingArg = parse_result_variants::NoMatchingArg;

	template<class T> ParseResult(T&& value) : ParseResultBase {std::forward<T>(value)} {}
};
} // namespace clap::parser::detail