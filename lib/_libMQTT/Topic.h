#ifndef TOPIC_H
#define TOPIC_H

#include <string>
#include <vector>

class Topic
{
public:
   Topic();
   Topic(const std::string& root);
   Topic(const Topic& other) = default;
   Topic& operator=(const Topic& other) = default;
   virtual ~Topic() = default;

   Topic& add(const std::string& item);
   Topic& add(const char* pItem);
   const char* c_str() const { return topic_.c_str(); }
   std::string operator[](const int nIndex) const;
private:
   std::string topic_;
   std::vector<std::string> cachedSplit_;
};

#endif // TOPIC_H
