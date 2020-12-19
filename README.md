# SHBSRBD - Time Functions

This library is written to be used in microcontrollers (like [Arduino]()) but it is not limited to since it is platform agnostic. As the name suggest, this library provides and object with which functions will be registered and they will run at a specified interval. Have in mind the this library does not guaranty that function will be executed in specified interval since it is using only 1 thread to achieve its functionality. With this in mind, make sure to handle blocking code properly.

## Example

Program should execute 2 functions, 1 every second and other every 3 seconds.

```cpp
#include "TF/TF.h"
#include "chrono"
#include "ctime"
#include "iostream"
#include "sys/time.h"

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

unsigned long timeOffset =
    duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
unsigned long millis()
{
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
             .count() -
         timeOffset;
}

void handler1(unsigned long t) { cout << t << " -> Handler 1" << endl; }
void handler2(unsigned long t) { cout << t << " -> Handler 2" << endl; }

int main()
{
  TF tf = TF(2, &millis);
  tf.reg(1000, &handler1);
  tf.reg(3000, &handler2);
  while (1) {
    tf.run();
  }
}
```

## Limitations

As mentioned at the beginning, blocking code can have negative effect on timing of registered function. Using example above, if something like this happen:

```cpp
void handler1(unsigned long t) {
  cout << t << " -> Handler 1" << endl;
  while(1);
}
```

`handler2` will never be executed since `handler1` is in an infinite loop, meaning that program will never reach place where `handler2` is called. This is extreme case, but similar thing will happen if any handler is taking to long to execute.