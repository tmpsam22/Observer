#include <subject.h>
#include <observer_iface.h>
#include <algorithm>

void Subject::addObserver(IObserver* observer)
{
     observers_.push_back ( observer );
}

void Subject::removeObserver(IObserver* observer)
{
     observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
          [observer](IObserver* observer_)
          {
               if (observer != observer_)
               {
                    return false;
               }
               delete observer;
               return true;
          }),
          observers_.end()
     );
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
