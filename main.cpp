#include <iostream>
#include <random>
#include <chrono>
#include <map>
#include <array>

#ifdef _WIN32
#include <conio.h>
#endif


uint32_t random_seedseq()
{
    uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq seeder{uint32_t(seed),uint32_t(seed >> 32)};
    ++seed;
    int out;
    seeder.generate(&out,&out+1);
    return out;
}

std::vector<int> rollDice(int numberOfDice)
{
    std::vector<int> result {};
    auto seed{ random_seedseq() };

    std::default_random_engine re(seed);
    std::uniform_int_distribution<int> distribution(1,6);

    for(int i = 0; i<numberOfDice; i++)
    {
        result.push_back(distribution(re));
    }

    return result;
}

std::string displayRollingDiceResult(std::vector<int> result)
{
    std::string sentence { "RESULT: {" };
    for(auto it = result.begin(); it != result.end(); it++)
    {
        sentence += std::to_string(*it);
        if(it != result.end())
            sentence += ";";
    }
    sentence += "}";

    return sentence;
}

int numberDiceFromResults(std::map<int,bool> &results)
{
    int numberOfDice {0};

    for(const auto elt : results)
    {
        if(elt.second == false)
            numberOfDice++;
    }

    return numberOfDice;
}
int main()
{
    bool playing = true;
    while(playing)
    {
        const int NUMBER_OF_TRY {3};
        std::map<int,bool> checkingDice;
        checkingDice[4] = false;
        checkingDice[2] = false;
        checkingDice[1] = false;

        for(int i=0;i<NUMBER_OF_TRY;i++)
        {
            int numberOfDice { numberDiceFromResults(checkingDice) };

            std::cout << " --------- " << std::endl << "| Essai " << i+1  << " |" << std::endl << " --------- " << std::endl;
            std::vector<int> dice = rollDice(numberOfDice);
            std::cout << displayRollingDiceResult(dice) << std::endl;

            for(auto it = dice.begin(); it!= dice.end(); it++)
            {
                switch(*it)
                {
                    case 4:
                        checkingDice[4] = true;
                        break;
                    case 2:
                        checkingDice[2] = true;
                        break;
                    case 1:
                        checkingDice[1] = true;
                        break;
                    default:
                        break;
                }
            }
        }

        if(checkingDice[1] == true && checkingDice[2] == true && checkingDice[4] == true)
            std::cout << "GAGNE" << std::endl;
        else
            std::cout << "PERDU" << std::endl;

        char replay{0};
        std::cout << "Rejouer ? (o/n) ";
        std::cin >> replay;

        switch(replay)
        {
        case 'o':
            playing = true;
            break;
        case 'n':
            playing = false;
            break;
        }
    }

    #ifdef _WIN32
    std::cout << "Appuyez sur une touche pour fermer le programme";
    getch();
    #endif

    return 0;
}
