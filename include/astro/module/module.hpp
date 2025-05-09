#pragma once

#include <memory>

#include "../utils.hpp"

namespace astro::module {

    template <typename... Args>
    using depends_on = astro::utils::arg_pack<Args...>;

    class manager {
        public:
            template <typename T>
            void register_component(std::shared_ptr<T> component) {
                _components.push_back(component);
            }
    };

    template <typename Derived, typename DependsOn>
    class component {
        public:
            using component_type = Derived;
            using depends_on_types = DependsOn<>;

        private:
    };

} // namespace astro::module