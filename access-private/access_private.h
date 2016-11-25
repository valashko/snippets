#pragma once


template<typename DataTag>
struct PrivateDataPointerWrapper
{
  using PrivateDataPointerType = typename DataTag::type;
  static PrivateDataPointerType data;
};

// explicit instantiation of static member 'data'
template<typename DataTag>
typename PrivateDataPointerWrapper<DataTag>::PrivateDataPointerType PrivateDataPointerWrapper<DataTag>::data;

template<typename DataTag, typename DataTag::type value>
struct Intruder : PrivateDataPointerWrapper<DataTag>
{
  struct Initializer
  {
    Initializer() { PrivateDataPointerWrapper<DataTag>::data = value; }
  };
  static Initializer instance; // it is legal to pass the address of a private member here
};

// explicit instantiation of static member 'instance'
template<typename DataTag, typename DataTag::type value>
typename Intruder<DataTag, value>::Initializer Intruder<DataTag, value>::instance;


#define INIT_PRIVATE_MEMBER_WRAPPER(CLASS_NAME, MEMBER_TYPE, MEMBER_NAME) \
        struct DataTagFor_##CLASS_NAME_##MEMBER_NAME { using type = MEMBER_TYPE CLASS_NAME::*; }; \
        template class Intruder<DataTagFor_##CLASS_NAME_##MEMBER_NAME, &CLASS_NAME::MEMBER_NAME>;

#define INIT_PRIVATE_METHOD_WRAPPER(CLASS_NAME, RETURN_TYPE, METHOD_NAME, /*ARGUMENT_TYPES*/...) \
        struct DataTagFor_##CLASS_NAME_##METHOD_NAME { using type = RETURN_TYPE(CLASS_NAME::*)(__VA_ARGS__); }; \
        template class Intruder<DataTagFor_##CLASS_NAME_##METHOD_NAME, &CLASS_NAME::METHOD_NAME>;

#define PRIVATE(INSTANCE, CLASS_NAME, MEMBER_NAME) \
        (INSTANCE.*PrivateDataPointerWrapper<DataTagFor_##CLASS_NAME_##MEMBER_NAME>::data)

// TODO create a macro with custom tag name to enable access to overloaded methods

