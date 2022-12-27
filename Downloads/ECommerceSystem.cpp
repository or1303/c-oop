#include "ECommerceSystem.h"

ECommerceSystem::ECommerceSystem(const char* name,
	int costumersSize,
	int retailersSize,
	int	ordersSize)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->costumers = new Costumer* [costumersSize];
	this->costumersAmount = 0;
	this->costumersSize = costumersSize;
	this->retailers = new Retailer* [retailersSize];
	this->retailersAmount = 0;
	this->retailersSize = retailersSize;
	this->orders = new Order* [ordersSize];
	this->ordersAmount = 0;
	this->ordersSize = ordersSize;
}

ECommerceSystem::~ECommerceSystem()
{
	delete[] name;
	for (int i = 0; i < costumersAmount; i++)
		delete costumers[i];
	delete[] costumers;

	for (int i = 0; i < retailersAmount; i++)
		delete retailers[i];
	delete[] retailers;
	
	for (int i = 0; i < ordersAmount; i++)
		delete orders[i];
	delete[] orders;
}

bool ECommerceSystem::addCostumer(Costumer* costumer)
{
	if (costumer == nullptr)
	{
		std::cout << "adding costumer failed: costumer is null" << std::endl;
		return false;
	}
	if (costumersAmount + 1 == costumersSize)
		if (resizeCostumers() == false)
			return false;
	costumers[costumersAmount] = costumer;
	costumersAmount++;
	std::cout << "adding costumer succeded:" << std::endl;
	costumer->print();
	return true;
}

bool ECommerceSystem::addRetailer(Retailer* retailer)
{
	if (retailer == nullptr)
		return false;
	if (retailersAmount + 1 == retailersSize)
		if (resizeRetailers() == false)
			return false;
	retailers[retailersAmount] = retailer;
	retailersAmount++;
	retailer->print();
	return true;
}

bool ECommerceSystem::addProductToRetailer(int retailerIndex, Product* product)
{
	if (product == nullptr)
		return false;
	if (retailers == nullptr)
		return false;
	if (retailerIndex >= retailersAmount)
		return false;
	if (retailers[retailerIndex] == nullptr)
		return false;
	return retailers[retailerIndex]->addProduct(product);
}

bool ECommerceSystem::addProductToCostumer(int costumerIndex, int retailerIndex, int productIndex)
{
	if (costumers == nullptr)
		return false;
	if (costumerIndex >= costumersAmount)
		return false;
	if (costumers[costumerIndex] == nullptr)
		return false;
	if (retailers == nullptr)
		return false;
	if (retailerIndex >= retailersAmount)
		return false;
	if (retailers[retailerIndex] == nullptr)
		return false;
	Product* product = retailers[retailerIndex]->getProduct(productIndex);
	if (product == nullptr)
		return false;
	return costumers[costumerIndex]->addProduct(product);
}

bool ECommerceSystem::payment(int costumerIndex)
{
	if (costumers == nullptr)
		return false;
	if (costumerIndex >= costumersAmount)
		return false;
	if (costumers[costumerIndex] == nullptr)
		return false;
	Order* order = costumers[costumerIndex]->payment();
	if (order == nullptr)
		return false;
	order->print();
	return addOrder(order);
}

void ECommerceSystem::printRetailers() const
{
	std::cout << name << " ECommerce System." << std::endl;
	std::cout << "Retailers: " << std::endl;
	for (int i = 0; i < retailersAmount; i++)
	{
		std::cout << i << ": ";
		retailers[i]->print();
	}
}

void ECommerceSystem::printCostumers() const
{
	std::cout << name << " ECommerce System." << std::endl;
	std::cout << "Costumers: " << std::endl;
	for (int i = 0; i < costumersAmount; i++)
	{
		std::cout << i << ": ";
		costumers[i]->print();
	}
}

bool ECommerceSystem::resizeCostumers()
{
	Costumer** biggerCostumers = new Costumer * [2 * costumersSize];
	for (int i = 0; i < costumersAmount; i++)
		biggerCostumers[i] = costumers[i];
	costumersSize *= 2;
	delete[] costumers;
	costumers = biggerCostumers;
	return true;
}

bool ECommerceSystem::resizeRetailers()
{
	Retailer** biggerRetailers = new Retailer * [2 * retailersSize];
	for (int i = 0; i < retailersAmount; i++)
		biggerRetailers[i] = retailers[i];
	retailersSize *= 2;
	delete[] retailers;
	retailers = biggerRetailers;
	return true;
}

bool ECommerceSystem::resizeOrders()
{
	Order** biggerOrders = new Order * [2 * ordersSize];
	for (int i = 0; i < ordersAmount; i++)
		biggerOrders[i] = orders[i];
	ordersSize *= 2;
	delete[] orders;
	orders = biggerOrders;
	return true;
}

bool ECommerceSystem::addOrder(Order* order)
{
	if (orders == nullptr)
		return false;
	if (ordersAmount + 1 == ordersSize)
		if (resizeOrders() == false)
			return false;
	orders[ordersAmount] = order;
	ordersAmount++;
	return true;
}
