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
