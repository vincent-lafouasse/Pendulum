#include <chrono>
#include <thread>
#include <raylib.h>

int main() {
    InitWindow(800, 600, "hi");
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    CloseWindow();

}
