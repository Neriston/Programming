#include <iostream>
#include <vector>

class Fenwick {
  uint m_ = 0;
  uint q_ = 0;
  uint a_ = 0;
  uint b_ = 0;
  uint cur_ = 0;
  uint sum_ = 0;
  std::vector<uint> fenwick_ = std::vector<uint>(16777216, 0);  // B array (simply without fenwick)
  //  only one array cause of query sum comes only after query update

  uint NextRand() {
    cur_ = cur_ * a_ + b_;
    return cur_ >> 8;
  }

 public:
  //  we don't need to use 2^32 cause of uint max is 2^32 - 1.
  const int64_t max = 4294967296;  //  2^32
  const uint size = 16777216;      // 2^24

  Fenwick() = default;

  Fenwick(const uint m, const uint q, const uint a, const uint b) : m_(m), q_(q), a_(a), b_(b) {
  }

  void Update() {
    uint add = NextRand();
    uint l = NextRand();
    uint r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    fenwick_[l] += add;
    fenwick_[r + 1] -= add;
  }

  void BuildPrefixSum() {
    uint last = fenwick_[0];
    uint now_sum = fenwick_[0];
    for (uint i = 1; i < size; ++i) {
      last += fenwick_[i];
      fenwick_[i] = last + now_sum;
      now_sum = fenwick_[i];
    }
  }

  void Sum() {

    uint l = NextRand();
    uint r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    sum_ += fenwick_[r] - (l > 0 ? fenwick_[l - 1] : 0);
  }

  void Accomplishment() {
    for (uint i = 0; i < m_; ++i) {
      Update();
    }
    BuildPrefixSum();
    for (uint i = 0; i < q_; ++i) {
      Sum();
    }
    std::cout << sum_;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint m = 0;
  uint q = 0;
  uint a = 0;
  uint b = 0;
  std::cin >> m >> q >> a >> b;
  Fenwick fenwick(m, q, a, b);
  fenwick.Accomplishment();
  return 0;
}