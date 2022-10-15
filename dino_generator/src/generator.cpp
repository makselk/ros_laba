#include "generator.hpp"
#include <time.h>
#include <stdlib.h>
#include <algorithm>


/// @brief Используемая базы с постфиксами, семействами и периодами
const std::string POSTFIX[10] = {"saurus",
                                 "raptor",
                                 "pteryx",
                                 "stacator",
                                 "rex",
                                 "ceratops",
                                 "gnathus",
                                 "roides",
                                 "draco",
                                 "dromeus"};

const std::string FAMILY[20] = {"Abelisauridae",
                                "Noasauridae",
                                "Megalosauridae",
                                "Carcharodontosauridae",
                                "Tyrannosauridae",
                                "Plateosauridae",
                                "Brachiosauridae",
                                "Titanosauridae",
                                "Scelidosauridae",
                                "Ankylosauridae",
                                "Hadrosauridae",
                                "Protoceratopsidae",
                                "Alvarezsauridae",
                                "Cetiosauridae",
                                "Diplodocidae",
                                "Euhelopodidae",
                                "Nodosauridae",
                                "Ceratopsidae",
                                "Omeisauridae",
                                "Vulcanodontidae"};

const std::string PERIOD_OF_PERIOD[3] = {"Early",
                                         "Midddle",
                                         "Late"};

const std::string PERIOD[3] = {"Cretaceous",
                               "Jurassic",
                               "Tirassic"};

DinoGenerator::DinoGenerator() 
{
    /// Инициализация обработчика ноды, сервера сервиса, паблишера и подписчика топика
    nh_ = ros::NodeHandle("~");
    dino_server_ = nh_.advertiseService("dino_srv", &DinoGenerator::generateName, this);
    pub_ = nh_.advertise<std_msgs::String>("dino_topic", 2);
    sub_ = nh_.subscribe("dino_topic", 2, &DinoGenerator::generateFact, this);
}

bool DinoGenerator::generateName(dino_service::dino_service_file::Request &req,
                                 dino_service::dino_service_file::Response &res) 
{
    /// Обработка пустого запроса
    if(req.input.empty()) 
    {
        res.output = "Error"; // а надо ли?
        return false;
    }

    /// На всякий случай сначала переводим все в нижний регистр
    std::transform(req.input.begin(), req.input.end(), std::back_inserter(res.output), tolower);
    /// Первую букву в верхний регистр
    std::transform(res.output.begin(), res.output.begin() + 1, res.output.begin(), toupper);

    /// Рандомно выбираем постфикс
    srand(time(nullptr));
    res.output += POSTFIX[rand() % 10];

    /// Публикуем в топик
    std_msgs::String name;
    name.data = res.output.data();
    pub_.publish(name);

    // Выводим в коммандную сторку полученное имя
    ROS_INFO_STREAM(res.output.data());

    return true;
}

void DinoGenerator::generateFact(const std_msgs::String &src) 
{
    /// Заполняем строку рандомной информацией
    srand(time(nullptr));
    std::string fact = src.data;
    fact += " belonged to the ";
    fact += FAMILY[rand() % 20];
    fact += " family and lived in the ";
    fact += PERIOD_OF_PERIOD[rand() % 3];
    fact += " ";
    fact += PERIOD[rand() % 3];
    ROS_INFO_STREAM(fact.c_str());
}
