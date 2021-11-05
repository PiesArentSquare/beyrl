#include <iostream>
#include <beyrl/beyrl.hpp>

int main() {
    beyrl::RenderingContext context;
    auto window = context.window(1280, 720, "Main Window");
    window.run();
}