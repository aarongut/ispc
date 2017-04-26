//@error
//assigning mismatched polymorphic types

export void foo(number<0> bar) {
    integer baz = bar;
}
