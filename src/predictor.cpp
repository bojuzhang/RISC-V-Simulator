#include "predictor.hpp"

bool Predictor::predict() {
    return now >= 2;
}

void Predictor::update(bool scc) {
    if (scc && now != 3) now++;
    if ((!scc) && now != 0) now--;
}