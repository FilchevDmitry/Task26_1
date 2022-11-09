#include <iostream>
#include <string>
#include<ctime>
#include<iomanip>
#include<map>
#pragma warning(disable : 4996)
class Track 
{  
private:
    std::string nameTtack;
    std::time_t dataTrack;
    std::time_t timerTrack;
public:
    void setName(std::string name)
    {
        std::srand(time(nullptr));
        nameTtack = name;
        dataTrack = time(nullptr);
        timerTrack = rand() % 300;
    }
    std::string getName()
    {
        return nameTtack;
    }
    std::string getDataTrack()
    {
        std::tm tempData = *std::localtime(&dataTrack);
        std::string data = std::asctime(&tempData);
        return data;
    }
    std::string getTimerTrack()
    {
        char time[100];
        std::tm tempTrack = *std::localtime(&timerTrack);
        std::strftime(time,sizeof(time),"%M:%S",&tempTrack);
        return time;
    }
};
class Player
{
private:
    std::map<std::string, std::string> playList;
    Track track;
    std::map<std::string, std::string>::iterator playNow;
    bool play = false;
    bool pause = false;
public:
    void setTrack(std::string name)
    {
         track.setName(name);
         playList[name] = "time track-"+track.getTimerTrack()+" data :"+track.getDataTrack();
    } 
    void getPlay()
    {
        if(playList.size()!=0)
        {
            std::string trackName;
            if (!play)
            {
                std::cout << "Input name track for play : ";
                std::cin >> trackName;
                std::map<std::string, std::string>::iterator id = playList.find(trackName);
                if (playList.find(trackName) == playList.end())
                {
                    std::cout << "The track with this name is not in the list" << std::endl;
                }
                else
                {
                    std::cout << "NOW PLAY" << " " << id->first << " " << id->second << std::endl;
                    playNow = id;
                    play = true;
                }
            }
            
       }
        else
              {
                std::cout << "Play list empty!!!\n";
               }
    }
    void getPause()
    {
        if (play)
        {
            if (!pause) 
            {
                std::cout << "PAUSE" << " " << playNow->first << std::endl;
                pause = true;
            }
            else
            {
                std::cout << "PLAY" << " " << playNow->first << std::endl;
                pause = false;
            }
        }
    }
    void getNext()
    {
        if (play)
        {
            std::srand(time(nullptr));
            std::map<std::string, std::string>::iterator id = playList.begin();
            std::advance(id, rand() % (playList.size() + 1));
            std::cout << id->first << " " << id->second;
            playNow = id;
        }
    }
    void getStop()
    {
        if (play)
        {
            std::cout << "STOP" << std::endl;
            play = false;
        }
    }
};


int main()
{
    int num = 0;
    int command = 0;
    bool exit = true;
    std::string nameTrack;
    Player* player=new Player();
    std::cout << "Enter the number of tracks you want to record : ";
    std::cin >> num;
    for (int i=0; i < num; i++)
    {
        std::cout << "Input name track : ";
        std::cin >> nameTrack;
        player->setTrack(nameTrack);
    }
    while (exit)
    {
        std::cout << "Input command :\n1-play\n2-pause\n3-next\n4-stop\n5-exit" << std::endl;
        std::cin >> command;
        switch (command)
        {
        case 1:
        {
            player->getPlay();
            break;
        }
        case 2:
        {
            player->getPause();
            break;
        }
        case 3:
        {
            player->getNext();
            break;
        }
        case 4:
        {
            player->getStop();
            break;
        }
        case 5:
        {
            exit = false;
            break;
        }
        default:
        {
            std::cout << "Incorect command\n";
            break; 
        }
        }
    }
    delete player;
}
