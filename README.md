#Динозаврогенератор

- Для запуска в репозитории dino_generator лежит файл launch.launch

В случае запуска через launch файл:
- rosservice call /dino_gen1/dino_srv "input: ''"
- rostopic echo /dino_gen1/dino_topicS