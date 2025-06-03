#include <cmath>

#include <raylib.h>
#include <raymath.h>

static constexpr int width = 800;
static constexpr int height = 600;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(60);

    constexpr Vector2 center {width / 2.0f, height / 2.0f};
    constexpr float offset = 100.0f;
    float angle = 0.0f;

    while (!WindowShouldClose()) {
        ClearBackground(VIOLET);
        {
            BeginDrawing();
            const Vector2 offsetVector = {offset * std::sin(angle), offset * std::cos(angle)};
            const Vector2 circleCenter = Vector2Add(center, offsetVector);
            DrawCircle(circleCenter.x, circleCenter.y, 50.0f, RED);
            const float angularVelocity = std::sin(GetTime());
            angle += angularVelocity;
            EndDrawing();
        }
    }

    CloseWindow();
}
