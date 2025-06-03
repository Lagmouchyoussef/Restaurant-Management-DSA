
## Data Structure Manipulation

We consider the following structures:

- **Dish**: name, category, price  
- **DishElement**: contains a Dish variable, a pointer to the next element, and a pointer to the previous element  
- **Menu**: List of dishes, menu name  
- **MenuElement**: contains a Menu variable, a pointer to the next element, and a pointer to the previous element  

## Search Operations

1. `void displayDishesByCategory(Menu M, char* category)` → Displays all dishes belonging to a specific category  
2. `MenuElement* searchMenuByName(MenuElement* Em, char* name)` → Searches for a menu by its name  
3. `DishElement* searchDishByNameInMenus(MenuElement* Em, char* name)` → Searches through all menus to find a dish with a specific name (returns its address)  
4. `DishElement* searchDishByName(DishElement* Ep, char* name)` → Searches for a dish in a dishes list (using the dish name as parameter)  

## List Retrieval

1. `DishElement* getByCategory(Menu M, char* category)` → Returns the list of dishes in a specific category  
2. `DishElement* getDishesAbovePrice(Menu M, float price)` → Returns dishes with price higher than specified  
3. `MenuElement* getMenusByDishCount(MenuElement* Em)` → Returns menus containing more than 20 dishes  
4. `MenuElement* getFilteredMenus(MenuElement* Em)` → Returns menus with more than 20 dishes where price doesn't exceed 50db  

## Ordered Insertion

1. `DishElement* insertByPriceOrder(DishElement* Ep, Dish p)` → Adds a dish to the dishes list ordered by ascending price  
2. `DishElement* insertByNameOrder(DishElement* Ep, Dish p)` → Adds a dish to the list ordered alphabetically by name  
3. `Menu addByNameOrder(Menu M, Dish p)` → Adds a dish to a menu ordered by name  

# Deletion

1. `DishElement* deleteByName(DishElement* Ep, char* name)` → Deletes the dish matching a specific name  
2. `DishElement* deleteByCategory(DishElement* Ep, char* category)` → Deletes all dishes belonging to a specific category  
3. `MenuElement* deleteByDishCount(MenuElement* Em, int count)` → Deletes menus containing a specific number of dishes  

## Part II

Redo all the above operations considering a circular singly linked list
