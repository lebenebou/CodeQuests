
#include <iostream>
#include <algorithm>
#include <random>
#include <queue>
#include <vector>

std::queue<int> getShuffledDeck(std::vector<int>& cards)
{
    std::random_shuffle(cards.begin(), cards.end());

    std::queue<int> deck;
    std::for_each(cards.begin(), cards.end(), [&deck](int card) { deck.push(card); });
    return deck;
}

std::pair<int, int> getValidPair(const std::vector<int>& board)
{
    for (int i = 0; i < board.size() - 1; ++i)
    {
        if (board[i] == 10)
            return std::make_pair(i, -1);

        if (board[i] > 10)
            continue;

        for (int j = i + 1; j < board.size(); ++j)
        {
            if (board[j] == 10)
                return std::make_pair(-1, j);

            if (board[j] > 10)
                continue;

            if (board[i] + board[j] == 10)
                return std::make_pair(i, j);
        }
    }

    return std::make_pair(-1, -1);
}

bool playRound(std::queue<int>& deck)
{
    std::vector<int> board;
    board.reserve(12);

    while (board.size() < 12)
    {
        int card = deck.front();
        deck.pop();

        if (card < 10)
        {
            board.push_back(card);
        }
        else
            deck.push(card);
    }

    while (deck.size())
    {
        auto pair = getValidPair(board);

        if (pair.first == -1 && pair.second == -1)
        {
            return false;
        }

        int card = deck.front();
        deck.pop();

        if (pair.first != -1 && pair.second != -1)
        {   
            board[pair.first] = card;
            board[pair.second] = deck.front();
            deck.pop();
        }
        else if (pair.first != -1)
        {
            board[pair.first] = card;
        }
        else
        {
            board[pair.second] = card;
        }
    }

    return true;
}

int main(int argc, char const* argv[])
{
    std::vector<int> cards;
    for (int i = 0; i < 52; ++i) cards.push_back(i);
    std::transform(cards.begin(), cards.end(), cards.begin(), [](int card) { return (card % 13) + 1; });

    std::queue<int> deck = getShuffledDeck(cards);

    const int trials = 1000000;
    int wins = 0;
    for (int i = 0; i < trials; ++i)
    {
        wins += playRound(deck);
        deck = getShuffledDeck(cards);
    }

    double winPercentage = (double)wins / (double)trials * 100.0;

    std::cout << wins << " Wins out of " << trials << " games." << std::endl;
    std::cout << "Win percentage: " << winPercentage << "%" << std::endl;

    return 0;
}