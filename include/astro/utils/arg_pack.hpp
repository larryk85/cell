#pragma once

#include <type_traits>
#include <tuple>

namespace astro::utils {
    template <typename... Args>
    struct arg_pack {
        using pack = std::tuple<Args...>;
        using types = std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...>;

        consteval std::size_t size() const noexcept { return sizeof...(Args); }
    };

    template <std::size_t N, template<typename...> typename Pack = arg_pack>
    using arg_pack_at = std::tuple_element_t<N, typename Pack<>::types>;

} // namespace astro::utils