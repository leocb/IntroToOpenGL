#ifndef BASECLASS_H
#define BASECLASS_H

class BaseClass
{
public:
  BaseClass();
  virtual ~BaseClass();

protected:
private:
  BaseClass(const BaseClass &other) {}
  void operator=(const BaseClass &other) {}
};

#endif // !BASECLASS_H