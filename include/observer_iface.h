/// observer_iface.h представлен интерфейс наблюдателя

#pragma once
#ifndef INCLUDE_OBSERVER_IFACE_H
#define INCLUDE_OBSERVER_IFACE_H

// класс обслуживания наблюдателей
class Subject;

/// @brief интерфейс наблюдателя
struct IObserver
{
     /// @brief коллбек при получении оповещения
     /// со стороны наблюдаемых объектов
     virtual void onNotify(const Subject&) = 0;

     /// @brief деструктор
     virtual ~IObserver() { }
};

#endif