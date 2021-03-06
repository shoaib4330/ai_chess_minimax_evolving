#include "../Headers/ChessState.h"
#include <iostream>
#include <vector>
using namespace std;

bool ChessState::makeMove(ChessMove pieceMove) {
    this->playerToMove *= -1;
    this->board[pieceMove.To[0]][pieceMove.To[1]] = this->board[pieceMove.From[0]][pieceMove.From[1]];
    this->board[pieceMove.From[0]][pieceMove.From[1]] =0;
    return true;
}

int ChessState ::getQueensNum(int playerIndex) {
    int piece=0;
    int count=0;
    if (playerIndex==+1)
        piece=5;
    else
        piece=-5;

    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}

int ChessState ::getBishopsNum(int playerIndex) {
    int piece=0;
    int count=0;
    if (playerIndex==+1)
        piece=3;
    else
        piece=-3;

    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}

int ChessState ::getKnightsNum(int playerIndex) {
    int piece=0;
    int count=0;
    if (playerIndex==+1)
        piece=2;
    else
        piece=-2;

    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}

int ChessState ::getPawnsNum(int playerIndex) {
    int piece=0;
    int count=0;
    if (playerIndex==+1)
        piece=1;
    else
        piece=-1;

    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}

int ChessState ::getRooksNum(int playerIndex) {
    int piece=0;
    int count=0;
    if (playerIndex==+1)
        piece=4;
    else
        piece=-4;

    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}

ChessState ChessState::nextState(ChessMove gChessMove) {
    ChessState newChessState = *this;
    newChessState.makeMove(gChessMove);
    return newChessState;
}

int ChessState::getPlayerToMove(){
    return this->playerToMove;
}

void ChessState::setPlayerToMove(int givenPlayer){
    this->playerToMove=givenPlayer;
}

int ChessState::getPlayerColorAtIndex(int aBoard[][8], int i, int j) {
    if (i >= 8 || j >= 8 || i < 0 || j < 0)
        cout << endl << "Error: ChessState: Method: getPlayerColorAtIndex(): Index out of Bound";
    if (aBoard[i][j] < 0)
        return -1;
    else if (aBoard[i][j] == 0)
        return 0;
    else
        return +1;

}

bool ChessState::checkForPawn(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {
    int PlayerGoatsSpecifier = this->playerToMove;
    if (currentPieceInteger == 1 || currentPieceInteger == -1) {
        //Its a PYADA...Can only move Forward
        if (currentPieceInteger == 1 && PlayerGoatsSpecifier > 0) {
            //Its White player...Will Need Decrement For Moving..
            if (fromRow > 6) {
                cout << endl << "isTraversalPossible: White Pawn cannot be at Row>7";
                return false;
            } else if (fromRow == 0) {
                //Cannot go forward Move not possible for you..Cannot go back either...
                return false;
            } else if (toRow < 0) {
                cout << endl << "isTraversalPossible: White Pawn cannot move to Row>7";
                return false;
            }

            if (fromRow == 6) {
                if (fromRow - toRow == 1 || fromRow - toRow == 2) {
                    //Move is allowed oneNext and 2Next...Assuming Straight movement at the moment...
                    if (fromCol == toCol) {
                        if (fromRow - toRow == 2) {
                            if (this->board[fromRow - 1][fromCol] == 0 && this->board[fromRow - 2][fromCol] == 0) {
                                return true;
                            } else {
                                return false;
                            }
                        } else if (fromRow - toRow == 1) {
                            if (this->board[fromRow - 1][fromCol] == 0) {
                                return true;
                            }
                        }
                        return false;
                    } else if (fromCol != toCol && fromRow - toRow == 1) {
                        //When it wants to move in Diagonal...
                        int absDiff = abs(fromCol - toCol);
                        if (absDiff == 1) {
                            if (this->board[toRow][toCol] != 0 &&
                                (getPlayerColorAtIndex(this->board, fromRow, fromCol)) !=
                                (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                                return true;
                            } else if ((getPlayerColorAtIndex(this->board, fromRow, fromCol)) ==
                                       (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                                return false;
                            }
                            return false;

                        } else {
                            return false;
                        }

                    }
                    return false;
                }
                return false;
            } else if (fromRow - toRow == 1) {
                //Move is allowed oneNext and 2Next...Assuming Straight movement at the moment...
                if (fromCol == toCol) {
                    if (fromRow - toRow == 2) {
                        if (this->board[fromRow - 1][fromCol] == 0 && this->board[fromRow - 2][fromCol] == 0) {
                            return true;
                        } else {
                            return false;
                        }
                    } else if (fromRow - toRow == 1) {
                        if (this->board[fromRow - 1][fromCol] == 0) {
                            return true;
                        }
                    }
                    return false;
                } else if (fromCol != toCol && fromRow - toRow == 1) {
                    //When it wants to move in Diagonal...
                    int absDiff = abs(fromCol - toCol);
                    if (absDiff == 1) {
                        if (this->board[toRow][toCol] != 0 && (getPlayerColorAtIndex(this->board, fromRow, fromCol)) !=
                                                              (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                            return true;
                        } else if ((getPlayerColorAtIndex(this->board, fromRow, fromCol)) ==
                                   (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                            return false;
                        }
                        return false;
                    } else {
                        return false;
                    }

                }
            } else {
                return false;
            }

        } else if (currentPieceInteger == -1 && PlayerGoatsSpecifier < 0) {
            //Its White player...Will Need Decrement For Moving..
            if (fromRow < 1) {
                //--cout << endl << "isTraversalPossible: Black Pawn cannot be at Row<1";
                return false;
            } else if (fromRow == 7) {
                //Cannot go forward Move not possible for you..Cannot go back either...
                return false;
            } else if (toRow < 1) {
                //--cout << endl << "isTraversalPossible: Black Pawn cannot move to Row<1";
                return false;
            }

            if (fromRow == 1) {
                if (toRow - fromRow == 1 || toRow - fromRow == 2) {
                    //Move is allowed oneNext and 2Next...Assuming Straight movement at the moment...
                    if (fromCol == toCol) {
                        if (toRow - fromRow == 2) {
                            if (this->board[fromRow + 1][fromCol] == 0 && this->board[fromRow + 2][fromCol] == 0) {
                                return true;
                            } else {
                                return false;
                            }
                        } else if (toRow - fromRow == 1) {
                            if (this->board[fromRow + 1][fromCol] == 0) {
                                return true;
                            }
                        }
                        return false;
                    } else if (fromCol != toCol && toRow - fromRow == 1) {
                        //When it wants to move in Diagonal...
                        int absDiff = abs(fromCol - toCol);
                        if (absDiff == 1) {
                            if (this->board[toRow][toCol] != 0 &&
                                (getPlayerColorAtIndex(this->board, fromRow, fromCol)) !=
                                (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                                return true;
                            } else if ((getPlayerColorAtIndex(this->board, fromRow, fromCol)) ==
                                       (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                                return false;
                            }
                            return false;

                        } else {
                            return false;
                        }

                    }
                    return false;
                }
                return false;
            } else if (toRow - fromRow == 1) {
                //Move is allowed oneNext...Assuming Straight movement at the moment...
                if (fromCol == toCol) {
                    if (toRow - fromRow == 2) {
                        if (this->board[fromRow + 1][fromCol] == 0 && this->board[fromRow + 2][fromCol] == 0) {
                            return true;
                        } else {
                            return false;
                        }
                    } else if (toRow - fromRow == 1) {
                        if (this->board[fromRow + 1][fromCol] == 0) {
                            return true;
                        }
                    }
                    return false;
                } else if (fromCol != toCol && toRow - fromRow == 1) {
                    //When it wants to move in Diagonal...
                    int absDiff = abs(fromCol - toCol);
                    if (absDiff == 1) {
                        if (this->board[toRow][toCol] != 0 && (getPlayerColorAtIndex(this->board, fromRow, fromCol)) !=
                                                              (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                            return true;
                        } else if ((getPlayerColorAtIndex(this->board, fromRow, fromCol)) ==
                                   (getPlayerColorAtIndex(this->board, toRow, toCol))) {
                            return false;
                        }
                        return false;
                    } else {
                        return false;
                    }

                }
            } else {
                return false;
            }
        }
    }
    return false;
}

bool ChessState::checkForRook(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {
    int PlayerGoatsSpecifier = this->playerToMove;
    if (currentPieceInteger == 4 || currentPieceInteger == -4) {
        //Its a Qilla/Rook.....
        if (currentPieceInteger == 4 && PlayerGoatsSpecifier > 0) {
            //Its White player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                if (fromCol == toCol) {
                    if (toRow > fromRow) {
                        for (int i = fromRow + 1; i <= toRow; ++i) {
                            if (i == toRow) {
                                if (getPlayerColorAtIndex(this->board, i, fromCol) == 0 ||
                                    getPlayerColorAtIndex(this->board, i, fromCol) == -1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[i][fromCol] != 0) {
                                return false;
                            }
                        }
                    } else if (fromRow > toRow) {
                        for (int i = fromRow - 1; i >= toRow; --i) {
                            if (i == toRow) {
                                if (getPlayerColorAtIndex(this->board, i, fromCol) == 0 ||
                                    getPlayerColorAtIndex(this->board, i, fromCol) == -1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[i][fromCol] != 0) {
                                return false;
                            }
                        }
                    } else {
                        return false;
                    }
                } else if (fromRow == toRow) {
                    //Handles column wala scene...
                    if (toCol > fromCol) {
                        for (int i = fromCol + 1; i <= toCol; ++i) {
                            if (i == toCol) {
                                if (getPlayerColorAtIndex(this->board, fromRow, i) == 0 ||
                                    getPlayerColorAtIndex(this->board, fromRow, i) == -1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[fromRow][i] != 0) {
                                return false;
                            }
                        }
                    } else if (fromCol > toCol) {
                        for (int i = fromCol - 1; i >= toCol; --i) {
                            if (i == toCol) {
                                if (getPlayerColorAtIndex(this->board, i, fromCol) == 0 ||
                                    getPlayerColorAtIndex(this->board, i, fromCol) == -1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[i][fromCol] != 0) {
                                return false;
                            }
                        }
                    } else {
                        return false;
                    }

                } else {
                    return false;
                }

            }

        } else if (currentPieceInteger == -4 && PlayerGoatsSpecifier < 0) {
            //Its Black player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                if (fromCol == toCol) {
                    if (toRow > fromRow) {
                        for (int i = fromRow + 1; i <= toRow; ++i) {
                            if (i == toRow) {
                                if (getPlayerColorAtIndex(this->board, i, fromCol) == 0 ||
                                    getPlayerColorAtIndex(this->board, i, fromCol) == +1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[i][fromCol] != 0) {
                                return false;
                            }
                        }
                    } else if (fromRow > toRow) {
                        for (int i = fromRow - 1; i >= toRow; --i) {
                            if (i == toRow) {
                                if (getPlayerColorAtIndex(this->board, i, fromCol) == 0 ||
                                    getPlayerColorAtIndex(this->board, i, fromCol) == +1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[i][fromCol] != 0) {
                                return false;
                            }
                        }
                    } else {
                        return false;
                    }
                } else if (fromRow == toRow) {
                    //Handles column wala scene...
                    if (toCol > fromCol) {
                        for (int i = fromCol + 1; i <= toCol; ++i) {
                            if (i == toCol) {
                                if (getPlayerColorAtIndex(this->board, fromRow, i) == 0 ||
                                    getPlayerColorAtIndex(this->board, fromRow, i) == +1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[fromRow][i] != 0) {
                                return false;
                            }
                        }
                    } else if (toCol < fromCol) {
                        for (int i = fromCol - 1; i >= toCol; --i) {
                            if (i == toCol) {
                                if (getPlayerColorAtIndex(this->board, fromRow, i) == 0 ||
                                    getPlayerColorAtIndex(this->board, fromRow, i) == +1) {
                                    return true;
                                }
                                return false;
                            } else if (this->board[fromRow][i] != 0) {
                                return false;
                            }
                        }
                    } else {
                        return false;
                    }

                } else {
                    return false;
                }

            }
        }
    }
    return false;
}

bool ChessState::checkForBishop(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {
    int PlayerGoatsSpecifier = this->playerToMove;
    if (currentPieceInteger == 3 || currentPieceInteger == -3) {
        //Its a Toap/Bishop.....
        if (currentPieceInteger == 3 && PlayerGoatsSpecifier > 0) {
            //Its White player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                if (fromCol != toCol && fromRow != toRow && board[fromRow][fromCol] > 0) {

                    if (fromRow > toRow) {
                        if (fromCol > toCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol - 1; i >= toCol; --i) {
                                currentRow--;

                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == -1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        } else if (toCol > fromCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol + 1; i <= toCol; ++i) {
                                currentRow--;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == -1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        }
                        return false;
                    } else if (toRow > fromRow) {
                        if (fromCol > toCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol - 1; i >= toCol; --i) {
                                currentRow++;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == -1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        } else if (toCol > fromCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol + 1; i <= toCol; ++i) {
                                currentRow++;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == -1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        }
                    }
                    return false;
                } else {
                    return false;
                }

            }

        } else if (currentPieceInteger == -3 && PlayerGoatsSpecifier < 0) {
            //Its Black player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                if (fromCol != toCol && fromRow != toRow && board[fromRow][fromCol] < 0) {

                    if (fromRow > toRow) {
                        if (fromCol > toCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol - 1; i >= toCol; --i) {
                                currentRow--;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == +1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        } else if (toCol > fromCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol + 1; i <= toCol; ++i) {
                                currentRow--;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == +1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        }
                        return false;
                    } else if (toRow > fromRow) {
                        if (fromCol > toCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol - 1; i >= toCol; --i) {
                                currentRow++;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == +1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        } else if (toCol > fromCol) {
                            int currentRow = fromRow;
                            for (int i = fromCol + 1; i <= toCol; ++i) {
                                currentRow++;
                                if (i == toCol && currentRow == toRow) {
                                    if (this->board[currentRow][i] == 0 ||
                                        getPlayerColorAtIndex(this->board, currentRow, i) == +1) {
                                        return true;
                                    }
                                    return false;
                                }
                                if (this->board[currentRow][i] != 0) {
                                    return false;
                                }
                            }
                            return false;
                        }
                    }
                    return false;
                } else {
                    return false;
                }

            }
        }
    }
    return false;
}

bool ChessState::checkForKnight(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {

    int PlayerGoatsSpecifier = this->playerToMove;
    if (currentPieceInteger == 2 || currentPieceInteger == -2) {
        //Its a knight.....
        if (currentPieceInteger == 2 && PlayerGoatsSpecifier > 0) {
            //Its White player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                //Main White Logic Comes Here.....
                if (fromRow != toRow && fromCol != toCol) {
                    if (fromRow > toRow) {
                        if (fromCol > toCol) {
                            int ToCol_two_move = fromCol - 2;
                            int ToCol_one_move = fromCol - 1;
                            if (ToCol_one_move < 0) {
                                return false;
                            }

                            if (ToCol_one_move >= 0) {
                                if (fromRow - 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow - 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move >= 0) {
                                if (ToCol_two_move == toCol && fromRow - 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                        return true;
                                    }
                                }
                            }
                        } else if (toCol > fromCol) {
                            int ToCol_two_move = fromCol + 2;
                            int ToCol_one_move = fromCol + 1;
                            if (ToCol_one_move >= 8) {
                                return false;
                            }

                            if (ToCol_one_move <= 7) {
                                if (fromRow - 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow - 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move <= 7) {
                                if (ToCol_two_move == toCol && fromRow - 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                        return true;
                                    }
                                }
                            }
                        }
                    } else if (toRow > fromRow) {
                        if (fromCol > toCol) {
                            int ToCol_one_move = fromCol - 1;
                            int ToCol_two_move = fromCol - 2;

                            if (ToCol_one_move < 0) {
                                return false;
                            }

                            if (ToCol_one_move >= 0) {
                                if (fromRow + 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow + 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move >= 0) {
                                if (ToCol_two_move == toCol && fromRow + 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                        return true;
                                    }
                                }
                            }

                        } else if (toCol > fromCol) {
                            int ToCol_two_move = fromCol + 2;
                            int ToCol_one_move = fromCol + 1;

                            if (ToCol_one_move >= 8) {
                                return false;
                            }

                            if (ToCol_one_move <= 7) {
                                if (fromRow + 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow + 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move <= 7) {
                                if (ToCol_two_move == toCol && fromRow + 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == -1) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        } else if (currentPieceInteger == -2 && PlayerGoatsSpecifier < 0) {
            //Its Black player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0)) {
                //Now we know current position and targeted positions are in bounds
                //Main White Logic Comes Here.....
                if (fromRow != toRow && fromCol != toCol) {
                    if (fromRow > toRow) {
                        if (fromCol > toCol) {
                            int ToCol_two_move = fromCol - 2;
                            int ToCol_one_move = fromCol - 1;
                            if (ToCol_one_move < 0) {
                                return false;
                            }

                            if (ToCol_one_move >= 0) {
                                if (fromRow - 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow - 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move >= 0) {
                                if (ToCol_two_move == toCol && fromRow - 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                        return true;
                                    }
                                }
                            }
                        } else if (toCol > fromCol) {
                            int ToCol_two_move = fromCol + 2;
                            int ToCol_one_move = fromCol + 1;
                            if (ToCol_one_move >= 8) {
                                return false;
                            }

                            if (ToCol_one_move <= 7) {
                                if (fromRow - 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow - 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move <= 7) {
                                if (ToCol_two_move == toCol && fromRow - 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                        return true;
                                    }
                                }
                            }
                        }
                    } else if (toRow > fromRow) {
                        if (fromCol > toCol) {
                            int ToCol_one_move = fromCol - 1;
                            int ToCol_two_move = fromCol - 2;

                            if (ToCol_one_move < 0) {
                                return false;
                            }

                            if (ToCol_one_move >= 0) {
                                if (fromRow + 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow + 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move >= 0) {
                                if (ToCol_two_move == toCol && fromRow + 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                        return true;
                                    }
                                }
                            }

                        } else if (toCol > fromCol) {
                            int ToCol_two_move = fromCol + 2;
                            int ToCol_one_move = fromCol + 1;

                            if (ToCol_one_move >= 8) {
                                return false;
                            }

                            if (ToCol_one_move <= 7) {
                                if (fromRow + 2 == toRow) {
                                    if (toCol == ToCol_one_move && fromRow + 2 == toRow) {
                                        if (this->board[toRow][toCol] == 0 ||
                                            getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                            return true;
                                        }
                                    }
                                }
                            }

                            if (ToCol_two_move <= 7) {
                                if (ToCol_two_move == toCol && fromRow + 1 == toRow) {
                                    if (this->board[toRow][toCol] == 0 ||
                                        getPlayerColorAtIndex(this->board, toRow, toCol) == +1) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    return false;
}

bool ChessState::checkForKing(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {
    int PlayerGoatsSpecifier = this->playerToMove;
    if (currentPieceInteger == 6 || currentPieceInteger == -6)
    {
        //Its a knight.....
        if (currentPieceInteger == 6 && PlayerGoatsSpecifier > 0)
        {
            //Its White player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0))
            {
                if (toRow==fromRow-1)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    if (toCol==fromCol && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    return false;
                }
                else if(toRow==fromRow+1)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    if (toCol==fromCol && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    return false;
                }
                else if (toRow==fromRow)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==-1))
                    {
                        return true;
                    }
                }
                else{
                    return false;
                }
            }
        }
        if (currentPieceInteger == -6 && PlayerGoatsSpecifier < 0)
        {
            //Its Black player...
            if ((fromRow < 8 && fromRow >= 0) && (toRow < 8 && toRow >= 0) && (fromCol < 8 && fromCol >= 0) &&
                (toCol < 8 && toCol >= 0))
            {
                if (toRow==fromRow-1)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    if (toCol==fromCol && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    return false;
                }
                else if(toRow==fromRow+1)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    if (toCol==fromCol && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    return false;
                }
                else if (toRow==fromRow)
                {
                    if (toCol==fromCol-1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                    if (toCol==fromCol+1 && (this->board[toRow][toCol]==0 || getPlayerColorAtIndex(this->board,toRow,toCol)==+1))
                    {
                        return true;
                    }
                }
                else{
                    return false;
                }
            }
        }
    }
    return false;
}

bool ChessState::checkForQueen(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {
    int queenAsBishop;
    int queesAsRook;
    if (this->playerToMove<0){
        queenAsBishop=-3;
        queesAsRook =-4;
    }
    else{
        queenAsBishop=3;
        queesAsRook=-3;
    }
    if (checkForBishop(queenAsBishop,toRow,toCol,fromRow,fromCol)==true || checkForRook(queesAsRook,toRow,toCol,fromRow,fromCol)==true)
    {
        return true;
    }
    return false;
}

bool ChessState::isTraversalPossible(int currentPieceInteger, int toRow, int toCol, int fromRow, int fromCol) {

    if (currentPieceInteger == 1 || currentPieceInteger == -1) {
        return checkForPawn(currentPieceInteger, toRow, toCol, fromRow, fromCol); //Pawn
    } else if (currentPieceInteger == 4 || currentPieceInteger == -4) {
        return checkForRook(currentPieceInteger, toRow, toCol, fromRow, fromCol); //Rook
    } else if (currentPieceInteger == 3 || currentPieceInteger == -3) {
        return checkForBishop(currentPieceInteger, toRow, toCol, fromRow, fromCol);
    } else if (currentPieceInteger == 2 || currentPieceInteger == -2) {
        return checkForKnight(currentPieceInteger, toRow, toCol, fromRow, fromCol);
    } else if (currentPieceInteger == 6 || currentPieceInteger == -6) {
        return checkForKing(currentPieceInteger, toRow, toCol, fromRow, fromCol);
    } else if (currentPieceInteger == 5 || currentPieceInteger == -5){
        return checkForQueen(currentPieceInteger, toRow, toCol, fromRow, fromCol);
    } else if (true) {
        //--cout << endl << "Koi Aur Giiti Agai he";
    }
    return false;
}

void ChessState::addValidCorresspondingMoveForPiece(int pieceRow, int pieceColumn, int originalBoard[][8]) {
    //Making a copy of original board
    int secondaryBoard[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            secondaryBoard[i][j] = originalBoard[i][j];
        }
    }
    //Copy of board obtained......

    //get the integer Representing CurrentPiece
    int currentPieceInteger = originalBoard[pieceRow][pieceColumn];

    for (int k = 0; k < 8; ++k) {
        for (int l = 0; l < 8; ++l) {
            int colorAtTarget = getPlayerColorAtIndex(secondaryBoard, k, l);
            int colorOfOwn = getPlayerColorAtIndex(secondaryBoard, pieceRow, pieceColumn);

            if (colorAtTarget == colorOfOwn) {
                //--cout << endl << "Move not possible, piece of same player already exists at targeted index";
            } else {
                //--cout << endl << "Move might be possible, Adversary exists at targeted index";
                bool toBeAdded = isTraversalPossible(currentPieceInteger, k, l, pieceRow, pieceColumn);
                if (toBeAdded) {
                    if (this->playerToMove==+1 && (pieceRow==0 || pieceRow == 1 || pieceRow ==2) )
                    {
//                        cout<<endl<<"Bleeep: Sign of White but Move's From is of Black"<<endl;
//                        cout<<endl<<"From: "<<pieceRow<<pieceColumn<<" to "<<k<<l<<endl;
//                        cout<<endl<<"Goat is: ";
//                        this->showPiece(board[pieceRow][pieceColumn]);
//                        cout<<endl;
                    }
                    if (this->playerToMove==-1 && (pieceRow==7 || pieceRow == 6 || pieceRow ==5) )
                    {
//                        cout<<endl<<"Bleeep: Sign of Black but Move's From is of White"<<endl;
//                        cout<<endl<<"From: "<<pieceRow<<pieceColumn<<" to "<<k<<l<<endl;
//                        cout<<endl<<"Goat is: ";
//                        this->showPiece(board[pieceRow][pieceColumn]);
//                        cout<<endl;
                    }
                    this->Moves[this->movesCount].From[0] = pieceRow;
                    this->Moves[this->movesCount].From[1] = pieceColumn;
                    this->Moves[this->movesCount].To[0] = k;
                    this->Moves[this->movesCount].To[1] = l;
                    this->movesCount++;
                }
            }

        }
    }


}

int ChessState::makeValidMovesList() {
    // This function must create a list of all valid moves for the player in the current
    // state of the game;
    //  it must return an integer specifying total valid moves in the list
    this->movesCount=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            addValidCorresspondingMoveForPiece(i, j, this->board);
        }
    }


    for (int k = 0; k < movesCount ; ++k) {

        if (movesCount-1-k > k)
        {
            ChessMove tempMove =this->Moves[k];
            this->Moves[k] = this->Moves[movesCount-1-k];
            this->Moves[movesCount-1-k]= tempMove;
        }

    }

    int *arr = new int[movesCount];
    for (int l = 0; l < movesCount ; ++l) {
        arr[l] = l;
    }

    vector<ChessMove> tempArray;
    for (int m = 0; m < movesCount ; ++m) {
        tempArray.push_back(Moves[m]);
    }

    random_shuffle(&arr[0],&arr[movesCount]);

    for (int n = 0; n < movesCount ; ++n) {
        Moves[arr[n]] = tempArray.at(n);
    }
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    shuffle(this->Moves.begin(),this->Moves.end(),default_random_engine(seed));
//
//    vector<ChessMove> tempArray;
//
//    for (int k = 0; k < 200 ; ++k) {
//        if (this->Moves[k].From[0]==0 && this->Moves[k].From[1]==0 && this->Moves[k].To[0]==0 && this->Moves[k].To[1]==0){
//            //continue;
//        }
//        else{
//            tempArray.push_back(this->Moves[k]);
//        }
//    }
//
//    for (int l = 0; l < tempArray.size(); ++l) {
//        this->Moves[l] = tempArray.at(l);
//    }
//
//    for (int m = movesCount; m < 200 ; ++m) {
//        this->Moves[m].From[0]=this->Moves[m].From[1]=this->Moves[m].To[0]=this->Moves[m].To[1]=0;
//    }
//    //The "Moves" array has been shuffled now. the max and min deadlock for repeated moves must be resolved now.

    return this->movesCount;
}

bool ChessState:: isPlayerInCheck(){
    int kingToCheck;
    int kingIndex[2];
    if (this->playerToMove<0)
        kingToCheck=-6;
    else
        kingToCheck=6;

    kingIndex[0] = kingIndex[1] = -1;
    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (kingToCheck==this->board[i][j])
            {
                kingIndex[0]=i;
                kingIndex[1]=j;
            }
        }
    }

    for (int i = 0; i < this->movesCount ; ++i) {
        if (getPlayerColorAtIndex(this->board,kingIndex[0],kingIndex[1]) != getPlayerColorAtIndex(this->board,this->Moves[i].From[0],this->Moves[i].From[1]) )
        {
            if (this->Moves[i].To[0]==kingIndex[0] && this->Moves[i].To[1]==kingIndex[1])
            {
                return true;
            }
        }
    }
    return false;
}

bool ChessState:: isPlayerCheckedMate(){
    int kingToCheck;
    int kingIndex[2];
    if (this->playerToMove<0)
        kingToCheck=-6;
    else
        kingToCheck=6;

    kingIndex[0] = kingIndex[1] = -1;
    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (kingToCheck==this->board[i][j])
            {
                kingIndex[0]=i;
                kingIndex[1]=j;
            }
        }
    }

    ChessState tempoState;
    for (int k = 0; k < 8; ++k) {
        for (int i = 0; i < 8; ++i) {
            tempoState.board[k][i] = this->board[k][i];
        }
    }

    tempoState.addValidCorresspondingMoveForPiece(kingIndex[0],kingIndex[1],tempoState.board);
    ChessMove* possiblMovesForKing = new ChessMove[tempoState.movesCount];
    int totalTruesNeeded = tempoState.movesCount+1;
    int currentTrues =0;
    for (int l = 0; l < tempoState.movesCount ; ++l) {
        possiblMovesForKing[l] = tempoState.Moves[l];
    }

    for (int i = 0; i < this->movesCount ; ++i) {
        if (getPlayerColorAtIndex(this->board,kingIndex[0],kingIndex[1]) != getPlayerColorAtIndex(this->board,this->Moves[i].From[0],this->Moves[i].From[1]) )
        {
            if (this->Moves[i].To[0]==kingIndex[0] && this->Moves[i].To[1]==kingIndex[1])
            {
                currentTrues++;
            }
        }
    }

    for (int m = 0; m < tempoState.movesCount ; ++m) {
        for (int i = 0; i < this->movesCount ; ++i) {
            if (getPlayerColorAtIndex(this->board,kingIndex[0],kingIndex[1]) != getPlayerColorAtIndex(this->board,this->Moves[i].From[0],this->Moves[i].From[1]) )
            {
                if (this->Moves[i].To[0]==possiblMovesForKing[m].To[0] && this->Moves[i].To[1]==possiblMovesForKing[m].To[1])
                {
                    currentTrues++;
                }
            }
        }
    }
    if (totalTruesNeeded==currentTrues)
    {
        return true;
    }
    return false;
}

void ChessState::showMoves() {
    cout << endl << "Total Possible Moves in this State: " << this->movesCount;
    cout << endl;
    for (int i = 0; i < this->movesCount; ++i) {
        cout << "From: " << this->Moves[i].From[0] << this->Moves[i].From[1] << " To: " << this->Moves[i].To[0]
             << this->Moves[i].To[1] << " -- ";
    }
}

void ChessState::showPiece(int pieceCode) {
    if (pieceCode < 0)
        cout << "B";
    else if (pieceCode > 0)
        cout << "W";
    switch (pieceCode) {
        case 0:
            cout << "-";
            break;

        case 1:
        case -1:
            cout << "P";
            break;
        case 2:
        case -2:
            cout << "N";
            break;
        case 3:
        case -3:
            cout << "B";
            break;
        case 4:
        case -4:
            cout << "R";
            break;
        case 5:
        case -5:
            cout << "Q";
            break;
        case 6:
        case -6:
            cout << "K";
            break;
    }
    cout << "\t";
}

void ChessState::showState() {
    cout << endl << "Player To Move:\t";
    if (playerToMove > 0)
        cout << "WHITE" << endl;
    else
        cout << "Black" << endl;

    cout << endl << endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            showPiece(board[i][j]);
        }
        cout << endl << endl;
    }
}

ChessState::ChessState() {
    this->movesCount = 0;

    playerToMove = 1;

    board[0][0] = -4;
    board[0][1] = -2;
    board[0][2] = -3;
    board[0][3] = -5;
    board[0][4] = -6;
    board[0][5] = -3;
    board[0][6] = -2;
    board[0][7] = -4;

    board[1][0] = -1;
    board[1][1] = -1;
    board[1][2] = -1;
    board[1][3] = -1;
    board[1][4] = -1;
    board[1][5] = -1;
    board[1][6] = -1;
    board[1][7] = -1;

    board[2][0] = 0;
    board[2][1] = 0;
    board[2][2] = 0;
    board[2][3] = 0;
    board[2][4] = 0;
    board[2][5] = 0;
    board[2][6] = 0;
    board[2][7] = 0;

    board[3][0] = 0;
    board[3][1] = 0;
    board[3][2] = 0;
    board[3][3] = 0;
    board[3][4] = 0;
    board[3][5] = 0;
    board[3][6] = 0;
    board[3][7] = 0;

    for (int i = 4; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = -board[7 - i][j];
        }
    }
    //board[4][3] = -5;
}
