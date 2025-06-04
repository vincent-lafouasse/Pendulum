#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"
#include "catpuccin.hpp"
#include "quantities.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;

static constexpr int targetFps = 60;
static constexpr float frameLen = 1.0 / targetFps;

static constexpr float scalingFactor = 100.0f;  // pixels per cm
constexpr float pixels(Length l) {
    return scalingFactor * l.as_millis() / 10.0f;
}

constexpr float degreesToRadians(float deg) {
    return deg * PI / 180.0f;
}

struct Config {
    Length length;
    float initialThetaDeg;
    float constant;
};

struct LookAndFeel {
    Vec2 center;
    float armWidth;
    float radius;

    Color centerColor;
    Color armColor;
    Color ballColor;
    Color backgroundColor;
};

struct Pendulum {
    Pendulum(Config cfg, LookAndFeel look)
        : cfg(cfg),
          look(look),
          theta(degreesToRadians(cfg.initialThetaDeg)),
          thetaPrime(0),
          ball{0, 0} {
        const Vec2 axial = {std::sin(theta), std::cos(theta)};
        ball = look.center + axial.scaled(pixels(cfg.length));
    }

    const Config cfg;
    const LookAndFeel look;
    float theta;
    float thetaPrime;
    Vec2 ball;

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
        ClearBackground(look.backgroundColor);
        BeginDrawing();
        this->renderArm(look.center, ball, look.armColor);
        DrawCircleV(look.center.get(), look.armWidth, look.centerColor);
        DrawCircleV(ball.get(), look.radius, look.ballColor);

        EndDrawing();
    }

    void update() {
        const float angularAcceleration = -cfg.constant * std::sin(theta);
        thetaPrime += angularAcceleration * frameLen;
        theta += thetaPrime * frameLen;
        const Vec2 axial = {std::sin(theta), std::cos(theta)};
        ball = look.center + axial.scaled(pixels(cfg.length));
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    constexpr Config cfg = {
        .length = Length::from_millis(35.0f),
        .initialThetaDeg = 45.0f,
        .constant = 5.0f,
    };

    constexpr LookAndFeel look = {
        .center = {width / 2.0f, height / 2.0f},
        .armWidth = height / 150.f,
        .radius = 50.0f,

        .centerColor = catpuccin::lavender,
        .armColor = catpuccin::blue,
        .ballColor = catpuccin::teal,
        .backgroundColor = catpuccin::darkGray,
    };

    Pendulum p(cfg, look);

    while (!WindowShouldClose()) {
        p.render();
        p.update();
    }

    CloseWindow();
}
