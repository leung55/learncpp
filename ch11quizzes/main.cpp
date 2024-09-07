// define your factorial() function template here

template <int F>
constexpr int factorial() {
    if constexpr (F == 0) {
        return 1;
    }
    return F*factorial<F-1>();
}

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    // factorial<-3>(); // should fail to compile

    return 0;
}