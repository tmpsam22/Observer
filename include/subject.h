/// subject.h представлен класс для обслуживания наблюдателей

#pragma once
#ifndef INCLUDE_SUBJECT_H
#define INLCUDE_SUBJECT_H

#include <list>

// интерфейс наблюдателя
class IObserver;

/// @brief класс для обслуживания наблюдателей
struct Subject
{

public:

     /// @brief добавить наблюдателя в список
     /// @param IObserver интерфейс наблюдателя
     void addObserver(IObserver* observer);

     /// @brief удалить из списка наблюдателя
     /// @param IObserver интерфейс наблюдателя
     void removeObserver(IObserver* observer);

protected:

     /// @brief оповещение наблюдателей
     /// @param subject класс обслуживания
     void notify(const Subject& subject);

     /// @brief деструктор
     virtual ~Subject();

private:

     /// список наблюдателей
     std::list<IObserver*> observers_;

};

#endif