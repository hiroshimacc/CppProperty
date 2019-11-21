#pragma once
#include <functional>
#include <utility>
#include <type_traits>

namespace CppProperty
{
    /**
     * @namespace CppProperty::details
     * @brief Implementations details for C++14 properties
     */
    namespace details{
        /**
         * @brief Type traits for properties
         * @tparam T being the type of values
         */
        template <class T>
        struct property_traits{
            using value_type = std::remove_reference_t<std::remove_cv_t<T>>;
            using getter_type = std::function<value_type()>;
            using setter_type = std::function<void(value_type)>;
        };

        /**
         * @brief Type traits for properties (based on a reference)
         * @tparam T being the type of reference
         */
        template <class T>
        struct property_traits<T&>{
            using ref_type = T&;
            using value_type = std::remove_reference_t<std::remove_cv_t<T>>;
            using getter_type = std::function<ref_type()>;
            using setter_type = std::function<void(value_type)>;
        };
    }

    /**
     * @brief A class that allows use of transparent getters and setters through the implicit conversions and assignment operators
     * @tparam T being the type of value to get from the property
     */
    template<class T>
    class property
    {
    public:
        using trait_type = details::property_traits<T>;
        using value_type = typename trait_type::value_type;
        using getter_type = typename trait_type::getter_type;
        using setter_type = typename trait_type::setter_type;

        property(getter_type xget, setter_type xset)
            : get_{ std::move(xget) }
            , set_{ std::move(xset) }
        {            
        }

        operator value_type () const
        {
            return get_();
        }

        property& operator=(value_type const& value)
        {
            set_(value);
            return *this;
        }

        property& operator=(value_type&& value)
        {
            set_(std::move(value));
            return *this;
        }

    private:
        getter_type get_;
        setter_type set_;
    };

    /**
     * @brief A class that allows use of transparent getters and setters through the implicit conversions and assignment operators
     * @tparam T being the type of references to get from the property
     */
    template<class T>
    class property<T&>
    {
    public:
        using trait_type = details::property_traits<T&>;
        using value_type = typename trait_type::value_type;
        using getter_type = typename trait_type::getter_type;
        using setter_type = typename trait_type::setter_type;

        property(getter_type xget, setter_type xset)
            : get_{ std::move(xget) }
            , set_{ std::move(xset) }
        {            
        }

        operator value_type& ()
        {
            return get_();
        }

        operator value_type const& () const
        {
            return get_();
        }

        property& operator=(value_type const& value)
        {
            set_(value);
            return *this;
        }

        property& operator=(value_type&& value)
        {
            set_(std::move(value));
            return *this;
        }

    private:
        getter_type get_;
        setter_type set_;
    };
}

#define prop_get [this]
#define prop_getref [this]() ->auto&
#define prop_set [this](auto&& value)
