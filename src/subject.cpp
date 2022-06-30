#include <subject.h>
#include <observer_iface.h>
#include <algorithm>

void Subject::addObserver(IObserver* observer)
{
     observers_.push_back( observer ); // добавляем наблюдателя в список
}

void Subject::removeObserver(IObserver* observer)
{
     // удаляем наблюдателя из списка
     observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
          [observer](IObserver* observer_)
          {
               if (observer != observer_)
               {
                    return false;
               }
               return true;
          }),
          observers_.end()
     );
}

void Subject::notify(const Subject& subject)
{
     // оповещаем всех наблюдателей
     for(auto& val : observers_)
     {
          val->onNotify(subject);
     }
}

