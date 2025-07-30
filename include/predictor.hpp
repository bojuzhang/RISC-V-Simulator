#pragma once

class Predictor {
private:
    int now;

public:
    bool predict();

    void update(bool);
};