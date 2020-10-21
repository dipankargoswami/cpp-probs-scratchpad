#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Player{
public:
    Player() : score_(0) {
    }

    int getScore() {
        return score_;
    }

    void setScore(int score) {
        score_ = score;
    }
private:
    int score_;
    string name_;
};

class PlayerList {
public:
    PlayerList(int num_players) : players_(num_players, Player()) {
    }

    int getPlayerScore(int index) {
        return players_[index].getScore();
    }

    void setPlayerScore(int index, int score) {
        players_[index].setScore(score);
    }

    int getHighestRatedPlayerIndex() {
        int max_score = 0;
        int winning_index = -1;

        for (size_t i = 0; i < players_.size(); i++)
         {
             Player player = players_[i];
            if (player.getScore() > max_score) {
                max_score = player.getScore();
                winning_index = i;
            }
        }
        return winning_index;
    }
private:
    std::vector<Player> players_;
    //int highest_score;
    //int highest_score_index;
};

class LudoBoard {
    public:
    LudoBoard(int start, int end, vector<vector<int>> snakePos, vector<vector<int>> ladderPos) {
        start_ = start;
        end_ = end;

        //Assuming vectors are sanity checked before passing
        for(auto elem: snakePos) {
            destNumberMap_[elem[0]] = elem[1];
        }

        //Giving preference to ladder in case of conflict
        for(auto elem: ladderPos) {
            destNumberMap_[elem[0]] = elem[1];
        }
    }

    int getDestNumber(int start, int increment) {

        int dest = start + increment;

        if (dest > end_) {
            return start;
        }

        //We shouldn't unnecessarily check in the map;
        if (dest == end_) {
            return end_;
        }

        std::map<int, int>::iterator itr = destNumberMap_.find(dest);

        return itr!=destNumberMap_.end() ? itr->second : dest;
    }

    int getEndpoint() {
        return end_;
    }
private:
    int start_;
    int end_;
    std::map<int, int> destNumberMap_;
};

class Dice {
public:
    Dice(int startPoint, int endPoint) : start_point_(startPoint), end_point_(endPoint) {

    }

    int getNextRoll() {
        return rand() % (start_point_ - end_point_) + start_point_;
    }
private:
    int start_point_;
    int end_point_;
};

int main() {
    LudoBoard board(1, 20, {{10, 5}, {15, 2}}, {{11, 15}});

    assert(board.getDestNumber(7,3) == 5);
    assert(board.getDestNumber(7,4) == 15);
    assert(board.getDestNumber(7,5) == 12);
    assert(board.getDestNumber(17,5) == 17);
    assert(board.getDestNumber(17,3) == 20);

    PlayerList plist(3);
    assert(plist.getPlayerScore(0) == 0);
    plist.setPlayerScore(1, 20);
    assert(plist.getPlayerScore(1) == 20);
    assert(plist.getPlayerScore(2) == 0);
    plist.setPlayerScore(1, 0);


    Dice dice(1, 6);

    for(int i = 0; i < 100; i++) {
        int r = dice.getNextRoll();
        assert(r >= 1 && r <= 6);
    }

    int max_score = 0;

    for(int i = 0; i < 50; i++) {
        int player_index = i % 3/*Number of players*/;
        
        int roll = dice.getNextRoll();/*What is the next number*/
        int start_pos = plist.getPlayerScore(player_index);
        int dest = board.getDestNumber(start_pos, roll);

        if(dest == board.getEndpoint()) {
            cout << "Hello Player " << (player_index+1) << ", Congratulations !!!! You have won with the new roll " << roll << endl;
            return EXIT_SUCCESS;
        }
        else {
            cout << "Hello Player " << (player_index+1) << ", your roll is " << roll << " and new score is " << dest << endl;
            plist.setPlayerScore(player_index, dest);
        }
    }

    cout << "Hello Player " << plist.getHighestRatedPlayerIndex() + 1 << ", Congratulations !!!! You have won." << endl;

}