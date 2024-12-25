#include <iostream>
#include <Windows.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

#pragma execution_character_set("utf-8")

using namespace std;

class Publisher;
class Stock;

class Book {
public:
	string title = "";
	Wt::Dbo::ptr<Publisher>publisher;
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>>stocks;
	
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, publisher, "publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToMany, "book");
	}

};
class Publisher {
public:
	string name = "";
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>>books;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
	}

};
class Stock;
class Shop
{
public:
	string name = "";
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>>stocks;

	template<class Action>
	
		void persist(Action& a)
		{
			Wt::Dbo::field(a, name, "name");
			Wt::Dbo::hasMany(a, stocks,Wt::Dbo::ManyToMany,"stock");
	}
};
class Sale;
class Stock
{
public:
	int count=0;
	Wt::Dbo::ptr<Book>book;
	Wt::Dbo::ptr<Shop>shop;
	Wt::Dbo::collection<Wt::Dbo::ptr<Sale>>sales;

	template<class Action>

	void persist(Action& a)
	{
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, book, "book");
		Wt::Dbo::belongsTo(a, shop, "shop");
		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "sale");
	}
};

class Sale
{
public:
	double price= 0.0;
	string date_sale = "";
	int count = 0;
	Wt::Dbo::ptr<Stock>stock;

	template<class Action>

	void persist(Action& a)
	{
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date_sale, "date_sale");
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, stock,"stock");
	}
};


int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	cout << "Hello" << endl;
	try {
		std::string connectionString =
			"host=localhost "
			"port=5432 "
			"dbname=music "
			"user=postgres "
			"password=Firsova2010";
		cout << "Connect OK" << endl;

		unique_ptr<Wt::Dbo::backend::Postgres>conn 
			= make_unique<Wt::Dbo::backend::Postgres>(connectionString);
		
		Wt::Dbo::Session s;
		s.setConnection(move(conn));

		s.mapClass<Book>("book");
		s.mapClass<Publisher>("publisher");
		s.mapClass<Shop>("shop");
		s.mapClass<Stock>("stock");
		s.mapClass<Sale>("sale");

		s.dropTables();
		s.createTables();
		

		/*Wt::Dbo::Transaction t{s};

		auto b1 = unique_ptr<Book>(move(unique_ptr<Book>{new Book{"Game of trone"}}));
		auto b2 = unique_ptr<Book>(move(unique_ptr<Book>{new Book{"Black White"}}));
		auto b3 = unique_ptr<Book>(move(unique_ptr<Book>{new Book{"War and peace"}}));

		auto p1 = unique_ptr<Publisher>(move(unique_ptr<Publisher>{new Publisher{"Mir" }}));
		auto p2 = unique_ptr<Publisher>(move(unique_ptr<Publisher>{new Publisher{"Trud" }}));
		auto p3 = unique_ptr<Publisher>(move(unique_ptr<Publisher>{new Publisher{"May" }}));

		auto s1 = unique_ptr<Shop>(move(unique_ptr<Shop>{new Shop{ "House of book in Arbat" }}));
		auto s2 = unique_ptr<Shop>(move(unique_ptr<Shop>{new Shop{ "House of book in Polyanka" }}));
		auto s3 = unique_ptr<Shop>(move(unique_ptr<Shop>{new Shop{ "Romaskka" }}));

		auto st1 = unique_ptr<Stock>(move(unique_ptr<Stock>{new Stock{ 3 }}));
		auto st2 = unique_ptr<Stock>(move(unique_ptr<Stock>{new Stock{ 2 }}));
		auto st3 = unique_ptr<Stock>(move(unique_ptr<Stock>{new Stock{ 10 }}));

		auto sa1 = unique_ptr<Sale>(move(unique_ptr<Sale>{new Sale{ 326.1,"2020-10-12", 6 }}));
		auto sa2 = unique_ptr<Sale>(move(unique_ptr<Sale>{new Sale{ 555.6,"2021-03-28", 4 }}));
		auto sa3 = unique_ptr<Sale>(move(unique_ptr<Sale>{new Sale{ 222.5, "2022-05-29", 5 }}));

		//найти по введеным данным
		string p;
		cout << "Add publisher" << endl;
		cin >> p;

		/*Wt::Dbo::collection < Wt::Dbo::ptr<Publisher> publisher
			= s.find<Publisher>().where("name = ?").bind(p);
			
		Wt::Dbo::ptr<Publisher> findPublisher = s.find<Publisher>().where("name = ?").bind(p);
		Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books = s.find<Book>().where("publisher_id = ?").bind(findPublisher);
		std::vector<Wt::Dbo::collection<Wt::Dbo::ptr<Stock>>> stocks;
		for (const auto& id : books) {
			stocks.push_back(s.find<Stock>().where("book_id = ?").bind(id.id()));
		}
		vector<Wt::Dbo::collection<Wt::Dbo::ptr<Shop>>> shops;
		for (const auto& col : stocks) {
			for (const auto& id : col) {
				shops.push_back(s.find<Shop>().where("id = ?").bind(id->shops));
			}
		}
		cout << "Shops with books of " << p << ": \n";
		set<std::string> names;
		for (const auto& col : shops) {
			for (const auto& id : col) {
				names.insert(id->name);
			}
		}
		for (const auto& name : names) {
			cout << name << endl;
		}
		*/
		//t.commit();


		
	}
	catch(const exception& e)
	{
		cout << e.what() << endl;
	}
}