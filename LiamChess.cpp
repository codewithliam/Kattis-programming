// LiamChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <cctype>
#include <cmath>

using namespace std;

const enum Piece { King, Queen, Rook, Bishop, Knight, Pawn };
const enum class State { Empty, Friendly, Opponent };

struct Square {
    int x, y;
    bool operator==(const Square& square) {
        return (x == square.x && y == square.y);
    }
};

vector<Square> white_attacked_squares; 
vector<Square> black_attacked_squares; 


class ChessBoard {
public:
    char board[8][8] = {
        {'R', 'F', 'B', 'Q', 'K', 'B', 'F', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'f', 'b', 'q', 'k', 'b', 'f', 'r'}
    };


    const map<char, Piece> sprites =
    {{'P', Piece::Pawn}, {'H', Piece::Rook}, {'F', Piece::Knight},
       {'I',Piece::Bishop}, {'K', Piece::King}, {'Q', Piece::Queen}};

    bool getPiece(Piece& piece_buffer, int from_x, int from_y, bool white_to_play) {
        char piece_char = board[from_y][from_x];

        int checksum = int(white_to_play) + int(isupper(piece_char) != 0);

        if (checksum == 1) {
            piece_buffer = sprites.at(piece_char);
        }
        else { return false; }
        return true;
    }


    void printBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}; 

string makeMove(ChessBoard& chess_board, string move_input, bool white_to_play) {
    int from_x, int from_y, int to_x, int to_y; 
    scanf_s("%d" "%d" "%d" "%d", &from_x, &from_y, &to_x, &to_y); 
    Piece p; 
    bool valid_piece = chess_board.getPiece(p, from_x, from_y, white_to_play); 
    bool valid_move = checkLegalMove(chess_board, p, from_x, from_y, to_x, to_y, white_to_play); 
    
    return "OK"; 
}

bool checkLegalMove(ChessBoard& chess_board, Piece p, int from_x, int from_y, int to_x, int to_y, bool white_to_play) {

    vector<Square> moveable_squares;

    Square from{ from_x, from_y };
    Square to{ to_x, to_y };


    auto Move = [&](int to_x, int to_y, bool white_to_play) {
        State state;
        if (chess_board.board[to_y][to_x] == '.') {
            return state = State::Empty;
        }
        if ((isupper(int(chess_board.board[to_y][to_x])) + int(white_to_play)) == 1) {
            return state = State::Friendly;
        }
        else { return state = State::Opponent;}
        };

    if (Move(to_x, to_y, white_to_play) == State::Friendly) {
        return false; 
    }

        switch (p) {
        case Pawn:
            if (white_to_play) {
                if (Move(from_y + 1, from_x, white_to_play) == State::Empty) {
                    if (from_x == to_x && from_y + 1 == to_y)) {
                        return true; 
                    }
                    if (Move(from_y + 2, from_x, white_to_play) == State::Empty)
                    {
                        if (from_x == to_x && from_y + 2 == to_y from_y == 1) {
                            return true;
                        }
                    } 
                    break;
                }
        //Black to play
            else {
                if (Move(from_y - 1, from_x, white_to_play) == State::Empty) {
                    if (from_x == to_x && from_y - 1 == to_y)) {
                        return true;}

                if (Move(from_y - 2, from_x, white_to_play) == State::Empty) {
                    if (from_x == to_x && from_y == 7 && to_y == 5) {
                        return true;}
                }
            break; 

        case Rook: 

            if (int(from_y == to_y) + int(from_x == to_x) != 1) {
                return false;
            }
            else {
                if (from_y == to_y) {
                    int min_val, max_val;
                    min_val = min(from_x, to_x);
                    max_val = max(from_x_to_x);

                    for (int i = min_val, i < max_val, i++) {
                        if (Move(i, from_y, white_to_play) != State::Empty) {
                            return false;
                        }
                    }
                    return true;

                }

                if (from_x == to_x) {
                    int min_val, max_val;
                    min_val = min(from_y, to_y);
                    max_val = max(from_y, to_y);

                    for (int i = min_val, i < max_val, i++) {
                        if (Move(i, from_x, white_to_play) != State::Empty) {
                            return false;
                        }
                    }
                    return true;
                }
            }

            break; 

        case Bishop: 



int main() {
    //printChessBoard();
    ChessBoard chess_board = ChessBoard();
    char(&board)[8][8] = chess_board.board;

    chess_board.printBoard(); 
    bool game_over = false; 
    bool white_to_play = true; 
    string move_input; 

    while (game_over == false) {
        if (white_to_play) { cout << "white to play";}
        else { cout << "black to play";}
        getline(cin, move_input);
        makeMove()
    }

    return 0;
}