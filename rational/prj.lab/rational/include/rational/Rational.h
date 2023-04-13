// Rational.h
#pragma once


#include <iosfwd>
#include <cstdint>


class Rational {
  public:
    Rational();
    Rational(const Rational&) = default;
    Rational(Rational&&) = default;
    Rational(const int32_t num) noexcept ;
    Rational(const int32_t num, const int32_t denom);
    ~Rational() = default;
    Rational& operator=(const Rational&) = default;
    Rational& operator=(Rational&&) = default;

    int32_t num() const noexcept { return num_; }
    int32_t den() const noexcept { return den_; }

    bool operator==(const Rational& ) const noexcept;
    bool operator!=(const Rational& ) const noexcept;
    bool operator>(const Rational& ) const noexcept;
    bool operator<(const Rational& ) const noexcept;
    bool operator>=(const Rational& ) const noexcept;
    bool operator<=(const Rational& ) const noexcept;

    Rational operator-() const noexcept;

    explicit operator bool() const noexcept;

    Rational& operator*=(const Rational& rhs) noexcept;

    Rational& operator+=(const Rational& rhs) noexcept;

    Rational& operator-=(const Rational& rhs) noexcept;

    Rational& operator/=(const Rational& rhs);

    std::istream& read_from(std::istream& istrm) noexcept;
    std::ostream& write_to(std::ostream& ostrm) const noexcept;

  private:
    int32_t num_ = 0;
    int32_t den_ = 1;
    static const char delimiter_ = '/';
  private:
    void normalize();
};

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept;

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept;

inline Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
  return Rational(lhs) += rhs;
}

inline Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
  return Rational(lhs) -= rhs;
}

inline Rational operator/(const Rational& lhs, const Rational& rhs) {
  return Rational(lhs) /= rhs;
}

inline Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
  return Rational(lhs) *= rhs;
}