#include "api.hpp"
#include <iostream>
#include "keyboard.hpp"
#include "utils.hpp"

using namespace std;
using namespace TgBot;
using namespace Utils;

void sendText(Bot& bot, Message::Ptr message, const Question& q)
{
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale(q.Text));
}

void sendPhoto(Bot& bot, Message::Ptr message, const Question& q)
{
    bot.getApi().sendPhoto(message->chat->id, InputFile::fromFile(q.Photo, "image/jpeg"));
}

void sendKeyboard(Bot& bot, Message::Ptr message, const Question& q)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    for (const auto& s : q.Answers)
    {
        vector<InlineKeyboardButton::Ptr> row0;
        InlineKeyboardButton::Ptr button(new InlineKeyboardButton);
        button->callbackData = fromLocale(s.first);
        button->text = fromLocale(s.second);
        row0.push_back(button);
        keyboard->inlineKeyboard.push_back(row0);
    }
    bot.getApi().sendMessage(message->chat->id, fromLocale("Варианты ответа:"), false, 0, keyboard, "Markdown");
}

void sendQuestion(Bot& bot, Message::Ptr message, const Question& q)
{
    sendText(bot, message, q);
    sendPhoto(bot, message, q);
    sendKeyboard(bot, message, q);
}

std::map<std::string, std::function<void(Bot&, CallbackQuery::Ptr)>> getAllCallbacks()
{
    std::map<std::string, std::function<void(Bot&, CallbackQuery::Ptr)>> callbacks =
            {
                    {"", onClick}
            };
    return callbacks;
}

std::map<std::string, std::string> question1 =
        {
                {"Отлично", "Италия"},
                {"Не верно", "Германия"},
                {"Нет,это не верно", "Испания"},
                {"Подумай", "Франция"},
        };
std::map<std::string, std::string> question2 =
        {
                {"Не верно!!", "Эйфелева башня"},
                {"Замечательно", "Пизанская башня"},
                {"Нет...", "Это вообще не башня"},
                {"Не то", "Останкинская башня"},
        };
std::map<std::string, std::string> question3 =
        {
                {"Верно", "Сидней"},
                {"Не верно!", "Нью-Йорк"},
                {"Нет, надо собраться!", "Париж"},
                {"Эх... Это не верно", "Сеул"},
        };
std::map<std::string, std::string> question4 =
        {
                {"Верно!", "Родина-Мать"},
                {"Не верно", "Статуя Свободы"},
                {"Нет", "Во имя победы"},
                {"Ну почти", "Родина"},
        };
std::map<std::string, std::string> question5 =
        {
                {"Не верно", "Останкинская башня"},
                {"Отлично!", "Эйфелева башня"},
                {"Не то", "Пизанская башня"},
                {"Нет!", "Это не башня,а маяк"},
        };
std::map<std::string, std::string> question6 =
        {
                {"Не верно", "Москва"},
                {"Верно", "Лондон"},
                {"Очень жаль, но нет", "Рим"},
                {"Не совсем то", "Вашингтон"},
        };
std::map<std::string, std::string> question7 =
        {
                {"Не верно", "Голубая мечеть"},
                {"Верно!", "Тадж-Махал"},
                {"Это не то название", "Казанский собор"},
                {"Со страной ты угадал", "Мандир"},
        };
std::map<std::string, std::string> question8 =
        {
                {"Ты молодец!", "Милан"},
                {"Не верно!", "Париж"},
                {"Не совсем то", "Барселона"},
                {"Неа", "Берлин"},
        };
std::map<std::string, std::string> question9 =
        {
                {"Не верно", "Москва"},
                {"Верно", "Санкт-Петербург"},
                {"Нет", "Казань"},
                {"Не то", "Тула"},
        };
std::map<std::string, std::string> question10 =
        {
                {"Не верно", "США"},
                {"Превoсходно!", "Бразилия"},
                {"Не угадал", "Аргентина"},
                {"Не совсем", "Венесуэлла"},
        };
std::vector<Question> Questions =
        {
                {
                        "Где находится Колизей?",
                        "q1.jpg",
                        question1
                },
                {
                        "Что изображено на фото?",
                        "q2.jpg",
                        question2
                },
                {
                        "В каком городе находится это здание?",
                        "q3.jpg",
                        question3
                },
                {
                        "Какое название у этого памятника?",
                        "q4.jpg",
                        question4
                },
                {
                        "Что изображено на фото?",
                        "q5.jpg",
                        question5
                },
                {
                        "Где находится Биг-Бен?",
                        "q6.jpg",
                        question6
                },
                {
                        "Как называется этот знаменитый храм?",
                        "q7.jpg",
                        question7
                },
                {
                        "Где находится Кафедральный собор?",
                        "q8.jpg",
                        question8
                },
                {
                        "В каком городе находится Спас на крови?",
                        "q9.jpg",
                        question9
                },
                {
                        "В какой стране находится статуя Христа?",
                        "q10.jpg",
                        question10
                }
        };

void sendMessage1(Bot& bot, Message::Ptr message)
{
    sendQuestion(bot, message, Questions[0]);
}

void sendEnd(Bot& bot, Message::Ptr message)
{
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Прекрасная игра, но мои вопросы закончились. "
                                                                                 "Напиши /end, чтобы завершить."));
}

void onClick(Bot& bot, CallbackQuery::Ptr query)
{
    static int i = 1;
    if (i <= 9)
    {
        bot.getApi().sendMessage(query->message->chat->id, query->data);
        sendQuestion(bot, query->message, Questions[i]);
    }
    if (i == 10)
    {
        bot.getApi().sendMessage(query->message->chat->id, query->data);
        sendEnd(bot, query->message);
    }
    ++i;
}

void onCommandStart(Bot& bot, Message::Ptr message)
{
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Хочешь начать игру?"));
}

void onCommandBegin(Bot& bot, Message::Ptr message)
{
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Отлично!!! Тогда начнем!"));
    sendMessage1(bot, message);
}

void onCommandEnd(Bot& bot, Message::Ptr message)
{
    bot.getApi().sendMessage(message->chat->id, "До встречи! Было приятно с тобой поиграть!!!");
}

void onCommandNo(Bot& bot, Message::Ptr message)
{
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Очень жаль. Пиши, если захочешь поиграть."));
}

std::map<std::string, std::function<void(Bot&, Message::Ptr)>> getAllCommands()
{
    std::map<std::string, std::function<void(Bot&, Message::Ptr)>> commands =
    {
        {"start", onCommandStart},
        {"end", onCommandEnd}
    };

    return commands;
}


void onAnyMessage(Bot& bot, Message::Ptr message)
{
    printf("User wrote %s\n", message->text.c_str());
    if (StringTools::startsWith(message->text, "/start"))
    {
        return;
    }
    if (StringTools::startsWith(message->text, "/end"))
    {
        return;
    }
    std::string hello = Utils::fromLocale("Привет");
    if (message->text.find(hello) != std::string::npos)
    {
        bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Привет, ") + message->from->firstName +
                                                    Utils::fromLocale(
                                                            ".\n Мои команды: /start - чтобы запустить викторину; "
                                                                    "\n/end - чтобы закончить"));
        return;
    }
    std::string yes = Utils::fromLocale("Да");
    if (message->text.find(yes) != std::string::npos)
    {
        onCommandBegin(bot, message);
        return;
    }
    std::string no = Utils::fromLocale("Нет");
    if (message->text.find(yes) != std::string::npos)
    {
        onCommandNo(bot, message);
        return;
    }
    bot.getApi().sendMessage(message->chat->id, Utils::fromLocale("Привет, ") + message->from->firstName +
                                                Utils::fromLocale(
                                                        ".\n Мои команды:"
                                                                "\n/start - чтобы запустить викторину; "
                                                                "\n/end - чтобы закончить"));
}
