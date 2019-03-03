#ifndef TESTLAC_TOOLS_WSV_HPP
#define TESTLAC_TOOLS_WSV_HPP

#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

namespace testlac::tools {
template <typename S, typename A>
struct wsv_data {
private:
  template <class T, class Alloc>
  using rebind_to =
    typename std::allocator_traits<Alloc>::template rebind_alloc<T>;

  template <class T, class Alloc>
  using vector = std::vector<T, rebind_to<T, Alloc>>;

public:
  using allocator_type = A;

  using row_data_type = vector<S, A>;
  using data_type = vector<row_data_type, A>;

  wsv_data() = default;
  explicit wsv_data(A const& alloc) : data(alloc) {}
  data_type data;
};

template <typename S, typename A>
auto read_wsv(std::string const& filename, A const& a) -> wsv_data<S, A>
{
  auto in = std::ifstream(filename);
  wsv_data<S, A> wsv(a);
  auto& data = wsv.data;
  unsigned int ndata = 0;

  std::string input_string;

  std::getline(in, input_string);
  std::istringstream first_line(input_string);
  while (first_line >> input_string) {
    ++ndata;
  }

  data.resize(ndata);
  in.seekg(0, std::ios::beg);
  while (!in.eof()) {
    for (unsigned int i = 0; i < ndata; ++i) {
      S input_data;
      in >> input_data;
      if (in.eof()) {
        break;
      }
      data[i].push_back(input_data);
    }
  }

  return wsv;
}

template <typename S,
          typename A = std::allocator<void>,
          typename = std::enable_if_t<std::is_default_constructible_v<A>>>
auto read_wsv(std::string const& filename) -> wsv_data<S, A>
{
  return read_wsv<S>(filename, A());
}

template <typename S, typename A>
void write(std::string const& filename, wsv_data<S, A> const& wsv)
{
  auto out = std::ofstream(filename);
  auto const& data = wsv.data;
  auto const ncol = data.size();
  auto const nrow = data[0].size();

  auto const max_digits10 = std::numeric_limits<double>::max_digits10;
  auto const max_width = max_digits10 + 10;

  out.precision(max_digits10);
  out.setf(std::ios::scientific);
  for (std::size_t row = 0; row < nrow; ++row) {
    for (std::size_t col = 0; col < ncol; ++col) {
      out << std::setw(max_width) << data[col][row];
    }
    out << std::endl;
  }
}
} // namespace testlac::tools

#endif // TESTLAC_TOOLS_WSV_HPP
