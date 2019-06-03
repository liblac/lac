#ifndef TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP
#define TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP

namespace teststd::experimental::math {

struct traits_test02_struct_01 {
  using engine_type = int;
};

struct traits_test02_struct_02 {
};

struct traits_test02_struct_03a {
  using engine_type = int;
};

struct traits_test02_struct_03b {
  using engine_type = int;
};

struct traits_test02_struct_04a {
  using engine_type = int;
};

struct traits_test02_struct_04b {
  using engine_type = double;
};

} // namespace teststd::experimental::math

#endif // TESTSTD_EXPERIMENTAL_MATH_TRAITS_HPP
