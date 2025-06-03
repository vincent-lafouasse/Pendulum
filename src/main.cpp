#include <raylib.h>

static constexpr int width = 800;
static constexpr int height = 600;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ClearBackground(VIOLET);
        {
            BeginDrawing();
            EndDrawing();
        }
    }

    CloseWindow();
}
