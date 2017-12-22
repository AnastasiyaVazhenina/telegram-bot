#pragma once

#include <functional>
#include <map>
#include <string>
#include <tgbot/tgbot.h>


std::string readToken(const std::string& filename);

void initBot(TgBot::Bot& bot);

std::map<std::string, std::function<void(TgBot::Bot&, TgBot::CallbackQuery::Ptr)>> getAllCallbacks();

std::map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr)>> getAllCommands();

void onAnyMessage(TgBot::Bot& bot, TgBot::Message::Ptr message);

struct Question
{
    std::string Text;
    std::string Photo;
    std::map<std::string, std::string> Answers;
};

void sendQuestion(TgBot::Bot& bot, TgBot::Message::Ptr message, const Question& q);

void sendText(TgBot::Bot& bot, TgBot::Message::Ptr message, const Question& q);

void sendPhoto(TgBot::Bot& bot, TgBot::Message::Ptr message, const Question& q);

void sendKeyboard(TgBot::Bot& bot, TgBot::Message::Ptr message, const Question& q);

void sendMessage1(TgBot::Bot& bot, TgBot::Message::Ptr message);

void sendEnd(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onClick(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query);

void onCommandStart(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onCommandBegin(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onCommandEnd(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onCommandNo(TgBot::Bot& bot, TgBot::Message::Ptr message);
