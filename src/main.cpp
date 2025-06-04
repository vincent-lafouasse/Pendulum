#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"
#include "catpuccin.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;

static constexpr int targetFps = 60;
static constexpr float frameLen = 1.0 / targetFps;

static constexpr float pendulumConstant = 5.0f;  // g/l

struct Pendulum {
    Vec2 center;
    float armLength;
    float theta;
    float thetaPrime;

    void renderArm(Vec2 from, Vec2 to, Color color) const {
        constexpr float armWidth = height / 150.f;
        const Vec2 delta =
            (to - from).normalized().transverse().scaled(armWidth);
        const Vec2 a = from - delta;
        const Vec2 b = from + delta;
        const Vec2 c = to + delta;
        const Vec2 d = to - delta;
        DrawTriangle(a.get(), b.get(), c.get(), color);
        DrawTriangle(c.get(), d.get(), a.get(), color);
    }

    void render() const {
        constexpr Color centerColor = catpuccin::lavender;
        constexpr Color armColor = catpuccin::blue;
        constexpr Color ballColor = catpuccin::teal;
        constexpr float armWidth = height / 150.f;

        BeginDrawing();
        const Vec2 axial = {std::sin(theta), std::cos(theta)};
        const Vec2 circleCenter = center + axial.scaled(armLength);

        this->renderArm(center, circleCenter, armColor);
        DrawCircleV(center.get(), armWidth, centerColor);
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
        ClearBackground(catpuccin::darkGray);

        p.render();

        const float angularAcceleration = -pendulumConstant * std::sin(p.theta);
        p.thetaPrime += angularAcceleration * frameLen;
        p.theta += p.thetaPrime * frameLen;
    }

    CloseWindow();
}
