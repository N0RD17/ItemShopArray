#include <iostream>     // for input/output stream
#include <string_view>  // for std::string_view which should be faster than std::string
#include <array>        // for std::array<T,N>
#include <cstdint>      // for std::uint32_t
#include <cctype>       // for std::tolower()
#include <limits>	    // for std::numeric_limits

// Handles invalid inputs
void ignoreLine()
{
   // Ignores all characters up to next int
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// const while being able to handle compiled-time constant context
constexpr int numItems{ 6 };

// const while being able to handle compiled-time constant context
constexpr std::array<std::string_view, numItems> itemShopStore =
{"Boots", "Swords", "Helmets", "SuperSecretAwesomeItem", "Chestplate", "Leggings"};

// Handles printing the arrays
void printShop(const std::array<std::string_view, numItems> &ShopsItems);
void printInventory(const std::array<int, numItems> &playerInventory);

// Increments fixed-shop array elements based on purchased itemShopStore
void buyItems(std::array<int, numItems> &playerInventory);


int main()
{
   // Sets the fixed array for playerInventory
   std::array<int, numItems> playerInventory = {0, 0, 1, 0, 1, 0};

   // Handles loop
   bool isRunning = 1;

   // Handles shop input
   char shopDetector{};
   
   // Shop Loop
   while(isRunning)
   {
      printShop(itemShopStore);
      printInventory(playerInventory);

      std::cout << "--- If you would like to buy items type b, else, type q to exit ---" << '\n';
      std::cout << ": ";

      std::cin >> shopDetector;
      // If std::cin goes into failure mode
      if(std::cin.fail())
      {
         if(std::cin.eof())	// If stream was closed (CRTL+D in UNIX/LINUX)
         {
            std::cout << "EXITED!" << std::endl;
            std::exit(0);	// Shut down the progran!
         }
         std::cin.clear();	// Put us back in 'normal' operation
         ignoreLine();		// and remove bad input
      }
      ignoreLine();
      
      char answer = std::tolower(shopDetector);

      if(answer == 'q')
      {
         std::cout << "************ EXITING SHOP ************" << '\n';
         break;
      }

      switch(answer)
      {
         case 'b':{
            buyItems(playerInventory);
         }break;

         default:{
            std::cout << "\n\n";
            std::cout << "------------------------------------------------------------" << '\n';
            std::cout << "INVALID INPUT! Try again!!!" << '\n';
            std::cout << "------------------------------------------------------------" << '\n';
         }break;
      }
   }
   

   std::cout << std::endl;

//   getchar();
   return 0;
}

void printInventory(const std::array<int, numItems> &playerInventory)
{
   std::cout << "Items in your inventory: " << '\n';
   for(size_t i{ 0 }; i < playerInventory.size(); i++)
   {
      if(playerInventory[i] > 0)
      {
         std::cout << playerInventory[i] << "x" << itemShopStore[i] << '\n';
      }
      
   }
}

void printShop(const std::array<std::string_view, numItems> &ShopsItems)
{
   std::uint32_t counter{ 1 };
   std::cout << "*** WELCOME TO THE ITEM SHOP, TRAVELERS! ***" << std::endl;
   
   std::cout << "Items in the Shop: " << std::endl;
   std::cout << "-----------------------------------------------" << std::endl;
   for(size_t i{ 0 }; i < ShopsItems.size(); i++)
   {
      std::cout << counter << " | "<< ShopsItems[i] << '\n';
      counter++;
   }
   std::cout << "-----------------------------------------------" << std::endl;
}


void buyItems(std::array<int, numItems> &playerInventory)
{
   size_t input = 0;
   std::cout << "What item would you like to buy from store? (" << 1 << "-" << itemShopStore.size() << "): ";
   std::cin >> input;

   if(input <= 0 || input > itemShopStore.size())
   {
      std::cout << "\n\n******* Invalid number! Please select 1 - 6 *******" << '\n';
   } else {
      playerInventory.at(input - 1)++;
   }

   
}

