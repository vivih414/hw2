#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <fstream>

MyDataStore::MyDataStore()
{

}
MyDataStore::~MyDataStore()
{
  for(size_t i = 0; i < products_.size(); i++)
  {
    delete products_[i];
  }
  
  std::map<std::string, User*>::iterator it = users_.begin();
  while(it != users_.end())
  {
    delete it->second;
    it++;
  }
}
void MyDataStore::addProduct(Product* p)
{
  products_.push_back(p);
}
void MyDataStore::addUser(User* u)
{
  users_[u->getName()] = u;
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> result;

  if(terms.empty())
  {
    return std::vector<Product*>();
  }
  for(size_t i = 0; i < terms.size(); i++)
  {
    std::set<Product*> temp;
    for(size_t j = 0; j < products_.size(); j++)
    {
      Product* p = products_[j];
      std::set<std::string> keywords = p->keywords();
      if(keywords.find(terms[i]) != keywords.end())
      {
        temp.insert(p);
      }
    }
    if(i == 0)
    {
      result = temp;
    }
    else
    {
      if(type == 0)
      {
        result = setIntersection(result, temp);
      }
      else
      {
        result = setUnion(result, temp);
      }
    }
  }
  return std::vector<Product*>(result.begin(), result.end());
}
void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << std::endl;
  for(unsigned int i = 0; i < products_.size(); i++)
  {
    Product* p = products_[i];
		
		if(p != nullptr)
		{
			p->dump(ofile);
		}
  }
  
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  
  std::map<std::string, User*>::iterator it;
  for(it = users_.begin(); it != users_.end(); it++)
  {
    User* u = it->second;

		if(u != nullptr)
		{
			u->dump(ofile);
		}
  }

  ofile << "</users>" << std::endl;
}
void MyDataStore::addToCart(const std::string& username, Product* p)
{
	if(users_.find(username) == users_.end())
  {
		std::cout << "Invalid request" << std::endl;
    return;
  }

	if(p == nullptr || p->getName().empty())
	{
		std::cout << "Invalid request" << std::endl;
		return;	
	}

	if(carts_.find(username) == carts_.end())
	{
		carts_[username] = std::vector<Product*>();
	}
	carts_[username].push_back(p);
}
void MyDataStore::viewCart(const std::string& username)
{
  if(carts_.find(username) == carts_.end())
  {
		std::cout << "Invalid username" << std::endl;
		return;
  }

	if(carts_[username].empty())
	{
		return;
	}

	std::vector<Product*> cartUsers = carts_[username];
	for(size_t i = 0; i < cartUsers.size(); i++)
	{
    std::cout << "Item " << (i+1) << ":\n" << cartUsers[i]->displayString() << std::endl;
  }
}
void MyDataStore::buyCart(const std::string& username)
{
	User* user = users_[username];

  if(!user)
  {
		std::cout << "Invalid username" << std::endl;
    return;
  }

	if(carts_[username].empty())
  {
    return;
  }

  std::vector<Product*> finalCart;
  for(Product* p : carts_[username])
  {
    if(p->getQty() > 0 && user->getBalance() >= p->getPrice())
    {
      user->deductAmount(p->getPrice());
      p->subtractQty(1);
    }
    else
    {
      finalCart.push_back(p);
    }
  }
  carts_[username] = finalCart;
}