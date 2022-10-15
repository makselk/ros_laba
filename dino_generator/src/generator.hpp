#include "ros/ros.h"
#include "std_msgs/String.h"
#include "dino_service/dino_service_file.h"


class DinoGenerator {
public:
    explicit DinoGenerator();
public:
    /// @brief Генерирует название динозавра
    /// @param req - запрос
    /// @param res - ответ
    /// @return true, если генерация прошла успешно
    ///         false, если получен пустой запрос
    bool generateName(dino_service::dino_service_file::Request &req,
                      dino_service::dino_service_file::Response &res);

    /// @brief Генерирует случайный факт для заданного динозавра
    /// @param src - Название динозавра
    void generateFact(const std_msgs::String &src);
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    ros::ServiceServer dino_server_;
};