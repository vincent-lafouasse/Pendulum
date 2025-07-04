#include <cmath>
#include <random>

#include <raylib.h>
#include <raymath.h>

#include "Vec2.hpp"
#include "catpuccin.hpp"
#include "quantities.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;

static constexpr int targetFps = 140;
static constexpr float frameLen = 1.0 / targetFps;

static constexpr float earthAcceleration = 9.8f;  // m.s-2

static constexpr float scalingFactor = 10.0f;  // pixels per cm
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

    bool displayFps;
};

struct Pendulum {
    explicit Pendulum(Config cfg)
        : cfg(cfg),
          theta1(degreesToRadians(cfg.initialThetaDeg1)),
          thetaPrime1(0),
          theta2(degreesToRadians(cfg.initialThetaDeg2)),
          thetaPrime2(0) {}

    const Config cfg;
    float theta1;
    float thetaPrime1;
    float theta2;
    float thetaPrime2;

    static void renderArm(Vec2 from, Vec2 to, Color color, float width) {
        const Vec2 delta = (to - from).normalized().transverse().scaled(width);
        const Vec2 a = from - delta;
        const Vec2 b = from + delta;
        const Vec2 c = to + delta;
        const Vec2 d = to - delta;
        DrawTriangle(a.get(), b.get(), c.get(), color);
        DrawTriangle(c.get(), d.get(), a.get(), color);
    }

    void render(LookAndFeel look) const {
        const Vec2 axial1 = {std::sin(theta1), std::cos(theta1)};
        const Vec2 ball1 = look.center + axial1.scaled(pixels(cfg.length1));
        const Vec2 axial2 = {std::sin(theta2), std::cos(theta2)};
        const Vec2 ball2 = ball1 + axial2.scaled(pixels(cfg.length2));

        ClearBackground(look.backgroundColor);
        BeginDrawing();
        Pendulum::renderArm(look.center, ball1, look.armColor1, look.armWidth);
        Pendulum::renderArm(ball1, ball2, look.armColor2, look.armWidth);
        DrawCircleV(look.center.get(), look.armWidth, look.centerColor);
        DrawCircleV(ball1.get(), look.radius, look.ballColor1);
        DrawCircleV(ball2.get(), look.radius, look.ballColor2);

        if (look.displayFps) {
            DrawFPS(0, 0);
        }

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
        numerator1 += -g * (2.0f * m1 + m2) * std::sin(theta1);
        numerator1 += -m2 * g * std::sin(theta1 - 2.0f * theta2);
        const float denominator1 =
            l1 * (2.0f * m1 + m2 * (1.0f - std::cos(2.0f * dTh)));
        const float angularAcceleration1 = numerator1 / denominator1;

        float numerator2 =
            2.0f * std::sin(dTh) *
            (l1 * w1 * w1 * (m1 + m2) + std::cos(theta1) * g * (m1 + m2) +
             l2 * m2 * w2 * w2 * std::cos(dTh));
        const float denominator2 =
            l2 * (2.0f * m1 + m2 * (1.0f - std::cos(2.0f * dTh)));
        const float angularAcceleration2 = numerator2 / denominator2;

        thetaPrime1 += angularAcceleration1 * frameLen;
        theta1 += thetaPrime1 * frameLen;
        thetaPrime2 += angularAcceleration2 * frameLen;
        theta2 += thetaPrime2 * frameLen;
    }
};

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> angleDistribution(
        0, 360);  // distribution in range [0, 360]

    const Config cfg = {
        .length1 = Length::from_millis(200.0f),
        .initialThetaDeg1 = 170.0f,
        .mass1 = Mass::from_grams(400),

        .length2 = Length::from_millis(200.0f),
        .initialThetaDeg2 = 90.0f,
        .mass2 = Mass::from_grams(400),
    };

    LookAndFeel look = {
        .center = {width / 2.0f, height / 2.0f},
        .armWidth = height / 270.f,
        .radius = 20.0f,

        .centerColor = catpuccin::lavender,
        .armColor1 = catpuccin::blue,
        .ballColor1 = catpuccin::teal,
        .armColor2 = catpuccin::peach,
        .ballColor2 = catpuccin::red,
        .backgroundColor = catpuccin::darkGray,

        .displayFps = false,
    };

    Pendulum p(cfg);

    bool spaceKeyIsDown = false;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_SPACE) && !spaceKeyIsDown) {
            look.displayFps = !look.displayFps;
            spaceKeyIsDown = true;
        } else if (IsKeyUp(KEY_SPACE)) {
            spaceKeyIsDown = false;
        }

        p.render(look);
        p.update();
    }

    CloseWindow();
}
