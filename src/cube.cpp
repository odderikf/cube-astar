//
// Created by Odd-Erik on 29.11.2018.
//

#include "cube.h"


template<unsigned int N>
int cube<N>::getOffset(cube::Face face) {
    return face*N*N;
}

template<unsigned int N>
typename cube<N>::Face cube<N>::getFaceOn(int index) {
    return Face(index/(N*N));
}

template<unsigned int N>
typename cube<N>::Face cube<N>::getFaceAt(int index) {
    return Face(state[index]);
}

template<unsigned int N>
cube<N>::cube() {
    std::iota(state.begin(), state.end(), 0);
}

template<unsigned int N>
cube<N>::cube(std::array<int, 6 * N * N> &state) : state(state){}

template<unsigned int N>
cube<N>::cube(std::array<int, 6 * N * N> state) : state(state){}

template<unsigned int N>
cube<N> &cube<N>::move(const cube::Move &m) {
    switch(m){
        case F:break;
        case Ft:break;
        case Fp:break;
        case B:break;
        case Bt:break;
        case Bp:break;
        case L:break;
        case Lt:break;
        case Lp:break;
        case R:break;
        case Rt:break;
        case Rp:break;
        case U:break;
        case Ut:break;
        case Up:break;
        case M:break;
        case Mt:break;
        case Mp:break;
        case S:break;
        case St:break;
        case Sp:break;
        case E:break;
        case Et:break;
        case Ep:break;
    }
    return *this;
}

char threebythree::indexToSpeffz(int index) {
    return char('A'+ index/2);
}