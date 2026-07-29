# WarehouseGroup52

INDEX
MAIN ASPECTS
1. bootstrapping program, order script and management script
     a. MUST-HAVES (implementation)
     b. ERROR-HANDLING (across different operations and files)
2. warehouse process
3. supplier processes
4. extras pointers
     a. orders cycle of life
     b. ideas to let (2.) and (3.) communicate



CHAPTER ONE
1. BS  --  GLUE OF THE WHOLE THING  (+ order and management scripts kinda like user interface to order, display things and stuff)
    - in bash
    - sets environment: splits inventory if needed
                       creates FIFO (queues for each robot) (sizes specified at startup)
                                     -> gen config files for each supplier (which items, quantity, delivery time)
                                      -> need an algorithm to derive config files from inventory.csv (+ all items must be covered)
    - allows: (USER) placing orders
               (MANAGER) control of system
               (ANALYST) inspect log files
    - forks (3.) processes
    
    
        a. MANDATORY STUFF to implement (in the bash script)
        - check how many processes are running
        - restock an item by sending a message to (2. WH) via IPC
        - display current inventory levels for each item
        - display sizes of  PendingOrdersQueue  AND  PackagingQueue
        - display orders STATISTICS -> how?      grep, sort, awk, wc  use as appropriate
                                   -> what?    tot number of shipped orders
                                               number of rejected orders
                                               most popular items
        - "gracefully shut down every process (2.WH and 3.SP) and clean IPC resources"


        b. ERROR HANDLING
        - each operation must return code to indicate success and/or failure
                  -> system must define set of error codes that can be returned by operations
                  -> if a parameter can fail, then there must error-handling course for each scenario
        - each FILE operation must check for errors and report accordingly if operation fails (ex: read inventory.csv, write order.log)
    
      


CHAPTER TWO     
2. WH  --  CORE OF THE SYSTEM
   - inventory management (ex. lock it when there's incoming restocking to not let pickers fuck it up) 
   - processing of incoming orders -> how? -> thread pools for (order receivers)
                                                               (picker robots)
                                                               (packers)
  - NO messages BLOCKINGS while dealing with both (3. SP) and order messages/management
  - PROTECT FROM SIMULTANEOUS read() AND write() -> how -> SYNCHRONIZATION PRIMITIVES




CHAPTER THREE    
3. SP  --  small seemless pain in the ass
   - IPC communication
   - periodically delivers restocking shipments to (2. WH) 
   - must run concurrently with (2. WH) (NO messages BLOCKINGS)





CHAPTER NOTES/MENTAL IMAGINERY
4. extras
   - there are specific order characteristics
   - there are specific item characteristics
  
     
     a. ORDER STUFF  (put sleep() functions to simulate waiting time)
     - order thread -> check supply-demand
          -> picker robot <-> WH <- supplier
               -> packaging
                   -> mark as shipped (=append to orders.log)

     b. WH <-> SP COMMUNICATIO (ideas/pointers given on the file because I wouldn't have had the imagination/knowledge tbh kill me now)
         - signals + writing to a temporary file
         - send request via IPC +wait for response
         - can't remember the other ones, they are on the file, what should we do?
      




