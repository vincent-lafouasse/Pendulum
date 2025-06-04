#include <cmath>

#include <raylib.h>
#include <raymath.h>

static constexpr int width = 1600;
static constexpr int height = 900;
static constexpr Color darkGray{24, 24, 37, 255};
static constexpr Color lavender{180, 190, 254, 255};
static constexpr Color blue{137, 180, 250, 255};
static constexpr Color pink{245, 194, 231, 255};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(60);

    constexpr Vector2 center{width / 2.0f, height / 2.0f};
    constexpr float armLength = height / 2.5f;
    constexpr float armWidth = height / 150.f;
    float angle = 0.0f;

    while (!WindowShouldClose()) {
        ClearBackground(darkGray);
        {
            BeginDrawing();
            const Vector2 axial = {std::sin(angle), std::cos(angle)};
            const Vector2 transverse = {-axial.y, axial.x};
            const Vector2 circleCenter = Vector2Add(center, Vector2Scale(axial, armLength));

            const Vector2 delta = Vector2Scale(transverse, armWidth);
            const Vector2 a = Vector2Subtract(center, delta);
            const Vector2 b = Vector2Add(center, delta);
            const Vector2 c = Vector2Add(circleCenter, delta);
            const Vector2 d = Vector2Subtract(circleCenter, delta);
            DrawTriangle(a, b, c, pink);
            DrawTriangle(c, d, a, pink);

            DrawCircleV(center, 10.0f, pink);
            DrawCircleV(circleCenter, 50.0f, blue);

            EndDrawing();
        }
    }

    CloseWindow();
}
