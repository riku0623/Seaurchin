#pragma once

struct SpriteMoverTime {
    double Duration;
    double Wait;
};

struct SpriteMoverData {
    float X;
    float Y;
    float Z;
    float Extra1;
    float Extra2;
    float Extra3;
};

struct SpriteMoverObject {
    SpriteMoverData Data;
    SpriteMoverTime Time;
    double Now;
};

class SSprite;

class ScriptSpriteMover2 final {
private:
    SSprite *Target;
    
    void ApplyProperty(const std::string &prop, const std::string &value);

public:
    ScriptSpriteMover2(SSprite *target);
    ~ScriptSpriteMover2();

    void Tick(double delta);

    void Apply(const std::string &application);
};