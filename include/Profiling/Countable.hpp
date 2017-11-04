/*
 * File Name: Countable.h
 * Author(s): Pelanyo Kamara
 *
 * Super class which allows for fast counting of certain class and how many
 * exist in the global scope of the project 
 *
 * Copyright (c) 2017 Pelanyo Kamara
 * https://pkamara.me/QuasiLib
 * https://github.com/MathematicalDessert/QuasiLib
 */

#include <unordered_map>

namespace Quasi
{

    /*
     * Countable class, when a class inherits off Countable
     * it can then increment and decrement it's given counter.
     * 
     * Usage:
     *  
     * class MyClass
     *      : public Quasi::Countable<MyClass>
     * {
     *      // misc
     * }
     */
    template<typename T>
    class Countable
    {
        public:
            /*
             * Constructor automatically increments the counter
             */
            Countable()
            {
				if (objects->find(typeid(T).hash_code()) != objects->end())
					objects->find(typeid(T).hash_code())->second++;
				else
					objects->insert(std::make_pair(typeid(T).hash_code(), 1));
            }

            /*
             * Destructor automatically decrements the counter
             */
            ~Countable()
            {
				if (objects->find(typeid(T).hash_code()) != objects->end()) // let's just check it exists anyway
					objects->find(typeid(T).hash_code())->second--;
            }

            /*
             * int Countable::GetCount(void)
             * 
             * Returns the global number of the instance in the current program.
             * 
             * Usage:
             * 
             * MyClass::GetCount();
             * 
             */
            static int GetCount()
            {
				if (objects->find(typeid(T).hash_code()) != objects->end())
					return objects->find(typeid(T).hash_code())->second;
				return 0;
            }
        private:
            /*
             * No point creating multiple storage units for
             * each given class, just use one unordered map.
             */
            static std::unordered_map<size_t, int> *objects;
    };
}