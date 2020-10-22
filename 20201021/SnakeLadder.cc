#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Player{
public:
    Player(string name) : score_(0), name_(name) {
    }

    int getScore() {
        return score_;
    }

    string getName() {
        return name_;
    }

    void setScore(int score) {
        score_ = score;
    }

    bool operator < (const Player& p1) const
    {
        return (score_ < p1.score_);
    }

private:
    int score_;
    string name_;
};


class PlayerList {
public:
    PlayerList(std::vector<Player>& players) : players_(players) {
    }

    int getPlayerScore(int index) {
        return players_[index].getScore();
    }

    void setPlayerScore(int index, int score) {
        players_[index].setScore(score);
    }

    string getHighestRatedPlayer() {
        Player p = *max_element(players_.begin(), players_.end());
        return p.getName();
    }

    string getPlayerName(int index) {
        return players_[index].getName();
    }

    int playerCount() {
        return players_.size();
    }

private:
    std::vector<Player>& players_;
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

    //Lets do some unit testing for the board
    assert(board.getDestNumber(7,3) == 5);
    assert(board.getDestNumber(7,4) == 15);
    assert(board.getDestNumber(7,5) == 12);
    assert(board.getDestNumber(17,5) == 17);
    assert(board.getDestNumber(17,3) == 20);

    int playerCount;
    cout << "Enter number of players: " ;
    cin >> playerCount;

    std::vector<Player> players;
    for(int pi = 0; pi < playerCount; pi++) {
        string playerName;
        cout << "Enter Player name: ";
        cin >> playerName;
        players.push_back(Player(playerName));
    }
    PlayerList plist(players);

    //Some more unit testing, this time for the Player Manager
    std::vector<Player> pTest({Player("P1"), Player("P2"), Player("P3")});
    PlayerList plisttest(pTest);
    assert(plisttest.getPlayerScore(0) == 0);
    plisttest.setPlayerScore(1, 20);
    assert(plisttest.getPlayerScore(1) == 20);
    assert(plisttest.getPlayerScore(2) == 0);

    Dice dice(1, 6);

    //Just checking randomness of the dice
    for(int i = 0; i < 100; i++) {
        int r = dice.getNextRoll();
        assert(r >= 1 && r <= 6);
    }

    //Here goes the actual code
    for(int i = 0; i < 20; i++) {
        int player_index = i % plist.playerCount();

        int roll = dice.getNextRoll();/*What is the next number*/
        int start_pos = plist.getPlayerScore(player_index);
        int dest = board.getDestNumber(start_pos, roll);

        if(dest == board.getEndpoint()) {
            cout << "Hello Player " << plist.getPlayerName(player_index) << ", Congratulations !!!! You have won with the new roll " << roll << endl;
            return EXIT_SUCCESS;
        }
        else {
            cout << "Hello Player " << plist.getPlayerName(player_index) << ", your roll is " << roll << " and new score is " << dest << endl;
            plist.setPlayerScore(player_index, dest);
        }
    }

    cout << "Hello Player " << plist.getHighestRatedPlayer() << ", Congratulations !!!! You have won by being at the highest position." << endl;
}
