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

static constexpr float earthAcceleration = 9.8f;  // m.s-2

static constexpr float scalingFactor = 100.0f;  // pixels per cm
constexpr float pixels(Length l) {
    return scalingFactor * l.as_millis() / 10.0f;
}

constexpr float degreesToRadians(float deg) {
    return deg * PI / 180.0f;
}

struct Config {
    Length length1;
    float initialThetaDeg1;
    Mass mass1;

    Length length2;
    float initialThetaDeg2;
    Mass mass2;

    float constant;
};

struct LookAndFeel {
    Vec2 center;
    float armWidth;
    float radius;

    Color centerColor;
    Color armColor1;
    Color ballColor1;
    Color armColor2;
    Color ballColor2;
    Color backgroundColor;
};

struct Pendulum {
    Pendulum(Config cfg, LookAndFeel look)
        : cfg(cfg),
          look(look),
          theta1(degreesToRadians(cfg.initialThetaDeg1)),
          thetaPrime1(0),
          ball1{0, 0},
          theta2(degreesToRadians(cfg.initialThetaDeg2)),
          thetaPrime2(0),
          ball2{0, 0} {
        const Vec2 axial1 = {std::sin(theta1), std::cos(theta1)};
        ball1 = look.center + axial1.scaled(pixels(cfg.length1));
        const Vec2 axial2 = {std::sin(theta2), std::cos(theta2)};
        ball2 = ball1 + axial2.scaled(pixels(cfg.length2));
    }

    const Config cfg;
    const LookAndFeel look;
    float theta1;
    float thetaPrime1;
    Vec2 ball1;
    float theta2;
    float thetaPrime2;
    Vec2 ball2;

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
        this->renderArm(look.center, ball1, look.armColor1);
        this->renderArm(ball1, ball2, look.armColor2);
        DrawCircleV(look.center.get(), look.armWidth, look.centerColor);
        DrawCircleV(ball1.get(), look.radius, look.ballColor1);
        DrawCircleV(ball2.get(), look.radius, look.ballColor2);

        EndDrawing();
    }

    void update() {
        const float angularAcceleration = -cfg.constant * std::sin(theta1);
        thetaPrime1 += angularAcceleration * frameLen;
        theta1 += thetaPrime1 * frameLen;

        const Vec2 axial = {std::sin(theta1), std::cos(theta1)};
        ball1 = look.center + axial.scaled(pixels(cfg.length1));
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    constexpr Config cfg = {
        .length1 = Length::from_millis(20.0f),
        .initialThetaDeg1 = 45.0f,
        .mass1 = Mass::from_grams(200),

        .length2 = Length::from_millis(20.0f),
        .initialThetaDeg2 = -45.0f,
        .mass2 = Mass::from_grams(200),

        .constant = 5.0f,
    };

    constexpr LookAndFeel look = {
        .center = {width / 2.0f, height / 2.0f},
        .armWidth = height / 270.f,
        .radius = 20.0f,

        .centerColor = catpuccin::lavender,
        .armColor1 = catpuccin::blue,
        .ballColor1 = catpuccin::teal,
        .armColor2 = catpuccin::peach,
        .ballColor2 = catpuccin::red,
        .backgroundColor = catpuccin::darkGray,
    };

    Pendulum p(cfg, look);

    while (!WindowShouldClose()) {
        p.render();
        // p.update();
    }

    CloseWindow();
}
