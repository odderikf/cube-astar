//
// Created by Odd-Erik on 29.11.2018.
//

#ifndef OVING13_CUBE_H
#define OVING13_CUBE_H

#include <array>
#include <string>
#include <numeric>

template <unsigned int N>
class cube{
public:
    std::array<int, 6*N*N> state;
    enum Face{
        fF=0,
        fB=1,
        fL=2,
        fR=3,
        fU=4,
        fD=5
    };
    enum Move{
        F, Ft, Fp,
        B, Bt, Bp,
        L, Lt, Lp,
        R, Rt, Rp,
        U, Ut, Up,
        M, Mt, Mp,
        S, St, Sp,
        E, Et, Ep
    };
    static constexpr char facenames[6] = {'F', 'B', 'L', 'R', 'U', 'D'};
    static constexpr char movenames[6*3][3] = {
            "F", "F2", "F'",
            "B", "B2", "B'",
            "U", "U2", "U'",
            "D", "D2", "D'",
            "L", "L2", "L'",
            "R", "R2", "R'"
    };
    Face getFaceOn(int index);
    Face getFaceAt(int index);
    int getOffset(Face face);

    cube<N> &move(const Move &m);

    cube();
    explicit cube(std::array<int, 6*N*N> &state);
    explicit cube(std::array<int, 6*N*N> state);

};

template class cube<3u>;

class threebythree : public cube<3>{
public:
    enum piecetype{
        edge,
        corner,
        center
    };
    char indexToSpeffz(int index);
    std::string indexToFacenames(int index); // FL is left edge on F layer, FLD is left bottom corner on F layer.
    int SpeffzToIndex(char speffz, piecetype);
    int ColorsToIndex(std::string facenames);
};


#endif //OVING13_CUBE_H
