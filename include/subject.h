#pragma once

#ifndef INCLUDE_SUBJECT_H
#define INLCUDE_SUBJECT_H

#include <list>

class IObserver;

struct Subject
{

public:

     void addObserver(IObserver* observer);

     void removeObserver(IObserver* observer);

protected:

     void notify(const Subject& subject);

     virtual ~Subject();

private:

     std::list<IObserver*> observers_;
};

#endif