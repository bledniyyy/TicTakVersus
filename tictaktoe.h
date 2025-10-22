#include <vector>
#include <QDebug>
#include <QMetaEnum>
#include <algorithm>

enum class Player {
    X = 1,
    Y = 2
};

enum class ComputerVsPlayer {
    COMPUTER = 2,
    PLAYERc = 1
};


class Tiktaktoe {

private:
    Player player;
    ComputerVsPlayer AIplayer;
    int row;
    int col;
    std::vector<std::vector<int>> field;

public:
    Tiktaktoe() {
        field = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
    }

    void PointToFied (int x, int y, int player) {
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            qDebug() << "PIZDA\n";
        }
        
        field[x][y] = player;
    }

    int CheckPoint (int x, int y) const {
        return field[x][y];
    }

    const bool CheckWin  (const std::vector<std::vector<int>>& field, int player) const {
        return CheckRols(field,player) || CheckCols(field,player) || 
           CheckMainDiagonal(field,player) || CheckPobDiagonal(field,player);
    }

    bool CheckRols (const std::vector<std::vector<int>>& field ,int player) const {
        if (field.empty() || field.size() != 3) return false;
        for (int i = 0; i < 3; i++) {
            if (field[i].size() != 3) continue;

            if (field[i][0] == player && field[i][1] == player && field[i][2] == player) {
                qDebug() << "are you here";
                return true;
            }
        }
        return false;
    }

    bool CheckCols (const std::vector<std::vector<int>>& field ,int player) const {
        if (field.empty() || field.size() != 3) return false;
        for (int j = 0; j < 3; j++) {
            if (field[j].size() != 3) continue;

            if (field[0][j] == player && field[1][j] == player && field[2][j] == player) {
                qDebug() << "are you here";
                return true;
            }
        }
        return false;
    }

    bool CheckMainDiagonal (const std::vector<std::vector<int>>& field ,int player) const {
        if (field.empty() || field.size() != 3) return false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[0][0] == player && field[1][1] == player && field[2][2] == player) {
                    return true;
                }
            }
        }
        
        return false;  
    }
    bool CheckPobDiagonal  (const std::vector<std::vector<int>>& field,int player) const {
        if (field.empty() || field.size() != 3) return false;
        if (field[0][2] == player && field[1][1] == player && field[2][0] == player) {
            return true;
        }
        return false; 
    }

    bool checkAllCells() {
        return std::all_of(field.begin(), field.end(), [](const std::vector<int>& row) {
            return std::all_of(row.begin(), row.end(), [](int cell) {
                return cell != 0;
            });
        });
    }



 int minimax(std::vector<std::vector<int>> field, int depth, bool isAI)
{ 
    
    if (CheckWin(field, static_cast<int>(ComputerVsPlayer::COMPUTER))) {
        return 10 - depth; 
    }
    if (CheckWin(field, static_cast<int>(ComputerVsPlayer::PLAYERc))) {
        return depth - 10; 
    }
    
    
    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == 0) {
                isFull = false;
                break;
            }
        }
        if (!isFull) break;
    }
    
    if (isFull) {
        return 0; 
    }
    
    if (isAI) {
        int bestScore = -999;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] == 0) {
                    field[i][j] = static_cast<int>(ComputerVsPlayer::COMPUTER);
                    int score = minimax(field, depth + 1, false);
                    field[i][j] = 0;
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 999;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] == 0) {
                    field[i][j] = static_cast<int>(ComputerVsPlayer::PLAYERc);
                    int score = minimax(field, depth + 1, true);
                    field[i][j] = 0;
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

int bestMove(int moveIndex)
{   
    int x = -1, y = -1;
    int bestScore = -999;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == 0) {
                field[i][j] = static_cast<int>(ComputerVsPlayer::COMPUTER);
                int score = minimax(field, moveIndex + 1, false);
                field[i][j] = 0;
                
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    
    
    if (x == -1 || y == -1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] == 0) {
                    x = i;
                    y = j;
                    break;
                }
            }
            if (x != -1) break;
        }
    }
    
    return x * 3 + y;
}


std::vector<std::vector<int>> returnField() {
	return field;
}
};

