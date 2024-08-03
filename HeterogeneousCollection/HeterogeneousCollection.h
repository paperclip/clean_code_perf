#pragma once

#include <experimental/type_traits>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace andyg
{
    template <class...>
    struct type_list
    {
    };

    template <class... TYPES>
    struct visitor_base
    {
        using types = andyg::type_list<TYPES...>;
    };

    struct heterogeneous_container
    {
       public:
        heterogeneous_container() = default;
        heterogeneous_container(const heterogeneous_container& _other);
        heterogeneous_container& operator=(const heterogeneous_container& _other);

        template <class T>
        void push_back(const T& _t)
        {
            // don't have it yet, so create functions for printing, copying, moving, and destroying
            if (items<T>.find(this) == std::end(items<T>))
            {
                clear_functions.emplace_back([](heterogeneous_container& _c) { items<T>.erase(&_c); });

                // if someone copies me, they need to call each copy_function and pass themself
                copy_functions.emplace_back([](const heterogeneous_container& _from, heterogeneous_container& _to)
                                            { items<T>[&_to] = items<T>[&_from]; });
                size_functions.emplace_back([](const heterogeneous_container& _c) { return items<T>[&_c].size(); });
            }
            items<T>[this].push_back(_t);
        }

        void clear();

        template <class T>
        size_t number_of() const
        {
            auto iter = items<T>.find(this);
            if (iter != items<T>.cend())
            {
                return items<T>[this].size();
            }
            return 0;
        }

        size_t size() const;

        ~heterogeneous_container();

        template <class T>
        void visit(T&& visitor)
        {
            visit_impl(visitor, typename std::decay_t<T>::types{});
        }

       private:
        template <class T>
        static std::unordered_map<const heterogeneous_container*, std::vector<T>> items;

        template <class T, class U>
        using visit_function = decltype(std::declval<T>().operator()(std::declval<U&>()));
        template <class T, class U>
        static constexpr bool has_visit_v = std::experimental::is_detected<visit_function, T, U>::value;

        template <class T, template <class...> class TLIST, class... TYPES>
        void visit_impl(T&& visitor, TLIST<TYPES...>)
        {
            (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor));
        }

        template <class T, class U>
        void visit_impl_help(T& visitor)
        {
            static_assert(has_visit_v<T, U>,
                          "Visitors must provide a visit function accepting a reference for each type");
            for (auto&& element : items<U>[this])
            {
                visitor(element);
            }
        }

        std::vector<std::function<void(heterogeneous_container&)>> clear_functions;
        std::vector<std::function<void(const heterogeneous_container&, heterogeneous_container&)>> copy_functions;
        std::vector<std::function<size_t(const heterogeneous_container&)>> size_functions;
    };

    template <class T>
    std::unordered_map<const heterogeneous_container*, std::vector<T>> heterogeneous_container::items;
}  // namespace andyg
