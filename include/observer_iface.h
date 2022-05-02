#pragma once

#ifndef INCLUDE_OBSERVER_IFACE_H
#define INCLUDE_OBSERVER_IFACE_H

class Subject;

struct IObserver
{
     virtual void onNotify(const Subject&) = 0;

     virtual ~IObserver() { }
};

#endif