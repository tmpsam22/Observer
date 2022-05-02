#include <subject.h>
#include <observer_iface.h>

void Subject::addObserver(IObserver* observer)
{
     observers_.push_back ( observer );
}

void Subject::removeObserver(IObserver* observer)
{

}

void Subject::notify(const Subject& subject)
{
     for(auto& val : observers_)
     {
          val->onNotify(subject);
     }
}

Subject::~Subject()
{

}