// RUN: %clang_cc1 -fsyntax-only -verify -std=c++0x %s

struct A {}; // expected-note {{candidate function}}

struct BASE {
  operator A(); // expected-note {{candidate function}}
};

struct BASE1 {
 operator A();  // expected-note {{candidate function}}
};

class B : public BASE , public BASE1
{
  public:
  B();
} b;

extern B f();

const int& ri = (void)0; // expected-error {{reference to type 'int const' could not bind to an rvalue of type 'void'}}

int main() {
        const A& rca = f(); // expected-error {{conversion from 'class B' to 'struct A const' is ambiguous}}
        A& ra = f(); // expected-error {{non-const lvalue reference to type 'struct A' cannot bind to a temporary of type 'class B'}}
}
