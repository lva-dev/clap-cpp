#pragma once

#include <boost/optional.hpp>

#include <algorithm>
#include <cstddef>
#include <flat_map>
#include <format>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

namespace clap::detail::util::memory
{
template<class T> boost::optional<T&> as_ref(T *ptr)
{
	if (ptr != nullptr)
	{
		return *ptr;
	}
	else
	{
		return {};
	}
}

template<class T> boost::optional<const T&> as_ref(const T *ptr)
{
	if (ptr != nullptr)
	{
		return *ptr;
	}
	else
	{
		return {};
	}
}

template<class T> boost::optional<T&> as_ref(std::unique_ptr<T>& ptr)
{
	return as_ref(ptr.get());
}

template<class T> boost::optional<const T&> as_ref(const std::unique_ptr<T>& ptr)
{
	return as_ref(ptr.get());
}

template<class T> boost::optional<const T&> as_ref(std::unique_ptr<T>&& ptr) = delete;

template<class T>
boost::optional<const T&> as_ref(const std::unique_ptr<T>&& ptr) = delete;
} // namespace clap::detail::util::memory

namespace clap::detail::util::optional
{
template<class T> boost::optional<T&> as_ref(std::optional<T>& opt)
{
	if (opt.has_value())
	{
		return *opt;
	}
	else
	{
		return {};
	}
}

template<class T> boost::optional<const T&> as_ref(const std::optional<T>& opt)
{
	if (opt.has_value())
	{
		return *opt;
	}
	else
	{
		return {};
	}
}

template<class T> boost::optional<T&> as_ref(std::optional<T>&& opt) = delete;

template<class T> boost::optional<T&> as_ref(const std::optional<T>&& opt) = delete;

template<class T, class F>
constexpr auto transform_std(const boost::optional<T>& opt, F&& f)
{
	using Result = std::optional<std::invoke_result_t<F, T>>;

	if (opt)
	{
		return Result {std::invoke(std::forward<F>(f), *opt)};
	}

	return Result {std::nullopt};
}
} // namespace clap::detail::util::optional

namespace clap::detail::util::container
{
template<class T, class K, class V, class C, class Kc, class Mc>
boost::optional<const V&> try_get(const std::flat_map<K, V, C, Kc, Mc>& map,
	const T& value)
{
	if (auto it = map.find(value); it != map.end())
	{
		return it->second;
	}

	return {};
}

template<class T, class K, class V, class C, class Kc, class Mc>
boost::optional<V&> try_get(std::flat_map<K, V, C, Kc, Mc>& map, const T& value)
{
	if (auto it = std::ranges::find(map, value); it != std::ranges::end(map))
	{
		return it->second;
	}

	return {};
}

template<class T> boost::optional<T&> try_get(std::vector<T>& vec, std::size_t index)
{
	if (index >= vec.size())
	{
		return boost::none;
	}

	return vec[index];
}

template<class T>
boost::optional<const T&> constexpr try_get(const std::vector<T>& vec, std::size_t index)
{
	if (index >= vec.size())
	{
		return boost::none;
	}

	return vec[index];
}
} // namespace clap::detail::util::container

namespace clap::detail::util::str
{
inline std::optional<std::string_view> strip_prefix(std::string_view str,
	std::string_view prefix)
{
	if (str.starts_with(prefix))
	{
		return str.substr(prefix.size());
	}

	return {};
}

using SplitOnce = std::pair<std::string_view, std::string_view>;

inline std::optional<SplitOnce> split_once(std::string_view str, std::string_view needle)
{
	std::size_t start = str.find(needle);
	if (start == std::string_view::npos)
	{
		return {};
	}

	auto end = start + needle.size();
	return std::make_pair(str.substr(0, start), str.substr(end));
}
} // namespace clap::detail::util::str