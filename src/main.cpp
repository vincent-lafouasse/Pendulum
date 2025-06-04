#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"
#include "catpuccin.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;

static constexpr int targetFps = 60;
static constexpr float frameLen = 1.0 / targetFps;

struct Config {
    float length;
    float initialTheta;
    float constant;
};

struct LookAndFeel {
    Vec2 center;
    float armWidth;
    float radius;

    Color centerColor;
    Color armColor;
    Color ballColor;
};

struct Pendulum {
    Pendulum(Config cfg, LookAndFeel look)
        : cfg(cfg), look(look), theta(cfg.initialTheta), thetaPrime(0) {}

    const Config cfg;
    const LookAndFeel look;
    float theta;
    float thetaPrime;

    void renderArm(Vec2 from, Vec2 to, Color color) const {
        const Vec2 delta =
            (to - from).normalized().transverse().scaled(look.armWidth);
        const Vec2 a = from - delta;
        const Vec2 b = from + delta;
        const Vec2 c = to + delta;
        const Vec2 d = to - delta;
        DrawTriangle(a.get(), b.get(), c.get(), color);
        DrawTriangle(c.get(), d.get(), a.get(), color);
    }

    void render() const {
        ClearBackground(catpuccin::darkGray);
        BeginDrawing();
        const Vec2 axial = {std::sin(theta), std::cos(theta)};
        const Vec2 circleCenter = look.center + axial.scaled(cfg.length);

        this->renderArm(look.center, circleCenter, look.armColor);
        DrawCircleV(look.center.get(), look.armWidth, look.centerColor);
        DrawCircleV(circleCenter.get(), look.radius, look.ballColor);

        EndDrawing();
    }

    void update() {
        const float angularAcceleration = -cfg.constant * std::sin(theta);
        thetaPrime += angularAcceleration * frameLen;
        theta += thetaPrime * frameLen;
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    constexpr Config cfg = {
        .length = height / 2.5f,
        .initialTheta = PI / 4.0f,
        .constant = 5.0f,
    };

    constexpr LookAndFeel look = {
        .center = {width / 2.0f, height / 2.0f},
        .armWidth = height / 150.f,
        .radius = 50.0f,

        .centerColor = catpuccin::lavender,
        .armColor = catpuccin::blue,
        .ballColor = catpuccin::teal,
    };

    Pendulum p(cfg, look);

    while (!WindowShouldClose()) {
        p.render();
        p.update();
    }

    CloseWindow();
}
