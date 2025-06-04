#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;
static constexpr Color darkGray{24, 24, 37, 255};
static constexpr Color lavender{180, 190, 254, 255};
static constexpr Color blue{137, 180, 250, 255};
static constexpr Color pink{245, 194, 231, 255};

static constexpr int targetFps = 60;
static constexpr float frameLen = 1.0 / targetFps;

static constexpr float pendulumConstant = 5.0f;  // g/l

struct Pendulum {
    Vec2 center;
    float armLength;
    float theta;
    float thetaPrime;

    void render() const {
        constexpr float armWidth = height / 150.f;
        constexpr Color ballColor = blue;
        constexpr Color armColor = lavender;

        BeginDrawing();
        const Vec2 axial = {std::sin(theta), std::cos(theta)};
        const Vec2 transverse = {-axial.y(), axial.x()};
        const Vec2 circleCenter = center + axial.scaled(armLength);

        const Vec2 delta = transverse.scaled(armWidth);
        const Vec2 a = center - delta;
        const Vec2 b = center + delta;
        const Vec2 c = circleCenter + delta;
        const Vec2 d = circleCenter - delta;
        DrawTriangle(a.get(), b.get(), c.get(), armColor);
        DrawTriangle(c.get(), d.get(), a.get(), armColor);

        DrawCircleV(center.get(), armWidth, armColor);
        DrawCircleV(circleCenter.get(), 50.0f, ballColor);

        EndDrawing();
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    constexpr Vec2 center{width / 2.0f, height / 2.0f};
    constexpr float armLength = height / 2.5f;
    constexpr float initialAngle = PI / 4.0f;
    constexpr float inititialAngularSpeed = 0.0f;

    Pendulum p = {
        .center = center,
        .armLength = armLength,
        .theta = initialAngle,
        .thetaPrime = inititialAngularSpeed,
    };

    while (!WindowShouldClose()) {
        ClearBackground(darkGray);

        p.render();

        const float angularAcceleration = -pendulumConstant * std::sin(p.theta);
        p.thetaPrime += angularAcceleration * frameLen;
        p.theta += p.thetaPrime * frameLen;
    }

    CloseWindow();
}
