#include <cmath>
#include <random>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"
#include "catpuccin.hpp"
#include "quantities.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;

static constexpr int targetFps = 60;
static constexpr float frameLen = 1.0 / targetFps;

static constexpr float earthAcceleration = 2.8f;  // m.s-2

static constexpr float scalingFactor = 25.0f;  // pixels per cm
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
        // all in SI units
        const float dTh = theta1 - theta2;
        constexpr float g = earthAcceleration;
        const float l1 = cfg.length1.si();
        const float l2 = cfg.length2.si();
        const float m1 = cfg.mass1.si();
        const float m2 = cfg.mass2.si();
        const float w1 = thetaPrime1;
        const float w2 = thetaPrime2;

        float numerator1 = -2.0f * std::sin(dTh) * m2 *
                           (l2 * w2 * w2 + l1 * w1 * w1 * std::cos(dTh));
        numerator1 += -g * (2 * m1 + m2) * std::sin(theta1);
        numerator1 += -m2 * g * std::sin(theta1 - 2.0f * theta2);
        const float denominator1 =
            l1 * (2.0f * m1 + m2 * (1.0f - std::cos(2.0f * dTh)));
        const float angularAcceleration1 = numerator1 / denominator1;

        float numerator2 = 2.0f * std::sin(dTh) *
                           (std::cos(theta1) + l1 * w1 * w1 * (m1 + m2)) * g *
                           (m1 + m2);
        numerator2 += l2 * m2 * w2 * w2 * std::cos(dTh);
        const float denominator2 =
            l2 * (2.0f * m1 + m2 * (1.0f - std::cos(2.0f * dTh)));
        const float angularAcceleration2 = numerator2 / denominator2;

        thetaPrime1 += angularAcceleration1 * frameLen;
        theta1 += thetaPrime1 * frameLen;
        thetaPrime2 += angularAcceleration2 * frameLen;
        theta2 += thetaPrime2 * frameLen;

        const Vec2 axial1 = {std::sin(theta1), std::cos(theta1)};
        ball1 = look.center + axial1.scaled(pixels(cfg.length1));
        const Vec2 axial2 = {std::sin(theta2), std::cos(theta2)};
        ball2 = ball1 + axial2.scaled(pixels(cfg.length2));
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> angleRng(
        0, 360);  // distribution in range [0, 360]

    const Config cfg = {
        .length1 = Length::from_millis(80.0f),
        .initialThetaDeg1 = static_cast<float>(angleRng(rng)),
        .mass1 = Mass::from_grams(100),

        .length2 = Length::from_millis(80.0f),
        .initialThetaDeg2 = static_cast<float>(angleRng(rng)),
        .mass2 = Mass::from_grams(100),

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
        p.update();
    }

    CloseWindow();
}
