#include <signal.h>
#include <iostream>
#include <exception>

#include <tgbot/tgbot.h>

#include "api.hpp"
#include "utils.hpp"


using namespace std;
using namespace TgBot;
using namespace Utils;

bool sigintGot = false;


int main()
{
    Bot bot(readToken("token.cfg"));
    initBot(bot);

	signal(SIGINT, [](int s) {
		printf("SIGINT got");
		sigintGot = true;
	});

	try
    {
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

		TgLongPoll longPoll(bot);
		while (!sigintGot) 
        {
			printf("Long poll started\n");
			longPoll.start();
		}
	}
    catch (exception& e) 
    {
		printf("error: %s\n", e.what());
	}

	return 0;
}
