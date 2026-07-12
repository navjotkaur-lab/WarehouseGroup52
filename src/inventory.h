#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_DESC 64
#define MAX_CATEG 16

// Item struct
typedef struct{
    int item_id;
    char description[MAX_DESC];
    char category[MAX_CATEG];
    int stock_level;

} Item;

//------------

// Stage of the order enum
enum Stage{
    RECEIVED,
    PICKING,
    PACKING,
    SHIPPED
};

// Order struct
typedef struct{
    int client_id;
    int item_id;
    int quantity;
    enum Stage stage;  
} Order;

//------------

//Restocking shipment struct
typedef struct{
    int supplier_id;
    int item_id;
    int quantity;
} RestockShipment;

void decrementInventory (Order order);

void incrementInventory (RestockShipment restockShipment);

Item getItem(int id);


#endif