//
// Created by Daniel Naro on 4/10/2021.
//

#include "MuhleState.h"

#include <utility>

std::array<std::array<bool, 24>, 24> adjacents = {{
    {false, true, false, false, false, false, false, false, false,
     true, false, false, false,false, false, false, false,false,
     false, false, false, false, false, false},
    {true, false, true, false, true, false, false, false, false,
          false, false, false, false,false, false, false, false,false,
          false, false, false, false, false, false},
    {false, true, false, false, false, false, false, false, false,
          false, false, false, false,false, true, false, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, true, false, false, false, false,
          false, true, false, false,false, false, false, false,false,
          false, false, false, false, false, false},
    {false, true, false, true, false, true, false, true, false,
          false, false, false, false,false, false, false, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, true, false, false, false, false,
          false, false, false, false,true, false, false, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, false, true, false,
          false, false, true, false,false, false, false, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, true, false, true,
          false, false, false, false,false, false, false, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, false, true, false,
          false, false, false, true,false, false, false, false,false,
          false, false, false, false, false, false},
    {true, false, false, false, false, false, false, false, false,
          false, false, false, false,false, false, false, false,false,
          false, false, false, true, false, false},
    {false, false, false, true, false, false, false, false, false,
          true, false, true, false,false, false, false, false,false,
          true, false, false, false, false, false},
    {false, false, false, false, false, false, true, false, false,
          false, true, false, false,false, false, true, false,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, true,
          false, false, false, false,true, false, false, false,true,
          false, false, false, false, false, false},
    {false, false, false, false, false, true, false, false, false,
          false, false, false, true,false, true, false, false,false,
          false, false, true, false, false, false},
    {false, false, true, false, false, false, false, false, false,
          false, false, false, false,true, false, false, false,false,
          false, false, false, false, false, true},
    {false, false, false, false, false, false, false, false, false,
          false, false, true, false,false, false, false, true,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, false,false, false, true, false,true,
          false, true, false, false, false, false},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, true,false, false, false, true,false,
          false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false,
          false, true, false, false,false, false, false, false,false,
          false, true, false, false, false, false},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, false,false, false, false, true,false,
          true, false, true, false, true, false},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, false,true, false, false, false,false,
          false, true, false, false, false, false},
    {false, false, false, false, false, false, false, false, false,
          true, false, false, false,false, false, false, false,false,
          false, false, false, false, true, false},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, false,false, false, false, false,false,
          false, true, false, true, false, true},
    {false, false, false, false, false, false, false, false, false,
          false, false, false, false,false, true, false, false,false,
          false, false, false, false, true, false},
}};

bool validAction(Action action, Boards & boards, uint8_t playerToPlay, phase phasePlayer1, phase phasePlayer2);
bool validActionPhase0(Action action, Boards & boards, uint8_t playerToPlay, uint8_t nextPlayer);
bool validActionPhase1(Action action, Boards & boards, uint8_t playerToPlay, uint8_t nextPlayer);
bool validActionPhase2(Action action, Boards & boards, uint8_t playerToPlay, uint8_t nextPlayer);
uint8_t numberPiecesOfPlayer(std::array<uint8_t, 24> board, uint8_t playerToPlay);


std::array<bool, 16> getCompletedLines(std::array<uint8_t, 24> & board, uint8_t player){
    return std::array<bool, 16>{
            board[0] == player && board[9] == player && board[21] == player,
            board[3] == player && board[10] == player && board[18] == player,
            board[6] == player && board[11] == player && board[15] == player,
            board[1] == player && board[4] == player && board[7] == player,
            board[16] == player && board[19] == player && board[22] == player,
            board[8] == player && board[12] == player && board[17] == player,
            board[5] == player && board[13] == player && board[20] == player,
            board[2] == player && board[14] == player && board[23] == player,
            board[0] == player && board[1] == player && board[2] == player,
            board[3] == player && board[4] == player && board[5] == player,
            board[6] == player && board[7] == player && board[8] == player,
            board[9] == player && board[10] == player && board[11] == player,
            board[12] == player && board[13] == player && board[14] == player,
            board[15] == player && board[16] == player && board[17] == player,
            board[18] == player && board[19] == player && board[20] == player,
            board[21] == player && board[22] == player && board[23] == player,
    };
}

bool partOfLine(std::array<uint8_t, 24> & partial_board, uint8_t player, uint8_t  pieceToEat){
    auto completedLines = getCompletedLines(partial_board, player);
    switch (pieceToEat) {
        case 0:
            return completedLines[0] || completedLines[8];
        case 1:
            return completedLines[3] || completedLines[8];
        case 2:
            return completedLines[7] || completedLines[8];
        case 3:
            return completedLines[1] || completedLines[9];
        case 4:
            return completedLines[3] || completedLines[9];
        case 5:
            return completedLines[6] || completedLines[9];
        case 6:
            return completedLines[2] || completedLines[10];
        case 7:
            return completedLines[3] || completedLines[10];
        case 8:
            return completedLines[5] || completedLines[10];
        case 9:
            return completedLines[0] || completedLines[11];
        case 10:
            return completedLines[1] || completedLines[11];
        case 11:
            return completedLines[2] || completedLines[11];
        case 12:
            return completedLines[5] || completedLines[12];
        case 13:
            return completedLines[6] || completedLines[12];
        case 14:
            return completedLines[7] || completedLines[12];
        case 15:
            return completedLines[2] || completedLines[13];
        case 16:
            return completedLines[4] || completedLines[13];
        case 17:
            return completedLines[5] || completedLines[13];
        case 18:
            return completedLines[1] || completedLines[14];
        case 19:
            return completedLines[4] || completedLines[14];
        case 20:
            return completedLines[6] || completedLines[14];
        case 21:
            return completedLines[0] || completedLines[15];
        case 22:
            return completedLines[4] || completedLines[15];
        case 23:
            return completedLines[7] || completedLines[15];
        default:
            exit(-1);
    }
}

bool isNewLineCompleted(
        std::array<uint8_t, 24> & board,
        std::array<uint8_t, 24> & old_board,
        uint8_t player
){
    auto completedLines = getCompletedLines(board, player);
    auto oldCompletedLines = getCompletedLines(old_board, player);
    for(int i=0; i<16; i++){
        if (completedLines[i] && !oldCompletedLines[i]){
            return true;
        }
    }
    return false;
}

MuhleState::MuhleState() {
    boards = {};
    for (auto & board : boards){
        for (unsigned char & memory : board){
            memory = 0;
        }
    }
    phasePlayer1 = phase0;
    phasePlayer2 = phase0;
    lostPieces_player1 = 0;
    lostPieces_player2 = 0;
    playerToPlay = 1;
    for(int to=0; to<24; to++) {
        legalActions.emplace_back(24, to, 24);
    }
    final = false;
    winner = 0;
}



MuhleState MuhleState::playAction(Action action) {
    if( !validAction(action, boards, playerToPlay, phasePlayer1, phasePlayer2)) {
        exit(-1);
    }
    phase newPhasePlayer1 = phasePlayer1;
    phase newPhasePlayer2 = phasePlayer2;
    uint8_t newLostPiecesPlayer1 = lostPieces_player1;
    uint8_t newLostPiecesPlayer2 = lostPieces_player2;
    bool newFinal = false;
    uint8_t newWinner = 0;

    std::array<std::array<uint8_t,24>, memory_size> newBoards{};
    newBoards[0] = boards[0];
    for(int i=1; i<memory_size; i++){
        newBoards[i] = boards[i-1];
    }
    if(action.getFrom() != 24){
        newBoards[0][action.getFrom()] = 0;
    }
    newBoards[0][action.getTo()] = playerToPlay;
    if(action.getEat() != 24){
        newBoards[0][action.getEat()] = 0;
        if (playerToPlay == 1){
            newLostPiecesPlayer2++;
        } else {
            newLostPiecesPlayer1++;
        }
    }

    if(newPhasePlayer1 == phase0){
        if(numberPiecesOfPlayer(newBoards[0], 1) + lostPieces_player1 == 9){
            newPhasePlayer1 = phase1;
        }
    }else if(newPhasePlayer1 == phase1){
        if(numberPiecesOfPlayer(newBoards[0], 1)==3){
            newPhasePlayer1 = phase2;
        }
    }else{
        if(numberPiecesOfPlayer(newBoards[0], 1)==2){
            newFinal = true;
            newWinner = 2;
        }
    }

    if(newPhasePlayer2 == phase0){
        if(numberPiecesOfPlayer(newBoards[0], 2) + lostPieces_player2 == 9){
            newPhasePlayer2 = phase1;
        }
    }else if(newPhasePlayer2 == phase1){
        if(numberPiecesOfPlayer(newBoards[0], 2)==3){
            newPhasePlayer2 = phase2;
        }
    }else{
        if(numberPiecesOfPlayer(newBoards[0], 2)==2){
            newFinal = true;
            newWinner = 1;
        }
    }

    std::vector<Action> legalMoves;
    for(uint8_t from=0; from<25; from++){
        for(uint8_t to=0; to<24; to++){
            for(uint8_t eat=0; eat<25; eat++){
                Action newAction(from, to, eat);
                if (validAction(newAction, newBoards, nextPlayer(), newPhasePlayer1, newPhasePlayer2)){
                    legalMoves.push_back(newAction);
                }
            }
        }
    }
    if (legalMoves.empty()){
        newFinal = true;
        newWinner = playerToPlay;
    }

    /*if(
        newBoards[0] == newBoards[4]
        && newBoards[1] == newBoards[5]
        && newBoards[2] == newBoards[7]
    ){
        newFinal = true;
    }*/

    return MuhleState(
        newBoards, newPhasePlayer1, newPhasePlayer2, newLostPiecesPlayer1, newLostPiecesPlayer2,
        nextPlayer(), legalMoves, newFinal, newWinner);
}

bool validAction(
        Action action,
        Boards & boards,
        uint8_t playerToPlay,
        phase phasePlayer1,
        phase phasePlayer2
) {
    uint8_t nextPlayer = playerToPlay == 1 ? 2 : 1;
    if(playerToPlay == 1){
        switch (phasePlayer1) {
            case phase0:
                return validActionPhase0(action, boards, playerToPlay, nextPlayer);
            case phase1:
                return validActionPhase1(action, boards, playerToPlay, nextPlayer);
            case phase2:
                return validActionPhase2(action, boards, playerToPlay, nextPlayer);
            default:
                exit(-1);
        }
    } else {
        switch (phasePlayer2) {
            case phase0:
                return validActionPhase0(action, boards, playerToPlay, nextPlayer);
            case phase1:
                return validActionPhase1(action, boards, playerToPlay, nextPlayer);
            case phase2:
                return validActionPhase2(action, boards, playerToPlay, nextPlayer);
            default:
                exit(-1);
        }
    }
}

bool validActionPhase0(
        Action action,
        Boards & boards,
        uint8_t playerToPlay,
        uint8_t nextPlayer
) {
    if (action.getFrom() != 24){
        return false;
    }
    if (boards[0][action.getTo()] != 0){
        return false;
    }

    auto partial_board = boards[0];
    partial_board[action.getTo()] = playerToPlay;

    if (!isNewLineCompleted(partial_board, boards[0], playerToPlay)){
        if (action.getEat() != 24){
            return false;
        }
    }else{
        if (action.getEat() == 24){
            return false;
        }
        if(partial_board[action.getEat()] != nextPlayer){
            return false;
        }
        if(partOfLine(partial_board, nextPlayer, action.getEat())){
            return false;
        }
    }
    return true;
}

bool validActionPhase1(
        Action action,
        Boards & boards,
        uint8_t playerToPlay,
        uint8_t nextPlayer
) {
    if (action.getFrom() == 24){
        return false;
    }
    if(boards[0][action.getFrom()] != playerToPlay){
        return false;
    }
    if (boards[0][action.getTo()] != 0){
        return false;
    }
    if (!adjacents[action.getFrom()][action.getTo()]){
        return false;
    }

    auto partial_board = boards[0];
    partial_board[action.getFrom()] = 0;
    partial_board[action.getTo()] = playerToPlay;

    if (!isNewLineCompleted(partial_board, boards[0], playerToPlay)){
        if (action.getEat() != 24){
            return false;
        }
    }else{
        if (action.getEat() == 24){
            return false;
        }
        if(partial_board[action.getEat()] != nextPlayer){
            return false;
        }
        if(partOfLine(partial_board, nextPlayer, action.getEat())){
            return false;
        }
    }
    return true;
}

bool validActionPhase2(
        Action action,
        Boards & boards,
        uint8_t playerToPlay,
        uint8_t nextPlayer
) {
    if (action.getFrom() == 24){
        return false;
    }
    if(boards[0][action.getFrom()] != playerToPlay){
        return false;
    }
    if (boards[0][action.getTo()] != 0){
        return false;
    }

    auto partial_board = boards[0];
    partial_board[action.getFrom()] = 0;
    partial_board[action.getTo()] = playerToPlay;

    if (!isNewLineCompleted(partial_board, boards[0], playerToPlay)){
        if (action.getEat() != 24){
            return false;
        }
    }else{
        if (action.getEat() == 24){
            return false;
        }
        if(partial_board[action.getEat()] != nextPlayer){
            return false;
        }
        if(partOfLine(partial_board, nextPlayer, action.getEat())){
            return false;
        }
    }
    return true;
}

uint8_t MuhleState::nextPlayer() const {
    if (playerToPlay == 1){
        return 2;
    } else {
        return 1;
    }
}

MuhleState::MuhleState(const Boards &boards, phase phasePlayer1, phase phasePlayer2, uint8_t lostPiecesPlayer1,
                       uint8_t lostPiecesPlayer2, uint8_t playerToPlay, std::vector<Action> legalActions,
                       bool final, uint8_t winner) : boards(boards), phasePlayer1(phasePlayer1),
                                                     phasePlayer2(phasePlayer2), lostPieces_player1(lostPiecesPlayer1),
                                                     lostPieces_player2(lostPiecesPlayer2), playerToPlay(playerToPlay),
                                                     legalActions(std::move(legalActions)), final(final), winner(winner) {}

bool MuhleState::isFinal() {
    return final;
}

std::vector<Action> MuhleState::getLegalActions() const {
    return legalActions;
}

bool MuhleState::operator==(const MuhleState &rhs) const {
    return boards == rhs.boards &&
           phasePlayer1 == rhs.phasePlayer1 &&
           phasePlayer2 == rhs.phasePlayer2 &&
           lostPieces_player1 == rhs.lostPieces_player1 &&
           lostPieces_player2 == rhs.lostPieces_player2 &&
           playerToPlay == rhs.playerToPlay &&
           final == rhs.final &&
           winner == rhs.winner;
}

bool MuhleState::operator!=(const MuhleState &rhs) const {
    return !(rhs == *this);
}

bool MuhleState::operator<(const MuhleState &rhs) const {
    if (boards < rhs.boards)
        return true;
    if (rhs.boards < boards)
        return false;
    if (phasePlayer1 < rhs.phasePlayer1)
        return true;
    if (rhs.phasePlayer1 < phasePlayer1)
        return false;
    if (phasePlayer2 < rhs.phasePlayer2)
        return true;
    if (rhs.phasePlayer2 < phasePlayer2)
        return false;
    if (lostPieces_player1 < rhs.lostPieces_player1)
        return true;
    if (rhs.lostPieces_player1 < lostPieces_player1)
        return false;
    if (lostPieces_player2 < rhs.lostPieces_player2)
        return true;
    if (rhs.lostPieces_player2 < lostPieces_player2)
        return false;
    if (playerToPlay < rhs.playerToPlay)
        return true;
    if (rhs.playerToPlay < playerToPlay)
        return false;
    if (legalActions < rhs.legalActions)
        return true;
    if (rhs.legalActions < legalActions)
        return false;
    if (final < rhs.final)
        return true;
    if (rhs.final < final)
        return false;
    return winner < rhs.winner;
}

bool MuhleState::operator>(const MuhleState &rhs) const {
    return rhs < *this;
}

bool MuhleState::operator<=(const MuhleState &rhs) const {
    return !(rhs < *this);
}

bool MuhleState::operator>=(const MuhleState &rhs) const {
    return !(*this < rhs);
}

uint8_t numberPiecesOfPlayer(std::array<uint8_t, 24> board, uint8_t playerToPlay){
    uint8_t count = 0;
    for(uint8_t position = 0; position < 24; position++){
        if (board[position] == playerToPlay){
            count++;
        }
    }
    return count;
}






