#include <cmath>

#include <raylib.h>
#include <raymath.h>

static constexpr int width = 1600;
static constexpr int height = 900;
static constexpr Color darkGray{24, 24, 37, 255};
static constexpr Color lavender{180, 190, 254, 255};
static constexpr Color blue{137, 180, 250, 255};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(60);

    constexpr Vector2 center{width / 2.0f, height / 2.0f};
    constexpr float armLength = height / 2.5f;
    float angle = 0.0f;

    while (!WindowShouldClose()) {
        ClearBackground(darkGray);
        {
            BeginDrawing();
            const Vector2 armVector = {armLength * std::sin(angle),
                                       armLength * std::cos(angle)};
            const Vector2 circleCenter = Vector2Add(center, armVector);
            DrawCircleV(center, 10.0f, lavender);
            DrawCircleV(circleCenter, 50.0f, blue);
            // const float angularVelocity =
            std::sin(static_cast<float>(GetTime()));
            // angle += angularVelocity;
            EndDrawing();
        }
    }

    CloseWindow();
}
