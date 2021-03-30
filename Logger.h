#ifndef __JLOGGER__
#define __JLOGGER__

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#define TRUE 1

using namespace std;

class Logger {
public:
   //------------------------------------------------------------
   Logger()
   : exit_(false)
   , messages_available_(false)
   , messages_()
   {}

   //------------------------------------------------------------
   ~Logger() {
      // Guard against it never being used or being stopped elsewhere

      exit_ = true;
   }

   //------------------------------------------------------------
   // provide option to manually block and let all logs flush on exit
   void stopLogger() {
      exit_ = true;
   }

   //------------------------------------------------------------
   void print(std::string msg) {
      messages_.push(msg);
      messages_available_ = true;

      cout<<msg<<endl;
   }

   //------------------------------------------------------------
   void runLogger() {
      while (TRUE) {
         if (messages_available_ == true) {
            copyMessages();
            printMessages();
         }
         if (exit_ == true) {
            copyMessages();
            printMessages();
            return;
         }
      }
   }

private:
   //------------------------------------------------------------
   void copyMessages() {
      // Just copy them all out.  Deal with strcpy costs here in bulk.
      // Could optimize later if it becomes a problem and blocks enqueue
      while (messages_.size() != 0) {
         messages_to_print_.push(messages_.front());
         messages_.pop();
      }
      messages_available_ = false;
   }
   //------------------------------------------------------------
   void init() {

   }

   //------------------------------------------------------------
   void printMessages() {
      while (messages_to_print_.size() != 0) {
         fprintf(stderr, "%s", messages_to_print_.front().c_str());
         messages_to_print_.pop();
      }
   }

   std::atomic<bool> exit_;
   std::atomic<bool> messages_available_;
   std::queue<std::string> messages_;
   std::queue<std::string> messages_to_print_;
};

#endif
