#include "predictor.hpp"
#include <iostream>

bool Predictor::predict() {
    ++tot;
    return now >= 2;
}

void Predictor::update(bool scc) {
    if (!scc) ++loss;
    if (scc && now != 3) now++;
    if ((!scc) && now != 0) now--;
}

void Predictor::show() {{
    std::cerr << "Predictor Performance(loss/tot): " << loss << "/" << tot << "\n"; 
}}