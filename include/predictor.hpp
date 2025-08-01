#pragma once

class Predictor {
private:
    int now;

    int tot = 0, loss = 0;

public:
    bool predict();

    void update(bool);

    void show();
};