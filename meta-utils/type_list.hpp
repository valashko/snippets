namespace meta
{
    template<class T, class... Ts>
    struct type_list_back
    {
        using type = typename type_list_back<Ts...>::type;
    };

    template<class T>
    struct type_list_back<T>
    {
        using type = T;
    };

    template<class... Ts>
    using type_list_back_t = typename type_list_back<Ts...>::type;
}

