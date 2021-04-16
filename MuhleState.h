//
// Created by Daniel Naro on 4/10/2021.
//

#ifndef MUHLEALPHABETA_MUHLESTATE_H
#define MUHLEALPHABETA_MUHLESTATE_H


#include <cstdint>
#include <vector>
#include <array>
#include "Action.h"

#define memory_size 1

enum phase {
    phase0,
    phase1,
    phase2
};

typedef std::array<std::array<uint8_t, 24>, memory_size> Boards;

class MuhleState {
private:
    Boards boards{};
    phase phasePlayer1;
    phase phasePlayer2;
    uint8_t lostPieces_player1;
    uint8_t lostPieces_player2;
    uint8_t playerToPlay;
    std::vector<Action> legalActions;
    bool final;
    uint8_t winner;
    uint8_t nextPlayer() const;
public:
    MuhleState();
    MuhleState playAction(Action action);
    std::vector<Action> getLegalActions() const;

    MuhleState(const Boards &boards, phase phasePlayer1, phase phasePlayer2, uint8_t lostPiecesPlayer1,
               uint8_t lostPiecesPlayer2, uint8_t playerToPlay, std::vector<Action> legalActions, bool final,
               uint8_t winner);

    bool isFinal();

    bool operator==(const MuhleState &rhs) const;

    bool operator!=(const MuhleState &rhs) const;

    bool operator<(const MuhleState &rhs) const;

    bool operator>(const MuhleState &rhs) const;

    bool operator<=(const MuhleState &rhs) const;

    bool operator>=(const MuhleState &rhs) const;
};


#endif //MUHLEALPHABETA_MUHLESTATE_H
