---
title: "lac::is\_float\_field"
date: 2019-03-02T18:12:23+01:00
layout: main
---

## lac::is\_float\_field
Defined in [`<lac/traits.hpp>`](/header/lac/traits.hpp)

```cpp
template <typename T>
struct is_float_field;
```

If T is a [float field](/doc/float_field) or a cv-qualified version thereof,
provides the member constant `value` equal `true`. For any other type, `value`
is `false`. Standard arithmetic types (satisfying
[`std::arithmetic<T>`](https://en.cppreference.com/w/cpp/types/is_arithmetic) )
are assumed to satisfy float field.

**IMPORTANT:** The definiton of float field is not verifiable in code. Hence,
in case of a user type, the user has to manually check if their type is a float
field or not and specify it as such. The result of specifying `is_float_field`
true for a type which does not satisfy the requirements mentioned for the
[float field](/doc/float_field#requirements) is undefined.

### Template Parameters

| Type | Description and Requirements |
| --- | --- |
| `T` | Type to Check |


### Helper Variable Template

```cpp
template< class T >
inline constexpr bool is_float_field_v = is_float_field<T>::value;
```

## Inherited from `std::integral_constant`
### Member Constant

| Name | Description |
| --- | --- |
| `value` | `true` if `T` is a float field|


### Member Functions
| Name | Description |
| --- | --- |
| `operator bool` | converts the object to `bool`, returns `value`|
| `operator()` (C++14) | returns `value`|


### Member Types
|Typs | Description |
| --- | --- |
| `value_type` | bool |
| `type` | `std::integral_constant<bool, value>` |


